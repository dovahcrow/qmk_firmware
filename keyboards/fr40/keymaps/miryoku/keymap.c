// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "print.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed)
    dprintf("%#02X pressed, interrupted %d\n", keycode, record->tap.interrupted);
  else 
    dprintf("%#02X released, interrupted %d\n", keycode, record->tap.interrupted);

  if (!process_achordion(keycode, record)) {
      return false;
  }
  // your macros ...

  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    if (other_keycode == KC_B) {
        return true;
    }
    if (other_keycode == KC_SPC) {
        return true;
    }

    // Also allow same-hand holds when the other key is in the rows below the
    // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
    // if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }

    // Otherwise, follow the opposite hands rule.
    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  return 1000;
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LCTL:
    case MOD_RCTL:
    case MOD_LGUI:
    case MOD_RGUI:
      return true;  // Eagerly apply Shift and Ctrl mods.

    default:
      return false;
  }
}

#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)
#define HOME_N LSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I RALT_T(KC_I)
#define HOME_O LGUI_T(KC_O)

// uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
//   // If you quickly hold a tap-hold key after tapping it, the tap action is
//   // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
//   // lead to missed triggers in fast typing. Here, returning 0 means we
//   // instead want to "force hold" and disable key repeating.
//   switch (keycode) {
//     // Repeating is useful for Vim navigation keys.
//     case KC_H:
//     case HOME_J:
//     case HOME_K:
//     case HOME_L:
//       return QUICK_TAP_TERM;  // Enable key repeating.
//     default:
//       return 0;  // Otherwise, force hold and disable key repeating.
// }
// }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NO  , KC_Q         , KC_W         , KC_F         , KC_P  , KC_B, KC_NO        , KC_J          , KC_L         , KC_U   , KC_Y         , KC_QUOT,
        KC_NO  , HOME_A       , HOME_R       , HOME_S       , HOME_T, KC_G, KC_M         , HOME_N        , HOME_E       , HOME_I , HOME_O       , 
        KC_Z   , KC_X         , KC_C         , KC_D         , KC_V  , KC_K, KC_H         , KC_COMM       , KC_DOT       , KC_SLSH, CW_TOGG      ,
        CW_TOGG, LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB), KC_SPC,       LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), KC_NO  , KC_RIGHT
    ),
    // The Media Layer
    [1] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO , KC_UNDO, KC_PASTE, KC_COPY, KC_CUT  , KC_UNDO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO , KC_CAPS, KC_LEFT , KC_UP  , KC_RIGHT, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO , KC_NO  , KC_NO   , KC_NO  , KC_NO   ,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_ENT, KC_BSPC, KC_DEL  , KC_NO  , KC_NO
    ),
    // The Nav Layer
    [2] = LAYOUT(
        MEH(KC_SPC), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  , KC_UNDO, KC_PASTE, KC_COPY, KC_CUT  , KC_UNDO,
        KC_NO      , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_CAPS, KC_LEFT, KC_DOWN , KC_UP  , KC_RIGHT,
        KC_NO      , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  , KC_NO  , KC_NO   , KC_NO  , KC_NO   ,
        KC_NO      , KC_NO, KC_NO, KC_NO, KC_NO,        KC_ENT , KC_BSPC, KC_DEL  , KC_NO  , KC_NO
    ),
    // The Mouse Layer
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO            , KC_UNDO             , KC_PASTE            , KC_COPY           , KC_CUT               , KC_UNDO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO            , QK_MOUSE_CURSOR_LEFT, QK_MOUSE_CURSOR_DOWN, QK_MOUSE_CURSOR_UP, QK_MOUSE_CURSOR_RIGHT, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO            , KC_NO               , KC_NO               , KC_NO             , KC_NO                ,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        QK_MOUSE_BUTTON_2, QK_MOUSE_BUTTON_1   , QK_MOUSE_BUTTON_3   , KC_NO             , KC_NO
    ),
    // The Sym Layer
    [4] = LAYOUT(
        KC_NO    , S(KC_LBRC), S(KC_7), S(KC_8)   , S(KC_9)   , S(KC_RBRC), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO ,
        KC_NO    , KC_NO     , S(KC_4), S(KC_5)   , S(KC_6)   , S(KC_EQL) , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        S(KC_GRV), S(KC_1)   , S(KC_2), S(KC_3)   , S(KC_BSLS), KC_NO     , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO    , S(KC_9)   , S(KC_0), S(KC_MINS), KC_NO     ,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO 
    ),
    // The Num Layer
    [5] = LAYOUT(
        KC_NO , KC_LBRC, KC_7, KC_8   , KC_9   , KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO ,
        KC_NO , KC_NO  , KC_4, KC_5   , KC_6   , KC_EQL , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_GRV, KC_1   , KC_2, KC_3   , KC_BSLS, KC_NO  , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO , KC_DOT , KC_0, KC_MINS, KC_NO  ,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO 
    ),
    // The Fun Layer
    [6] = LAYOUT(
        KC_NO , KC_LBRC, KC_7, KC_8   , KC_9   , KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO ,
        KC_NO , KC_NO  , KC_4, KC_5   , KC_6   , KC_EQL , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_GRV, KC_1   , KC_2, KC_3   , KC_BSLS, KC_NO  , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO , KC_DOT , KC_0, KC_MINS, KC_NO  ,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO 
    )
};

const uint16_t PROGMEM combo_bootloader[] = {KC_QUOT, KC_Q, COMBO_END};

const uint16_t PROGMEM combo_as[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_bf[] = {KC_B, KC_F, COMBO_END};
const uint16_t PROGMEM combo_bg[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM combo_bv[] = {KC_B, KC_V, COMBO_END};
const uint16_t PROGMEM combo_cd[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_cv[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_cx[] = {KC_C, KC_X, COMBO_END};
const uint16_t PROGMEM combo_df[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_ds[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM combo_dv[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM combo_ed[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo_ef[] = {KC_E, KC_F, COMBO_END};
const uint16_t PROGMEM combo_er[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_ew[] = {KC_E, KC_W, COMBO_END};
const uint16_t PROGMEM combo_fg[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo_fr[] = {KC_F, KC_R, COMBO_END};
const uint16_t PROGMEM combo_fs[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM combo_fv[] = {KC_F, KC_V, COMBO_END};
const uint16_t PROGMEM combo_fw[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM combo_gt[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM combo_ij[] = {KC_I, KC_J, COMBO_END};
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_iu[] = {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM combo_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_jl[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM combo_jn[] = {KC_J, KC_N, COMBO_END};
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_kn[] = {KC_K, KC_N, COMBO_END};
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_rt[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo_sv[] = {KC_S, KC_V, COMBO_END};
const uint16_t PROGMEM combo_ty[] = {KC_T, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_uy[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_xz[] = {KC_X, KC_Z, COMBO_END};

const uint16_t PROGMEM combo_tabq[] = {KC_TAB, KC_Q, COMBO_END};
const uint16_t PROGMEM combo_pbspc[] = {KC_P, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
  COMBO(combo_bootloader, QK_BOOT),


    // COMBO(combo_xz, LGUI(KC_Z)),
    COMBO(combo_xz, LGUI(KC_X)),
    COMBO(combo_cx, LGUI(KC_C)),
    COMBO(combo_cv, LGUI(KC_V)),
    COMBO(combo_as, LGUI(KC_A)), 
    COMBO(combo_ds, LGUI(KC_S)), 

    
    COMBO(combo_tabq, LCA(KC_1)), 
    COMBO(combo_qw, LCA(KC_2)), 
    COMBO(combo_ew, LCA(KC_3)), 
    COMBO(combo_er, LCA(KC_4)), 
    COMBO(combo_rt, LCA(KC_5)), 
    COMBO(combo_ty, LCA(KC_6)), 
    COMBO(combo_uy, LCA(KC_7)), 

    COMBO(combo_op, MEH(KC_MINS)), 
    COMBO(combo_pbspc, MEH(KC_EQL))
};

