#pragma once

#define MAIN_SOUND E__NOTE(_B6), E__NOTE(_GS7), S__NOTE(_REST), Q__NOTE(_E7)

#define STARTUP_SONG SONG(NO_SOUND)
#define DEFAULT_LAYER_SONGS { \
    SONG(MAIN_SOUND), \
    SONG(QWERTY_SOUND) \
}

#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE
#define FORCE_NKRO

/*
    Deprecated features
*/
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#undef RGBLIGHT_ANIMATIONS

/*
    Preonic V3 LEDs

    Default Layout:
        +---------------+
        |  6  5   4  3  |
        |       0       |
        |  7  8   1  2  |
        +-----[spc]-----+

    LED Mode 1 (9 lights)
        +---------------+
        |  6  5   3  2  |
        |       9       |
        |  7  8   0  1  |
        +-----[spc]-----+

    LED Mode 2 (7 lights)
        +---------------+
        |  6  5   3  2  |
        |       4       |
        |  7         1  |
        +-----[spc]-----+
*/

#undef RGBLED_NUM
#undef USE_CIE1931_CURVE

#define RGBLED_NUM 18
#define RGBLIGHT_LED_MAP { 9, 0, 1, 2, 3, 5, 6, 7, 8, \
                           4, 0, 1, 2, 3, 5, 6, 7, 8  }

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST

#if defined USER_DEBUG_RGB
    /*
        Debug mode:
        - 32 hue ticks, wrap around
        - Smaller sat, val increments (15 multiples of 17)
            17  34  51  68  85
            102 119 136 153 170
            187 204 221 238 255
    */
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#else
    /*
        Regular mode:
        - 16 hue ticks, wrap around
        - Larger sat, val increments (5 multiples of 51)
            51 102 153 204 255
    */
    #define RGBLIGHT_HUE_STEP 16
    #define RGBLIGHT_SAT_STEP 51
    #define RGBLIGHT_VAL_STEP 51
#endif

#define RGBLIGHT_DEFAULT_HUE 0
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_DEFAULT_VAL 255

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
