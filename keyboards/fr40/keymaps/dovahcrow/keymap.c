// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define MOD_A MT(MOD_LGUI, KC_A)
#define MOD_S MT(MOD_LALT, KC_S)
#define MOD_D MT(MOD_LCTL, KC_D)
#define MOD_F MT(MOD_LSFT, KC_F)

#define MOD_J MT(MOD_RSFT, KC_J)
#define MOD_K MT(MOD_RCTL, KC_K)
#define MOD_L MT(MOD_LALT, KC_L)
#define MOD_QUOT MT(MOD_RGUI, KC_QUOT)

#define L_MED(KC) LT(1, KC)
#define L_NAV(KC) LT(2, KC)
#define L_MOUSE(KC) LT(3, KC)
#define L_NUM(KC) LT(4, KC)
#define L_SYM(KC) LT(5, KC)
#define L_FN(KC) LT(6, KC)

#define AR_1   LCA(KC_1)
#define AR_2   LCA(KC_2)
#define AR_3   LCA(KC_3)
#define AR_4   LCA(KC_4)
#define AR_5   LCA(KC_5)
#define AR_6   LCA(KC_6)
#define AR_7   LCA(KC_7)
#define AR_LW  LCA(KC_H)
#define AR_RW  LCA(KC_L)
#define AR_ACC LCA(KC_FSLH)
#define AR_TIL LCA(KC_COMMA)
#define OPWD   LGA(BSLH)

#define SPAD A(KC_SPC)

#define MAC_SLP C(G(KC_Q))

#define G1 G(KC_1)
#define G2 G(KC_2)
#define G3 G(KC_3)
#define G4 G(KC_4)
#define G5 G(KC_5)
#define G6 G(KC_6)
#define G7 G(KC_7)
#define G8 G(KC_8)
#define G9 G(KC_9)

enum macro_keycodes {
    SNPST_VID = SAFE_RANGE,
    SNPST_REG,
    SNPST,
    TMUXC,
    TMUXL,
    TMUXS,
    TMUX1,
    TMUX2,
    TMUX3,
    TMUX4,
    TMUX5,
    TMUX6,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #define KEYCORD(...) do { \
        uint16_t t[] = { __VA_ARGS__ }; \
        if (record->event.pressed) { \
            for (int i = 0; i < sizeof t / sizeof t[0]; i++) { \
                register_code16(t[i]); \
                unregister_code16(t[i]); \
            } \
        } \
    } while (0)

    switch (keycode) {
    case SNPST_VID:
        KEYCORD(A(C(S(KC_O))));
        return false;
    case SNPST_REG:
        KEYCORD(A(C(S(KC_I))));
        return false;
    case SNPST:
        KEYCORD(A(C(S(KC_U))));
        return false;
    case TMUXC:
        KEYCORD(A(KC_M), KC_C);
        return false;
    case TMUXL:
        KEYCORD(A(KC_M), KC_L);
        return false;
    case TMUXS:
        KEYCORD(A(KC_M), KC_LBRC);
        return false;
    case TMUX1:
        KEYCORD(A(KC_M), KC_1);
        return false;
    case TMUX2:
        KEYCORD(A(KC_M), KC_2);
        return false;
    case TMUX3:
        KEYCORD(A(KC_M), KC_3);
        return false;
    case TMUX4:
        KEYCORD(A(KC_M), KC_4);
        return false;
    case TMUX5:
        KEYCORD(A(KC_M), KC_5);
        return false;
    case TMUX6:
        KEYCORD(A(KC_M), KC_6);
        return false;
    default:
        return true;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // QWERTY
    [0] = LAYOUT(
        KC_TAB , KC_Q , KC_W   , KC_E         , KC_R         , KC_T, KC_Y         , KC_U  , KC_I   , KC_O   , KC_P    , KC_BSPC,
        KC_ESC , MOD_A, MOD_S  , MOD_D        , MOD_F        , KC_G, KC_H         , MOD_J , MOD_K  , MOD_L  , MOD_QUOT, 
        KC_LSFT, KC_Z , KC_X   , KC_C         , KC_V         , KC_B, KC_N         , KC_M  , KC_COMM, KC_DOT , KC_SLSH ,
        KC_NO  , KC_NO, KC_BSPC, L_NAV(KC_SPC), L_SYM(KC_SPC),       L_NUM(KC_ENT), KC_DEL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    // MEDIA
    [1] = LAYOUT(
        MEH(KC_SPC) , LCA(KC_1)   , LCA(KC_2) , LCA(KC_3) , LCA(KC_4)   , LCA(KC_5) , LCA(KC_6) , LCA(KC_7)   , MEH(KC_MINS), MEH(KC_EQL)  , KC_VOLD     , KC_VOLU,
        KC_NO       , LGUI(KC_A)  , LGUI(KC_S), LGUI(KC_W), LGUI(KC_F)  , KC_NO     , LCA(KC_H) , LCA(KC_J)   , LCA(KC_K)   , LCA(KC_L)    , LCA(KC_SLSH),
        KC_LSFT     , LGUI(KC_Z)  , LGUI(KC_X), LGUI(KC_C), LGUI(KC_V)  , LGUI(KC_3), LGUI(KC_4), LGUI(KC_5)  , LGUI(KC_6)  , MEH(KC_UP)   , LCA(KC_COMM),
        MEH(KC_SCLN), LCAG(KC_SPC), KC_NO   , KC_NO   , LGUI(KC_SPC), LGUI(KC_1), LGUI(KC_2), MEH(KC_LEFT), MEH(KC_DOWN), MEH(KC_RIGHT)
    ),
    // NAV
    [2] = LAYOUT(
        SPAD , AR_1 , AR_2 , AR_3 , AR_4 ,  AR_5  , AR_6      , AR_LW    , AR_RW  , KC_NO  , KC_NO, KC_NO,
        KC_NO, TMUX1, TMUX2, TMUX3, TMUX4, TMUX5  , KC_LEFT   , KC_DOWN  , KC_UP  , KC_RGHT, TMUXS,
        KC_NO, G1   , G2   , G3   , G4   , KC_HOME, KC_PGDN   , KC_PGUP  , KC_END , TMUXC  , KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          A(KC_MINS), A(KC_EQL), KC_NO  , KC_NO  , KC_NO
    ),
    // MOUSE
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    // NUM
    [4] = LAYOUT(
        KC_NO, KC_LBRC, KC_1 , KC_2   , KC_3 , KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_SCLN, KC_4 , KC_5   , KC_6 , KC_EQL , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_GRV , KC_7 , KC_8   , KC_9 , KC_BSLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO  , KC_0, KC_MINS, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    // SYM
    [5] = LAYOUT(
        KC_NO, KC_LCBR, KC_EXLM, KC_AT  , KC_HASH, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_COLN, KC_DLR , KC_PERC, KC_CIRC, KC_PLUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_TILD, KC_AMPR, KC_ASTR, KC_LPRN, KC_PIPE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO  , KC_RPRN, KC_UNDS, KC_NO  ,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    // FN
    [6] = LAYOUT(
        KC_NO, KC_1 , KC_2 , KC_3 , KC_4 , KC_5 , KC_6 , KC_7 , KC_8 , KC_9 , KC_0 , KC_NO,
        KC_NO, KC_4 , KC_5 , KC_6 , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_7 , KC_8 , KC_9 , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
};

const uint16_t PROGMEM combo_bootloader[] = {KC_TAB, KC_BSPC, COMBO_END};

const uint16_t PROGMEM combo_bf[] = {KC_B, KC_F, COMBO_END};
const uint16_t PROGMEM combo_bg[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM combo_cd[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_df[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_dfs[] = {KC_D, KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM combo_ds[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM combo_dv[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM combo_ed[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo_ef[] = {KC_E, KC_F, COMBO_END};
const uint16_t PROGMEM combo_fg[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo_fr[] = {KC_F, KC_R, COMBO_END};
const uint16_t PROGMEM combo_fs[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM combo_fv[] = {KC_F, KC_V, COMBO_END};
const uint16_t PROGMEM combo_fw[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM combo_gt[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM combo_ij[] = {KC_I, KC_J, COMBO_END};
const uint16_t PROGMEM combo_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_jkl[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_jl[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM combo_jn[] = {KC_J, KC_N, COMBO_END};
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_kn[] = {KC_K, KC_N, COMBO_END};
const uint16_t PROGMEM combo_sv[] = {KC_S, KC_V, COMBO_END};

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

const uint16_t PROGMEM combo_as[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_zx[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_xc[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_cv[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_shftz[] = {KC_LSFT, KC_Z, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_bootloader, QK_BOOT),
    COMBO(combo_as, G(KC_A)),
    COMBO(combo_df, G(KC_F)),
    COMBO(combo_shftz, G(KC_Z)),
    COMBO(combo_zx, G(KC_X)),
    COMBO(combo_xc, G(KC_C)),
    COMBO(combo_cv, G(KC_V)),
};

