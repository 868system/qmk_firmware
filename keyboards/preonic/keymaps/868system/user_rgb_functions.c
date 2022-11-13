#include QMK_KEYBOARD_H

#if defined RGBLIGHT_ENABLE

typedef struct {
    uint16_t r;
    uint16_t g;
    uint16_t b;
} rgb16_t;

typedef struct {
    uint16_t h;
    uint16_t s;
    uint16_t v;
} hsv16_t;

/*
    Note: a and b are [0.0,1.0) real ranges represented as [0,65536) integers
*/
inline uint16_t mult(const uint16_t a, const uint16_t b) {
    const uint32_t result = a * b;
    return (uint16_t)(result >> 16);
}

/*
    Internal 16-bit HSV to RGB computation (final output is still 8-bit)
*/
rgb16_t rgblight_hsv16_to_rgb16(const hsv16_t hsv16) {

    const uint16_t hue = hsv16.h;
    const uint16_t sat = hsv16.s;
    const uint16_t val = hsv16.v;

    /*
        sector  = hue / (65536/6)
        offset  = 6 * (hue - (sector * (65536/6)))
        65536/6 = 10922
    */
    const uint16_t sector = (uint32_t)hue * 3 >> 15;

    /*
        Odd sectors count the offset from the other end
    */
    const uint16_t offset_raw = 6 * (hue - (sector * 10922));
    const uint16_t offset = (sector & 1) == 1 ? ~offset_raw : offset_raw;

    /*
        65535 * cos(45)       = 46340
        65535 * (1 - cos(45)) = 19195;
    */
    const uint16_t high = mult(val, ~sat + mult(sat, ~mult(offset, 19195)));
    const uint16_t mid  = mult(val, ~sat + mult(sat,  mult(offset, 46340)));
    const uint16_t low  = mult(val, ~sat                                  );

    switch (sector) {
        case 0:  return (rgb16_t) { .r = high, .g = mid,  .b = low  };
        case 1:  return (rgb16_t) { .r = mid,  .g = high, .b = low  };
        case 2:  return (rgb16_t) { .r = low,  .g = high, .b = mid  };
        case 3:  return (rgb16_t) { .r = low,  .g = mid,  .b = high };
        case 4:  return (rgb16_t) { .r = mid,  .g = low,  .b = high };
        case 5:  return (rgb16_t) { .r = high, .g = low,  .b = mid  };
        default: return (rgb16_t) { .r = 0,    .g = 0,    .b = 0    };
    }
}

hsv16_t preprocess_16(const hsv16_t hsv16) {
    #if defined USER_CONVERT_RYGB
        /*
            Map RGB radial values to RYGB
        */
        const hsv16_t result = (hsv16_t) {
            .h = (hsv16.h < 32768) ? hsv16.h * 2 / 3                    // Warm Arc (RYG)
                                   : 21846 + (hsv16.h - 32768) * 4 / 3, // Cool Arc (GBR)
            .s = hsv16.s,
            .v = hsv16.v
        };
        return result;
    #else
        return hsv16;
    #endif // defined USER_CONVERT_RYGB
}

rgb16_t postprocess_16(const rgb16_t rgb16) {
    /*
        Simple white point: multiply Green by 2/3, and Blue by 1/2
    */
    const rgb16_t result = (rgb16_t) {
        .r = rgb16.r,
        .g = rgb16.g * 2 / 3,
        .b = rgb16.b / 2
    };
    return result;
}

RGB rgblight_hsv_to_rgb(const HSV hsv) {

    /*
        Bypass -- uncomment this if needed
    */
    // return hsv_to_rgb(hsv);

    /*
        Special case when hsv.v is zero
    */
    if (hsv.v == 0) {
        return (RGB) {
            .r = 0,
            .g = 0,
            .b = 0
        };
    }

    /*
        Stretch precision of input from 8-bit to 16-bit
    */
    const hsv16_t hsv16 = (hsv16_t) {
        .h = hsv.h << 8,
        .s = hsv.s << 8,
        .v = hsv.v << 8
    };

    const rgb16_t rgb16 = postprocess_16(
                          rgblight_hsv16_to_rgb16(
                          preprocess_16(hsv16)));

    return (RGB) {
        .r = rgb16.r >> 8,
        .g = rgb16.g >> 8,
        .b = rgb16.b >> 8
    };
}

#endif // defined RGBLIGHT_ENABLE
