#include QMK_KEYBOARD_H

#include "user_defines.h"

#if defined RGBLIGHT_ENABLE

#define RGBLIGHT_LAYER(HUE, SAT) \
        RGBLIGHT_LAYER_SEGMENTS( \
            {4, 1, HUE, SAT, 255}, \
            {2, 2, HUE, SAT, 255}, \
            {5, 2, HUE, SAT, 255})

const rgblight_segment_t PROGMEM rgb_RESET[]  = RGBLIGHT_LAYER(HUE_RED, 255);
const rgblight_segment_t PROGMEM rgb_BLOCK[]  = RGBLIGHT_LAYER(HUE_MAGENTA, 255);
const rgblight_segment_t PROGMEM rgb_LR_AND[] = RGBLIGHT_LAYER(0, 0);
const rgblight_segment_t PROGMEM rgb_RSE[]    = RGBLIGHT_LAYER(HUE_ORANGE, 255);
const rgblight_segment_t PROGMEM rgb_LWR[]    = RGBLIGHT_LAYER(HUE_AZURE, 255);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_LWR,
    rgb_RSE,
    rgb_LR_AND,
    rgb_BLOCK,
    rgb_RESET
);

#endif // defined RGBLIGHT_ENABLE
