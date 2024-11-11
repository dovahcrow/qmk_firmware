// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB        , KC_Q   , KC_W          , KC_E         , KC_R, KC_T    , KC_Y , KC_U   , KC_I   , KC_O    , KC_P          , KC_BSPC,
        LCTL_T(KC_ESC), KC_A   , KC_S          , KC_D         , KC_F, KC_G    , KC_H , KC_J   , KC_K   , KC_L    , LSFT_T(KC_ENT), 
        KC_LSFT       , KC_Z   , KC_X          , KC_C         , KC_V, KC_B    , KC_N , KC_M   , KC_RSFT, KC_UP   , MO(2)         ,
        KC_LCTL       , KC_LALT, LT(1, KC_LGUI), LT(1, KC_SPC), KC_SPC, KC_SPC, KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [1] = LAYOUT(
        MEH(KC_SPC) , LALT(KC_1)  , LALT(KC_2), LALT(KC_3), LALT(KC_4)  , LALT(KC_5), LALT(KC_6), LALT(KC_7)  , LSA(KC_MINS), LSA(KC_EQL)  , KC_VOLD      , KC_VOLU,
        KC_NO       , LGUI(KC_A)  , LGUI(KC_S), LGUI(KC_W), LGUI(KC_F)  , KC_NO     , LALT(KC_H), LALT(KC_J)  , LALT(KC_K)  , LALT(KC_L)   , LALT(KC_SLSH),
        KC_LSFT     , LGUI(KC_Z)  , LGUI(KC_X), LGUI(KC_C), LGUI(KC_V)  , LGUI(KC_3), LGUI(KC_4), LGUI(KC_5)  , LGUI(KC_6)  , LSA(KC_UP)   , LALT(KC_COMM),
        LSA(KC_SCLN), LCAG(KC_SPC), KC_TRNS   , KC_TRNS   , LGUI(KC_SPC), LGUI(KC_1), LGUI(KC_2), LSA(KC_LEFT), LSA(KC_DOWN), LSA(KC_RIGHT)
    ),
    [2] = LAYOUT(
        KC_NO, KC_BTN1   , KC_MS_U, KC_BTN2, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_VOLD, KC_VOLU,
        KC_NO, KC_MS_L   , KC_MS_D, KC_MS_R, KC_F1, KC_F2, KC_F3, KC_F4 , KC_F5 , KC_F6 , KC_NO  ,
        KC_NO, C(G(KC_Q)), KC_NO  , KC_NO  , KC_NO, KC_NO, KC_NO, KC_NO , KC_NO , KC_NO , KC_TRNS,
        KC_NO, KC_NO     , KC_NO  , KC_NO  , KC_NO, KC_NO, KC_NO, KC_NO , KC_NO , KC_NO
    )
};

const uint16_t PROGMEM combo_bootloader[] = {KC_TAB, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo_df[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_sd[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_kn[] = {KC_K, KC_N, COMBO_END};

const uint16_t PROGMEM combo_sf[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM combo_jl[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM combo_sdf[] = {KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_jkl[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_jn[] = {KC_J, KC_N, COMBO_END};

const uint16_t PROGMEM combo_ef[] = {KC_E, KC_F, COMBO_END};
const uint16_t PROGMEM combo_ji[] = {KC_J, KC_I, COMBO_END};

const uint16_t PROGMEM combo_ed[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo_dc[] = {KC_D, KC_C, COMBO_END};

const uint16_t PROGMEM combo_fv[] = {KC_F, KC_V, COMBO_END};
const uint16_t PROGMEM combo_rf[] = {KC_R, KC_F, COMBO_END};

const uint16_t PROGMEM combo_fg[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo_fb[] = {KC_F, KC_B, COMBO_END};

const uint16_t PROGMEM combo_tabq[] = {KC_TAB, KC_Q, COMBO_END};
const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_we[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_er[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_rt[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo_ty[] = {KC_T, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_yu[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo_ui[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_pbspc[] = {KC_P, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_bootloader, QK_BOOT),
    COMBO(combo_df, LSFT(KC_9)),
    COMBO(combo_jk, LSFT(KC_0)),
    COMBO(combo_sd, KC_LBRC),
    // COMBO(combo_kl, KC_RBRC),
    COMBO(combo_kn, KC_RBRC),
    COMBO(combo_sf , KC_COMM),
    // COMBO(combo_jl , KC_DOT),
    COMBO(combo_sdf, KC_COMM),
    // COMBO(combo_jkl, KC_DOT),
    COMBO(combo_jn , KC_DOT),
    COMBO(combo_ef, KC_SCLN),
    COMBO(combo_ji, KC_QUOT),
    COMBO(combo_ed, KC_EQL),
    COMBO(combo_dc, KC_MINS),
    COMBO(combo_fv, KC_BSLS),
    COMBO(combo_rf, KC_SLSH),
    COMBO(combo_tabq, KC_GRV),
    COMBO(combo_qw, KC_1),
    COMBO(combo_we, KC_2),
    COMBO(combo_er, KC_3),
    COMBO(combo_rt, KC_4),
    COMBO(combo_ty, KC_5),
    COMBO(combo_yu, KC_6),
    COMBO(combo_ui, KC_7),
    COMBO(combo_io, KC_8),
    COMBO(combo_op, KC_9),
    COMBO(combo_pbspc, KC_0),
};

