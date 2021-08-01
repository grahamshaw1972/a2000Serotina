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

#define PRESCL_256	4
/* 256 ticks per interrupt, 256 clock divisor */
#define TICKS_PER_SEC	(F_CPU / 256 / 256)

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

__attribute__((weak)) void matrix_init_user(void) {
    setPinOutput(STA3);
    setPinOutput(STA2);
    setPinOutput(STA1);
    setPinOutput(KCLK);
    setPinOutput(E0);
    setPinOutput(E1);
    setPinOutput(B7);
    writePinHigh(KCLK);

    init_timer();
}

static unsigned char prev_keycode = 0xff;
static unsigned char capslk;
static unsigned char lCtrlPressed = 0;
static unsigned char lAltPressed = 0;
static unsigned char rGuiPressed = 0;

__attribute__((weak)) bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	static int pressed = 0;

	if( record->event.pressed) {
		pressed++;
	} else {
		pressed--;
	}

	if( pressed > 0 ) {
		writePinHigh(STA3);
	} else {
		writePinLow(STA3);
	}

	if( pressed > 1 ) {
		writePinHigh(STA2);
	} else {
		writePinLow(STA2);
	}

	if( pressed > 2 ) {
		writePinHigh(STA1);
	} else {
		writePinLow(STA1);
	}

	if( keycode == KC_LCTL ) {
		if( record->event.pressed) {
			writePinHigh(E0);
			lCtrlPressed = 1;
		} else {
			writePinLow(E0);
			lCtrlPressed = 0;
		}
	}

	if( keycode == KC_LALT ) {
		if( record->event.pressed) {
			writePinHigh(E1);
			lAltPressed = 1;
		} else {
			writePinLow(E1);
			lAltPressed = 0;
		}
	}

	if( keycode == KC_RGUI ) {
		if( record->event.pressed) {
			writePinHigh(B7);
			rGuiPressed = 1;
		} else {
			writePinLow(B7);
			rGuiPressed = 0;
		}
	}

	if( lCtrlPressed && lAltPressed && rGuiPressed ) {
		amikb_reset();
	} else {
		unsigned char amigaKeyCode = amiga_keycode_table[record->event.key.row][record->event.key.col];
		amikb_sendkey(amigaKeyCode, record->event.pressed);
		amikb_wait_for_ack_resync_if_none();
	}

	return true;
}


void amikb_sendkey(unsigned char keycode, int press)
{
	int i;

	if(keycode == 0x62) {
		/* caps lock doesn't get a key release event when the key is released
		 * but rather when the caps lock is toggled off again
		 */
		if(!press) return;

		capslk = ~capslk;
		press = capslk;
	}

	/* keycode bit transfer order: 6 5 4 3 2 1 0 7 (7 is pressed flag) */
	keycode = (keycode << 1) | (~press & 1);
	if(keycode == prev_keycode) return;
	prev_keycode = keycode;

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
		if(keycode & 0x80) {
			PORTF &= ~ADATA_BIT;
		} else {
			PORTF |= ADATA_BIT;
		}
		keycode <<= 1;
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
	writePinHigh(STA1);

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
