#include QMK_KEYBOARD_H

#include "user_defines.h"

void keyboard_pre_init_user(void) {
    eeconfig_disable();
}

void keyboard_post_init_user(void) {
    #if defined RGBLIGHT_ENABLE
        extern const rgblight_segment_t* const PROGMEM my_rgb_layers[];
        rgblight_layers = my_rgb_layers;
        rgblight_set_clipping_range(0, 9);
        rgblight_set_effect_range(0, 10);
        rgblight_mode(RGBLIGHT_DEFAULT_MODE);
    #endif // defined RGBLIGHT_ENABLE
}

layer_state_t default_layer_state_set_user(const layer_state_t state) {
    #if defined AUDIO_ENABLE && defined DEFAULT_LAYER_SONGS
        extern float default_layer_songs[][16][2];
        if (layer_state_cmp(state, _MAIN)) {
            PLAY_SONG(default_layer_songs[_MAIN]);
        }
        else if (layer_state_cmp(state, _QWER)) {
            PLAY_SONG(default_layer_songs[_QWER]);
        }
    #endif // defined AUDIO_ENABLE && defined DEFAULT_LAYER_SONGS
    return state;
}

layer_state_t update_quad_layer_state(const layer_state_t state, const uint8_t layer_x, const uint8_t layer_y, const uint8_t layer_and, const uint8_t layer_or) {

    const layer_state_t status_x = 1UL & (state >> layer_x);
    const layer_state_t status_y = 1UL & (state >> layer_y);

    const layer_state_t mask_or  = 1UL << layer_or;
    const layer_state_t mask_and = 1UL << layer_and;

    return (status_x & status_y) ?                               state |     mask_and   |  mask_or
                                 : ( (status_x | status_y) ? ( ( state & ~   mask_and ) |  mask_or   )
                                                           : (   state & ~ ( mask_and   |  mask_or ) ) );
}

layer_state_t layer_state_set_user(const layer_state_t state) {

    const layer_state_t state_updated = update_quad_layer_state(state, _LWR, _RSE, _LR_AND, _LR_OR);

    #if defined RGBLIGHT_ENABLE
        rgblight_set_layer_state(0, layer_state_cmp(state_updated, _LWR));
        rgblight_set_layer_state(1, layer_state_cmp(state_updated, _RSE));
        rgblight_set_layer_state(2, layer_state_cmp(state_updated, _LR_AND));
        rgblight_set_layer_state(3, layer_state_cmp(state_updated, _BLOCK));
        rgblight_set_layer_state(4, layer_state_cmp(state_updated, _RESET));
    #endif // defined RGBLIGHT_ENABLE

    return state_updated;
}

bool process_record_user(const uint16_t keycode, keyrecord_t* const record) {
    switch (keycode) {

        case MO_LWR:
            if (record->event.pressed) {
                layer_on(_LWR);
            } else {
                layer_off(_LWR);
            }
            return false;

        case MO_RSE:
            if (record->event.pressed) {
                layer_on(_RSE);
            } else {
                layer_off(_RSE);
            }
            return false;

        case MO_RESET:
            if (record->event.pressed) {
                layer_on(_RESET);
            } else {
                layer_off(_RESET);
            }
            return false;

        case MO_UNBLOCK:
            if (record->event.pressed) {
                layer_on(_UNBLOCK);
            } else {
                layer_off(_UNBLOCK);
            }
            return false;

        case LED_MODE:
            if (!record->event.pressed) {
                if (rgblight_ranges.clipping_start_pos != 0) {
                    rgblight_set_clipping_range(0, 9);
                    rgblight_set_effect_range(0, 10);
                }
                else {
                    rgblight_set_clipping_range(9, 9);
                    rgblight_sethsv_at(0, 0, 0, 0);
                    rgblight_sethsv_at(0, 0, 0, 8);
                    rgblight_set_effect_range(1, 7);
                }
            }
            return false;

        case KC_SHOW_ALL_WINDOWS:
            if (record->event.pressed) {
                host_consumer_send(AC_SHOW_ALL_WINDOWS);
            } else {
                host_consumer_send(0);
            }
            return false;

        case KC_SHOW_ALL_APPS:
            if (record->event.pressed) {
                host_consumer_send(AC_SHOW_ALL_APPS);
            } else {
                host_consumer_send(0);
            }
            return false;

        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAIN] = LAYOUT_MAIN,

    [_QWER] = LAYOUT_QWERTY,
    
    [_LR_OR] = LAYOUT_preonic_1x2uC(
        KC_BSPC,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_EQL,
        KC_ENT,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_F11,     KC_F12,     KC_DEL,
        KC_GRV,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_TAB,
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_LBRC,    KC_RBRC,    KC_BSLS,    _______,
        _______,    _______,    _______,    KC_IME_ON,  _______,        XXXXXXX,            _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END
    ),

    [_LWR] = LAYOUT_preonic_1x2uC(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    KC_HOME,    KC_UP,      KC_END,     KC_PGUP,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    KC_VOLD,    KC_VOLU,    KC_PSCR,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,        _______,            _______,    _______,    _______,    _______,    _______
    ),

    [_RSE] = LAYOUT_preonic_1x2uC(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_PAUS,    KC_CAPS,    KC_NUM,     KC_SCRL,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,        _______,            _______,    _______,    _______,    _______,    _______
    ),

    [_LR_AND] = LAYOUT_preonic_1x2uC(
        TO(_BLOCK), DB_TOGG,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    LED_MODE,
        MO_RESET,   DF(_MAIN),  DF(_QWER),  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    RGB_SAD,    RGB_VAI,    RGB_SAI,    RGB_TOG,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    RGB_HUD,    RGB_VAD,    RGB_HUI,    RGB_M_SW,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    RGB_RMOD,   RGB_MOD,    RGB_M_P,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        XXXXXXX,            _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
    ),

    [_RESET] = LAYOUT_preonic_1x2uC(
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    RESET,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        XXXXXXX,            _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
    ),

    [_BLOCK] = LAYOUT_preonic_1x2uC(
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    MO_UNBLOCK,     XXXXXXX,            MO_UNBLOCK, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
    ),

    [_UNBLOCK] = LAYOUT_preonic_1x2uC(
        TG(_BLOCK), XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        XXXXXXX,            _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
    )

};
