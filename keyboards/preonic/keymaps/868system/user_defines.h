#pragma once

/*
    Windows 10 new Japanese IME key names
    https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/keyboard-japan-ime
*/
#define KC_IME_ON  KC_LNG1 // also Japanese Macintosh "かな" "Kana"
#define KC_IME_OFF KC_LNG2 // also Japanese Macintosh "英数" "Eisuu"

/*
    Macintosh Mission Control and Launchpad
*/
#define KC_MCON KC_SHOW_ALL_WINDOWS
#define KC_LPAD KC_SHOW_ALL_APPS

enum my_keycodes {
    MO_LWR = SAFE_RANGE,
    MO_RSE,
    MO_RESET,
    MO_UNBLOCK,
    LED_MODE,
    KC_SHOW_ALL_WINDOWS,
    KC_SHOW_ALL_APPS
};

/*
    https://usb.org/document-library/hid-usage-tables-122
*/
enum my_consumer_usages {
    AC_SHOW_ALL_WINDOWS = 0x29F,
    AC_SHOW_ALL_APPS    = 0x2A0
};

enum my_layers {
/* Typing layouts */
    _MAIN,
    _QWER,
/* Layered keys */
    _LR_OR,
    _LWR,
    _RSE,
    _LR_AND,
/* System operations */
    _RESET,
    _BLOCK,
    _UNBLOCK
};

/*
    Hue Names for HSV space
    Source: https://en.wikipedia.org/wiki/Tertiary_color

    This isn't accurate because the tertiary and some quaternary hue names
    were forced into 16 slots instead of the usual 12 ternary slots.
*/
#define HUE_RED           0 //  Primary
#define HUE_ORANGE       16 //      Ternary
#define HUE_YELLOW       32 //    Secondary
#define HUE_LIME         48 //        Quaternary
#define HUE_CHARTREUSE   64 //      Ternary
#define HUE_GREEN        80 //  Primary
#define HUE_SPRING       96 //      Ternary
#define HUE_AQUAMARINE  112 //        Quaternary
#define HUE_CYAN        128 //    Secondary
#define HUE_AZURE       144 //      Ternary
#define HUE_BLUE        160 //  Primary
#define HUE_INDIGO      176 //        Quaternary
#define HUE_VIOLET      192 //      Ternary
#define HUE_MAGENTA     208 //    Secondary
#define HUE_ROSE        224 //      Ternary
#define HUE_CRIMSON     240 //        Quaternary

/*
    Popular and standard keyboard layouts
*/

#define LAYOUT_MAIN LAYOUT_COLEMAK

#define LAYOUT_QWERTY LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P, \
                    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN, \
                    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_QWERTY_LP LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_SCLN, \
                    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_P, \
                    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_DVORAK LAYOUT_preonic_wrapper( \
                    KC_SLSH,    KC_COMM,    KC_DOT,     KC_P,       KC_Y,       KC_F,       KC_G,       KC_C,       KC_R,       KC_L, \
                    KC_A,       KC_O,       KC_E,       KC_U,       KC_I,       KC_D,       KC_H,       KC_T,       KC_N,       KC_S, \
                    KC_SCLN,    KC_Q,       KC_J,       KC_K,       KC_X,       KC_B,       KC_M,       KC_W,       KC_V,       KC_Z )

#define LAYOUT_QGMLWY LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_G,       KC_M,       KC_L,       KC_W,       KC_Y,       KC_F,       KC_U,       KC_B,       KC_SCLN, \
                    KC_D,       KC_S,       KC_T,       KC_N,       KC_R,       KC_I,       KC_A,       KC_E,       KC_O,       KC_H, \
                    KC_Z,       KC_X,       KC_C,       KC_V,       KC_J,       KC_K,       KC_P,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_COLEMAK LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN, \
                    KC_A,       KC_R,       KC_S,       KC_T,       KC_D,       KC_H,       KC_N,       KC_E,       KC_I,       KC_O, \
                    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_K,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_COLEMAK_DH LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN, \
                    KC_A,       KC_R,       KC_S,       KC_T,       KC_G,       KC_M,       KC_N,       KC_E,       KC_I,       KC_O, \
                    KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_COLEMAK_DHK LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN, \
                    KC_A,       KC_R,       KC_S,       KC_T,       KC_G,       KC_K,       KC_N,       KC_E,       KC_I,       KC_O, \
                    KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       KC_M,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_COLEMAK_DPGH LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_W,       KC_F,       KC_D,       KC_P,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN, \
                    KC_A,       KC_R,       KC_S,       KC_T,       KC_G,       KC_M,       KC_N,       KC_E,       KC_I,       KC_O, \
                    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_COLEMAK_DPGHK LAYOUT_preonic_wrapper( \
                    KC_Q,       KC_W,       KC_F,       KC_D,       KC_P,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN, \
                    KC_A,       KC_R,       KC_S,       KC_T,       KC_G,       KC_K,       KC_N,       KC_E,       KC_I,       KC_O, \
                    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_M,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH )

#define LAYOUT_preonic_wrapper( \
                    P_00,       P_01,       P_02,       P_03,       P_04,       P_05,       P_06,       P_07,       P_08,       P_09, \
                    P_10,       P_11,       P_12,       P_13,       P_14,       P_15,       P_16,       P_17,       P_18,       P_19, \
                    P_20,       P_21,       P_22,       P_23,       P_24,       P_25,       P_26,       P_27,       P_28,       P_29 \
    ) \
    LAYOUT_preonic_1x2uC( \
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS, \
        KC_TAB,     P_00,       P_01,       P_02,       P_03,       P_04,       P_05,       P_06,       P_07,       P_08,       P_09,       KC_BSPC, \
        KC_QUOT,    P_10,       P_11,       P_12,       P_13,       P_14,       P_15,       P_16,       P_17,       P_18,       P_19,       KC_ENT, \
        KC_LSFT,    P_20,       P_21,       P_22,       P_23,       P_24,       P_25,       P_26,       P_27,       P_28,       P_29,       KC_RSFT, \
        KC_LCTL,    KC_LALT,    KC_LGUI,    KC_IME_OFF, MO_LWR,         KC_SPC,             MO_RSE,     KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT )
