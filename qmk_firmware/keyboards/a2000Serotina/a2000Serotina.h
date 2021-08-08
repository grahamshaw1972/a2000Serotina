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

#pragma once

#include "quantum.h"

__attribute__((weak)) void matrix_init_user(void);

void amikb_sendkey(unsigned char keycode, int press);
void amikb_wait_for_ack_resync_if_none(void);
void amikb_wait_for_ack_reset_if_none(long timeout);
void wait_for_amiga(long timeout);
void amikb_reset(void);
void hard_reset(void);
void init_timer(void);
void reset_timer(void);
unsigned long get_msec(void);
void updateStatusLEDs(unsigned char previousCount, unsigned char newCount, int pressed, unsigned char amigaKeyCode);

// ACLK == KCLK == F6
#define ACLK	6
#define ACLK_BIT	(1 << ACLK)

// ADATA == KDAT == F7
#define ADATA	7
#define ADATA_BIT	(1 << ADATA)

#define TIMEOUT_MSEC 143
#define RESET_WARNING_MSEC 250
#define RESET_MSEC 500
#define RESET_WARNING_FULL_MSEC 10000

#define STA3 F3
#define STA2 F4
#define STA1 F5
#define KDAT F7
#define KCLK F6

#define LAYOUT( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09, K0A,   \
    K10, K11, K12, K13, K14, K15,                            \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A,   \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39,        \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,   \
    K50, K51, K52, K53, K54, K55, K56, K57, K58, K59,        \
    K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A,   \
    K70, K71,                     K76, K77, K78,             \
    K80, K81, K82, K83, K84, K85, K86, K87, K88, K89, K8A,   \
    K90, K91,           K94,      K96, K97, K98, K99,        \
    KA0, KA1, KA2,                KA6,                KAA,   \
    KB0, KB1, KB2, KB3, KB4, KB5, KB6,      KB8              \
) { \
    { K00,   KC_NO, K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   KC_NO }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A   }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58,   K59,   KC_NO }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67,   K68,   K69,   K6A   }, \
    { K70,   K71,   KC_NO, KC_NO, KC_NO, KC_NO, K76,   K77,   K78,   KC_NO, KC_NO }, \
    { K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87,   K88,   K89,   K8A   }, \
    { K90,   K91,   KC_NO, KC_NO, K94,   KC_NO, K96,   K97,   K98,   K99,   KC_NO }, \
    { KA0,   KA1,   KA2,   KC_NO, KC_NO, KC_NO, KA6,   KC_NO, KC_NO, KC_NO, KAA   }, \
    { KB0,   KB1,   KB2,   KB3,   KB4,   KB5,   KB6,   KC_NO, KB8,   KC_NO, KC_NO }, \
}

// Amiga Keycodes
#define AKC_GRV    0x00
#define AKC_1      0x01
#define AKC_2      0x02
#define AKC_3      0x03
#define AKC_4      0x04
#define AKC_5      0x05
#define AKC_6      0x06
#define AKC_7      0x07
#define AKC_8      0x08
#define AKC_9      0x09
#define AKC_0      0x0A
#define AKC_MINS   0x0B
#define AKC_EQL    0x0C
#define AKC_BSLS   0x0D
#define AKC_SPR0   0x0E
#define AKC_P0     0x0F
#define AKC_Q      0x10
#define AKC_W      0x11
#define AKC_E      0x12
#define AKC_R      0x13
#define AKC_T      0x14
#define AKC_Y      0x15
#define AKC_U      0x16
#define AKC_I      0x17
#define AKC_O      0x18
#define AKC_P      0x19
#define AKC_LBRC   0x1A
#define AKC_RBRC   0x1B
#define AKC_SPR1   0x1C
#define AKC_P1     0x1D
#define AKC_P2     0x1E
#define AKC_P3     0x1F
#define AKC_A      0x20
#define AKC_S      0x21
#define AKC_D      0x22
#define AKC_F      0x23
#define AKC_G      0x24
#define AKC_H      0x25
#define AKC_J      0x26
#define AKC_K      0x27
#define AKC_L      0x28
#define AKC_SCLN   0x29
#define AKC_QUOT   0x2A
#define AKC_NUHS   0x2B
#define AKC_SPR2   0x2C
#define AKC_P4     0x2D
#define AKC_P5     0x2E
#define AKC_P6     0x2F
#define AKC_NUBS   0x30
#define AKC_Z      0x31
#define AKC_X      0x32
#define AKC_C      0x33
#define AKC_V      0x34
#define AKC_B      0x35
#define AKC_N      0x36
#define AKC_M      0x37
#define AKC_COMM   0x38
#define AKC_DOT    0x39
#define AKC_SLSH   0x3A
#define AKC_SPR3   0x3B
#define AKC_PDOT   0x3C
#define AKC_P7     0x3D
#define AKC_P8     0x3E
#define AKC_P9     0x3F
#define AKC_SPC    0x40
#define AKC_BSPC   0x41
#define AKC_TAB    0x42
#define AKC_PENT   0x43
#define AKC_ENT    0x44
#define AKC_ESC    0x45
#define AKC_DEL    0x46
#define AKC_SPR4   0x47
#define AKC_SPR5   0x48
#define AKC_SPR6   0x49
#define AKC_PMNS   0x4A
#define AKC_UNDF   0x4B
#define AKC_UP     0x4C
#define AKC_DOWN   0x4D
#define AKC_RGHT   0x4E
#define AKC_LEFT   0x4F
#define AKC_F1     0x50
#define AKC_F2     0x51
#define AKC_F3     0x52
#define AKC_F4     0x53
#define AKC_F5     0x54
#define AKC_F6     0x55
#define AKC_F7     0x56
#define AKC_F8     0x57
#define AKC_F9     0x58
#define AKC_F10    0x59
#define AKC_PLPN   0x5A
#define AKC_PRPN   0x5B
#define AKC_PSLS   0x5C
#define AKC_PAST   0x5D
#define AKC_PPLS   0x5E
#define AKC_HELP   0x5F
#define AKC_LSFT   0x60
#define AKC_RSFT   0x61
#define AKC_CAPS   0x62
#define AKC_CTRL   0x63
#define AKC_LALT   0x64
#define AKC_RALT   0x65
#define AKC_LAMI   0x66
#define AKC_RAMI   0x67
#define AKC_RST_WARN 0x78
#define AKC_MAX    0x79

extern unsigned char amiga_keycode_table[MATRIX_ROWS][MATRIX_COLS];

// generated by KBFirmware JSON to QMK Parser
// https://noroadsleft.github.io/kbf_qmk_converter/
