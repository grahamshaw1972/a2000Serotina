/* Copyright 2021 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include "a2000Serotina.h"

static void resync(void);

static volatile unsigned long ticks;

void init_timer(void)
{
	power_timer0_enable();

	TCCR0A = 0;
	TCCR0B = PRESCL_256;

	TIMSK0 |= (1 << TOIE0);	/* enable ovf intr. */
}

void reset_timer(void)
{
	ticks = 0;
}

unsigned long get_msec(void)
{
	return 1000 * ticks / TICKS_PER_SEC;
}

ISR(TIMER0_OVF_vect)
{
	++ticks;
}

void flash_leds(void) {
	writePinHigh(STA3_LED);
	writePinHigh(STA2_LED);
	writePinHigh(STA1_LED);
	writePinHigh(CTRL_LED);
	writePinHigh(LAMI_LED);
	writePinHigh(RAMI_LED);
	writePinHigh(NLCK_LED);
	writePinHigh(SLCK_LED);
	writePinHigh(CAPS_LED);
	_delay_ms(INIT_FLASH_MSEC);
	writePinLow(STA3_LED);
	writePinLow(STA2_LED);
	writePinLow(STA1_LED);
	writePinLow(CTRL_LED);
	writePinLow(LAMI_LED);
	writePinLow(RAMI_LED);
	writePinLow(NLCK_LED);
	writePinLow(SLCK_LED);
	writePinLow(CAPS_LED);
}

__attribute__((weak)) void matrix_init_user(void) {
    setPinOutput(STA3_LED);
    setPinOutput(STA2_LED);
    setPinOutput(STA1_LED);
    setPinOutput(KCLK);
    setPinOutput(CTRL_LED);
    setPinOutput(LAMI_LED);
    setPinOutput(RAMI_LED);
    setPinOutput(CAPS_LED);

    writePinHigh(KCLK);

    init_timer();

    flash_leds();
}

static unsigned char prevAmigaKeycode = 0xff;
static unsigned char amiga_key_pressed[AKC_MAX] = { 0 }; // Zero-fill

__attribute__((weak)) bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	static int pressed = 0;

	unsigned char amigaKeyCode = amiga_keycode_table[record->event.key.row][record->event.key.col];
	unsigned char previousCount = amiga_key_pressed[amigaKeyCode];
	bool physicalKeyPressed = record->event.pressed;
	bool logicalKeyPressed;

	if( amigaKeyCode == AKC_CAPS ) {
		if( physicalKeyPressed ) {
			if(previousCount > 0) {
				amiga_key_pressed[amigaKeyCode]=0;
			} else {
				amiga_key_pressed[amigaKeyCode]=1;
			}
		}
	} else {
		if( physicalKeyPressed ) {
			amiga_key_pressed[amigaKeyCode]++;
		} else {
			amiga_key_pressed[amigaKeyCode]--;
		}
	}
	unsigned char newCount = amiga_key_pressed[amigaKeyCode];

	if( previousCount == 0 && newCount > 0 ) {
		pressed++;
		logicalKeyPressed = true;
	}

	if( previousCount > 0 && newCount == 0 ) {
		pressed--;
		logicalKeyPressed = false;
	}

	update_status_leds(previousCount, newCount, pressed, amigaKeyCode);

	if( amiga_key_pressed[AKC_CTRL] > 0 && amiga_key_pressed[AKC_LAMI] > 0 && amiga_key_pressed[AKC_RAMI] > 0 ) {
		amikb_reset();
	} else {
		if( (previousCount == 0 && newCount > 0) || (previousCount > 0 && newCount == 0) ) {
			amikb_sendkey(amigaKeyCode, logicalKeyPressed);
			amikb_wait_for_ack_resync_if_none();
		}
	}

	return true;
}

void update_status_leds(unsigned char previousCount, unsigned char newCount, int pressed, unsigned char amigaKeyCode) {
	if( pressed > 0 ) {
		writePinHigh(STA3_LED);
	} else {
		writePinLow(STA3_LED);
	}

	if( pressed > 1 ) {
		writePinHigh(STA2_LED);
	} else {
		writePinLow(STA2_LED);
	}

	if( pressed > 2 ) {
		writePinHigh(STA1_LED);
	} else {
		writePinLow(STA1_LED);
	}

	if( amigaKeyCode == AKC_CTRL ) {
		if( newCount > 0 ) {
			writePinHigh(CTRL_LED);
		} else {
			writePinLow(CTRL_LED);
		}
	}

	if( amigaKeyCode == AKC_LAMI ) {
		if( newCount > 0 ) {
			writePinHigh(LAMI_LED);
		} else {
			writePinLow(LAMI_LED);
		}
	}

	if( amigaKeyCode == AKC_RAMI) {
		if( newCount > 0 ) {
			writePinHigh(RAMI_LED);
		} else {
			writePinLow(RAMI_LED);
		}
	}

	if( amigaKeyCode == AKC_CAPS) {
		if( newCount > 0 ) {
			writePinHigh(CAPS_LED);
		} else {
			writePinLow(CAPS_LED);
		}
	}
}

void amikb_sendkey(unsigned char amigaKeycode, int press)
{
	int i;

	/* amigaKeycode bit transfer order: 6 5 4 3 2 1 0 7 (7 is pressed flag) */
	amigaKeycode = (amigaKeycode << 1) | (~press & 1);
	if(amigaKeycode == prevAmigaKeycode) return;
	prevAmigaKeycode = amigaKeycode;

	/* make sure we don't pulse the lines while grabbing control
	 * by first reinstating the pullups before changing direction
	 */
	PORTF |= ACLK_BIT | ADATA_BIT;
	DDRF |= ACLK_BIT | ADATA_BIT;

	/* pulse the data line and wait for about 100us */
	PORTF &= ~ADATA_BIT;
	_delay_us(20);
	PORTF |= ADATA_BIT;
	_delay_us(100);

	for(i=0; i<8; i++) {
		/* data line is inverted */
		if(amigaKeycode & 0x80) {
			PORTF &= ~ADATA_BIT;
		} else {
			PORTF |= ADATA_BIT;
		}
		amigaKeycode <<= 1;
		_delay_us(20);
		/* pulse the clock */
		cli();
		PORTF &= ~ACLK_BIT;
		EIFR |= (1 << INTF1);
		sei();
		_delay_us(20);
		PORTF |= ACLK_BIT;
		_delay_us(20);
	}
}

void amikb_wait_for_ack_resync_if_none(void) {

	/* similarly tristate first, then drop the pullups */
	DDRF &= ~(ACLK_BIT | ADATA_BIT);
	PORTF &= ~(ACLK_BIT | ADATA_BIT);

	reset_timer();
	// Wait for KDAT to go low
	while(PINF & ADATA_BIT) {
		if(get_msec() >= TIMEOUT_MSEC) {
			resync();
			break;
		}
	}
	DDRF |= ACLK_BIT;
	PORTF |= ACLK_BIT;
}

void amikb_wait_for_ack_reset_if_none(long timeout) {

	/* similarly tristate first, then drop the pullups */
	DDRF &= ~(ACLK_BIT | ADATA_BIT);
	PORTF &= ~(ACLK_BIT | ADATA_BIT);

	reset_timer();
	// Wait for KDAT to go low
	while(PINF & ADATA_BIT) {
		if(get_msec() >= timeout) {
			hard_reset();
			break;
		}
	}
	DDRF |= ACLK_BIT;
	PORTF |= ACLK_BIT;
}

void wait_for_amiga(long timeout) {
	DDRF &= ~(ACLK_BIT | ADATA_BIT);
	PORTF &= ~(ACLK_BIT | ADATA_BIT);
	reset_timer();
	// Wait for KDAT to go high
	while(!(PINF & ADATA_BIT)) {
		if(get_msec() >= timeout) {
			break;
		}
	}
	DDRF |= ACLK_BIT;
	PORTF |= ACLK_BIT;
}

static void resync(void)
{
	writePinHigh(STA1_LED);

	PORTF |= ACLK_BIT | ADATA_BIT;

	for(;;) {
		cli();
		DDRF |= ACLK_BIT | ADATA_BIT;

		PORTF &= ~ACLK_BIT;
		EIFR |= (1 << INTF1);
		sei();
		_delay_us(20);
		PORTF |= ACLK_BIT;

		DDRF &= ~(ACLK_BIT | ADATA_BIT);

		reset_timer();
		while(get_msec() < TIMEOUT_MSEC) {
			if(!(PINF & ADATA_BIT)) {
				return;
			}
		}
	}
}

__attribute__((weak)) void housekeeping_task_user(void) {
	/*
	if( (PINB & CTRL_BIT) && (PINB & LAMI_BIT) && (PINB & RAMI_BIT) ){
		writePinHigh(STA2);
		amikb_reset();
	} else {
		writePinLow(STA2);
	}
	*/
}

void hard_reset(void) {
	DDRF |= ACLK_BIT;
	PORTF &= ~ACLK_BIT;
	reset_timer();
	while(get_msec() < RESET_MSEC) {}
	//while((PINB & CTRL_BIT) && (PINB & LAMI_BIT) && (PINB & RAMI_BIT)) {}
	PORTF |= ACLK_BIT;
}

void amikb_reset(void) {
#ifdef SEND_RESET_WARNING
	amikb_sendkey(AKC_RST_WARN,1);
	amikb_wait_for_ack_reset_if_none(TIMEOUT_MSEC);
	amikb_sendkey(AKC_RST_WARN,1);
	amikb_wait_for_ack_reset_if_none(RESET_WARNING_MSEC);
	wait_for_amiga(RESET_WARNING_FULL_MSEC);
#endif
	hard_reset();
}
