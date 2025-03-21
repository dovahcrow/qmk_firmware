// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define NDEF KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB, KC_Q, KC_W, KC_E   , KC_R  , KC_T  , NDEF ,         NDEF , KC_Y  , KC_U  , KC_I   , KC_O  , KC_P   , KC_NO,
        KC_ESC, KC_A, KC_S, KC_D   , KC_F  , KC_G  , KC_NO,         KC_NO, KC_H  , KC_J  , KC_K   , KC_L  , KC_QUOT, KC_SCLN,
        KC_NO , KC_Z, KC_X, KC_C   , KC_V  , KC_B  , KC_NO,         KC_NO, KC_N  , KC_M  , KC_COMM, KC_DOT, KC_SLSH, KC_NO,
        NDEF  , NDEF, NDEF, KC_BSPC, KC_SPC, KC_ENT, NDEF ,         NDEF , KC_ENT, KC_SPC, KC_DEL , NDEF  , NDEF   , NDEF
    ),
};

