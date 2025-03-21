// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define NDEF KC_NO

#define MOD_A LGUI_T(KC_A)
#define MOD_S LALT_T(KC_S)
#define MOD_D LCTL_T(KC_D)
#define MOD_F LSFT_T(KC_F)

#define MOD_J LSFT_T(KC_J)
#define MOD_K LCTL_T(KC_K)
#define MOD_L LALT_T(KC_L)
#define MOD_QUOT LGUI_T(KC_QUOT)

#define L_MED(KC) LT(1, KC)
#define L_NAV(KC) LT(2, KC)
#define L_MSE(KC) LT(3, KC)
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
#define AR_ACC LCA(KC_SLSH)
#define AR_TIL LCA(KC_COMM)
#define OPWD   G(A(KC_BSLS))

#define SPAD A(KC_SPC)

#define MAC_SLP C(G(KC_Q))

#define KC_G1 G(KC_1)
#define KC_G2 G(KC_2)
#define KC_G3 G(KC_3)
#define KC_G4 G(KC_4)
#define KC_G5 G(KC_5)
#define KC_G6 G(KC_6)
#define KC_G7 G(KC_7)
#define KC_G8 G(KC_8)
#define KC_G9 G(KC_9)

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
    TMUX7,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #define KEYCORD(...) do { \
        uint16_t t[] = { __VA_ARGS__ }; \
        if (record->event.pressed) { \
            for (int i = 0; i < sizeof t / sizeof t[0]; i++) { \
                tap_code16(t[i]); \
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
    case TMUX7:
        KEYCORD(A(KC_M), KC_7);
        return false;
    default:
        return true;
    }
    return true;
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', '*', '*', '*', 'L',  'R', '*', '*', '*', 'R', 'R', 'R'
    );

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // QWERTY
    [0] = LAYOUT(
        KC_TAB, KC_Q , KC_W , KC_E          , KC_R         , KC_T         , NDEF      ,         NDEF , KC_Y         , KC_U         , KC_I         , KC_O  , KC_P    , QK_REP,
        KC_ESC, MOD_A, MOD_S, MOD_D         , MOD_F        , KC_G         , G(S(KC_V)),         SNPST, KC_H         , MOD_J        , MOD_K        , MOD_L , MOD_QUOT, KC_SCLN,
        QK_LLCK , KC_Z , KC_X , KC_C          , KC_V         , KC_B         , CW_TOGG   ,         OPWD , KC_N         , KC_M         , KC_COMM      , KC_DOT, KC_SLSH , QK_LLCK,
        NDEF  , NDEF , NDEF , L_MED(KC_BSPC), L_NAV(KC_SPC), L_MSE(KC_ENT), NDEF      ,         NDEF , L_SYM(KC_ENT), L_NUM(KC_SPC), L_FN(KC_DEL) , NDEF  , NDEF    , NDEF
    ),
    // MEDIA
    [1] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, NDEF ,         NDEF   , SNPST  , SNPST_REG, SNPST_VID, KC_NO  , KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO  , KC_MPRV, KC_VOLD  , KC_VOLU  , KC_MNXT, KC_NO, KC_NO,
        QK_LLCK , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         UG_TOGG, UG_NEXT, KC_NO    , KC_NO    , UG_PREV, KC_NO, QK_LLCK ,
        NDEF , NDEF , NDEF , KC_NO, KC_NO, KC_NO, NDEF ,         NDEF   , KC_MSTP, KC_MPLY  , KC_MUTE  , NDEF   , NDEF , NDEF
    ),
    // NAV
    [2] = LAYOUT(
        SPAD   , AR_1 , AR_2 , AR_3 , AR_4 , AR_5 , NDEF ,         NDEF , AR_6      , AR_LW    , AR_RW  , KC_NO  , KC_NO, KC_BSPC,
        KC_LALT, TMUX1, TMUX2, TMUX3, TMUX4, TMUX5, TMUX6,         TMUX7, KC_LEFT   , KC_DOWN  , KC_UP  , KC_RGHT, TMUXS, KC_NO,
        QK_LLCK, KC_G1, KC_G2, KC_G3, KC_G4, KC_G5, KC_NO,         KC_NO, KC_HOME   , KC_PGDN  , KC_PGUP, KC_END , TMUXC, QK_LLCK ,
        NDEF   , NDEF , NDEF , KC_NO, KC_NO, KC_NO, NDEF ,         NDEF , A(KC_MINS), A(KC_EQL), KC_NO  , NDEF   , NDEF , NDEF
    ),
    // MOUSE
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, NDEF ,         NDEF , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, MS_LEFT, MS_DOWN, MS_UP  , MS_RGHT, KC_NO, KC_NO,
        QK_LLCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, MS_WHLR, MS_WHLU, MS_WHLD, MS_WHLL, KC_NO, QK_LLCK,
        NDEF , NDEF , NDEF , KC_NO, KC_NO, KC_NO, NDEF ,         NDEF , MS_BTN2, MS_BTN1, MS_BTN3, NDEF   , NDEF , NDEF
    ),
    // NUM
    [4] = LAYOUT(
        KC_NO, KC_LBRC, KC_1, KC_2  , KC_3, KC_RBRC, NDEF ,         NDEF , KC_NO, KC_1 , KC_2, KC_3, KC_NO, KC_NO,
        KC_NO, KC_SCLN, KC_4, KC_5  , KC_6, KC_EQL , KC_NO,         KC_NO, KC_NO, KC_4 , KC_5, KC_6, KC_NO, KC_NO,
        QK_LLCK, KC_GRV , KC_7, KC_8  , KC_9, KC_BSLS, KC_NO,         KC_NO, KC_NO, KC_7 , KC_8, KC_9, KC_NO, QK_LLCK,
        NDEF , NDEF   , NDEF, KC_DOT, KC_0, KC_MINS, NDEF ,         NDEF , KC_NO, KC_NO, KC_0, NDEF, NDEF , NDEF
    ),
    // SYM
    [5] = LAYOUT(
        KC_LALT, KC_LCBR, KC_EXLM, KC_AT  , KC_HASH, KC_RCBR, NDEF ,         NDEF , KC_LCBR, KC_EXLM, KC_AT  , KC_HASH, KC_RCBR, KC_NO,
        KC_NO  , KC_COLN, KC_DLR , KC_PERC, KC_CIRC, KC_PLUS, KC_NO,         KC_NO, KC_COLN, KC_DLR , KC_PERC, KC_CIRC, KC_PLUS, KC_NO,
        QK_LLCK  , KC_TILD, KC_AMPR, KC_ASTR, KC_LPRN, KC_PIPE, KC_NO,         KC_NO, KC_TILD, KC_AMPR, KC_ASTR, KC_LPRN, KC_PIPE, QK_LLCK,
        NDEF   , NDEF   , NDEF   , KC_LPRN, KC_RPRN, KC_UNDS, NDEF ,         NDEF , KC_NO  , KC_NO  , KC_NO  , NDEF   , NDEF   , NDEF
    ),
    // FN
    [6] = LAYOUT(
        QK_REP , KC_F10, KC_F1, KC_F2, KC_F3, KC_F10, NDEF  ,       NDEF   , DM_REC1, DM_REC2, KC_NO, KC_NO, KC_NO, MAC_SLP,
        QK_AREP, KC_F11, KC_F4, KC_F5, KC_F6, KC_F11, AR_ACC,       DM_PLY1, DM_RSTP, KC_NO  , KC_NO, KC_NO, KC_NO, KC_NO,
        QK_BOOT, KC_F12, KC_F7, KC_F8, KC_F9, KC_F12, AR_TIL,       DM_PLY2, KC_NO  , KC_NO  , KC_NO, KC_NO, KC_NO, QK_BOOT,
        NDEF   , NDEF  , NDEF , KC_NO, KC_NO, KC_NO , NDEF  ,       NDEF   , KC_NO  , KC_NO  , KC_NO, NDEF , NDEF , NDEF
    ),
};

#if defined(COMBO_ENABLE)
const uint16_t PROGMEM combo_fg[] = {KC_G, MOD_F, COMBO_END};
const uint16_t PROGMEM combo_as[] = {MOD_A, MOD_S, COMBO_END};
const uint16_t PROGMEM combo_zx[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_xc[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_cv[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_vb[] = {KC_V, KC_B, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_as, LGUI(KC_A)),
    COMBO(combo_fg, LGUI(KC_F)),
    COMBO(combo_zx, LGUI(KC_Z)),
    COMBO(combo_xc, LGUI(KC_X)),
    COMBO(combo_cv, LGUI(KC_C)),
    COMBO(combo_vb, LGUI(KC_V)),
};
#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)  },
    [1] = { ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [2] = { ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)  },
    [3] = { ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)  },
    [4] = { ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)  },
    [5] = { ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)  },
    [6] = { ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)  },
};
#endif
