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
    if (other_keycode == KC_B || other_keycode == KC_T) {
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

#define HOME_A LSFT_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LCTL_T(KC_F)
#define HOME_J RCTL_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_ENT RSFT_T(KC_ENT)

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    // Repeating is useful for Vim navigation keys.
    case KC_H:
    case HOME_J:
    case HOME_K:
    case HOME_L:
    case KC_D:
      return QUICK_TAP_TERM;  // Enable key repeating.
    default:
      return 0;  // Otherwise, force hold and disable key repeating.
  }
}

#define TL_MOUSE MO(4)
#define TL_NAV MO(5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB , KC_Q    , KC_W  , KC_E   , KC_R  , KC_T   , KC_Y   , KC_U  , KC_I   , KC_O   , KC_P    , KC_BSPC,
        KC_ESC , HOME_A  , HOME_S, HOME_D , HOME_F, KC_G   , KC_H   , HOME_J, HOME_K , HOME_L , HOME_ENT, 
        CW_TOGG, KC_Z    , KC_X  , KC_C   , KC_V  , KC_B   , KC_N   , KC_M  , KC_NO  , KC_UP  , KC_NO   ,
        KC_NO  , TL_MOUSE, TL_NAV, TL_LOWR, KC_SPC,          TL_UPPR, KC_NO , KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    // The Lower (Sym) Layer
    [1] = LAYOUT(
        MEH(KC_SPC), KC_QUOT, S(KC_COMM), S(KC_4), S(KC_DOT) , KC_NO  , KC_NO  , KC_LBRC   , S(KC_MINS), KC_RBRC   , KC_SCLN   , KC_NO,
        S(KC_QUOT) , KC_BSLS, S(KC_0)   , S(KC_2), S(KC_9)   , S(KC_3), S(KC_5), S(KC_LBRC), KC_GRV    , S(KC_RBRC), S(KC_BSLS),
        KC_NO      , KC_NO  , S(KC_SCLN), S(KC_1), S(KC_SLSH), KC_NO  , S(KC_7), S(KC_6)   , S(KC_GRV) , KC_NO     , KC_NO     , 
        KC_NO      , KC_NO  , KC_NO     , TL_LOWR, KC_NO     ,          TL_UPPR, KC_NO     , KC_NO     , KC_NO     , KC_NO
    ),
    // The Upper (Num) Layer
    [2] = LAYOUT(
        MEH(KC_SPC), KC_1, KC_2, KC_3   , KC_4     , KC_5   , KC_6 , KC_7  , KC_8   , KC_9  , KC_0 , KC_NO,
        KC_NO      , KC_4, KC_5, KC_6   , KC_MINS  , S(KC_8), KC_NO, KC_EQL, KC_COMM, KC_DOT, KC_NO,
        KC_NO      , KC_7, KC_8, KC_9   , S(KC_EQL), KC_SLSH, KC_NO, KC_NO , KC_NO  , KC_NO , KC_NO,
        KC_NO      , KC_0, KC_0, TL_LOWR, KC_NO    ,          TL_UPPR, KC_NO, KC_NO , KC_NO  , KC_NO
    ),
  // The Adjusted (Fun) Layer
  [3] = LAYOUT(
        KC_F1  , KC_F2     , KC_F3, KC_F4, KC_F5  , KC_F6, KC_F7, KC_F8  , KC_F9  , KC_F10 , KC_F11      , KC_F12,
        KC_SLEP, KC_NO     , KC_NO, KC_NO, KC_PSCR, KC_NO, KC_NO, KC_VOLD, KC_VOLU, KC_MUTE, LCA(KC_SLSH),
        KC_NO  , C(G(KC_Q)), KC_NO, KC_NO, KC_NO  , KC_NO, KC_NO, KC_NO  , KC_NO  , KC_NO  , LCA(KC_COMM),
        DB_TOGG, KC_NO     , KC_NO, KC_NO, KC_NO  ,        KC_NO, KC_NO  , KC_NO  , KC_NO  , KC_NO
    ),
    // The Mouse Layer
    [4] = LAYOUT(
        MEH(KC_SPC), LCA(KC_1), LCA(KC_2), LCA(KC_3), LCA(KC_4), LCA(KC_5), LCA(KC_6), LCA(KC_7), KC_NO  , KC_NO  , KC_NO, KC_NO,
        KC_NO      , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_MS_L  , KC_MS_D  , KC_MS_U, KC_MS_R, KC_NO,
        KC_NO      , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , MS_WHLU  , MS_WHLD  , KC_NO  , KC_NO  , KC_NO,
        KC_NO      , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,            KC_BTN1  , KC_BTN2  , KC_BTN3, KC_NO  , KC_NO
    ),
    // The Nav Layer
    [5] = LAYOUT(
        MEH(KC_SPC), LCA(KC_1), LCA(KC_2), LCA(KC_3), LCA(KC_4), LCA(KC_5), LCA(KC_6), LCA(KC_7), G(KC_X)  , G(KC_V), G(KC_Z)  , KC_NO,
        KC_NO      , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_CAPS  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT, KC_NO    ,
        KC_NO      , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_HOME  , KC_PGUP  , KC_PGDN  , KC_END , KC_NO    ,
        KC_NO      , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,            KC_NO    , KC_NO    , LCA(KC_H), KC_NO  , LCA(KC_L)
    )
};

const uint16_t PROGMEM combo_bootloader[] = {KC_TAB, KC_BSPC, COMBO_END};

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

    
    // COMBO(combo_tabq, LCA(KC_1)), 
    // COMBO(combo_qw, LCA(KC_2)), 
    // COMBO(combo_ew, LCA(KC_3)), 
    // COMBO(combo_er, LCA(KC_4)), 
    // COMBO(combo_rt, LCA(KC_5)), 
    // COMBO(combo_ty, LCA(KC_6)), 
    // COMBO(combo_uy, LCA(KC_7)), 

    COMBO(combo_fv, LGUI(KC_F)), 

    COMBO(combo_op, MEH(KC_MINS)), 
    COMBO(combo_pbspc, MEH(KC_EQL))
};

