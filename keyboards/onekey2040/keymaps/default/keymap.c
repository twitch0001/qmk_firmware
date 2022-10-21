#include QMK_KEYBOARD_H

enum {_BASE, _LOWER};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌──────────────────────────────────────────────┐
     * │   _LOWER   │    C    │     B     │     A     │
     * └──────────────────────────────────────────────┘
     */
    [_BASE] = LAYOUT_ortho_1x4 (
       MO(_LOWER), QK_BOOT, DEBUG, KC_A
    ),
    [_LOWER] = LAYOUT_ortho_1x4 (
        _______, KC_3, KC_2, KC_1
    ),

};

const char *current_layer_string(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            return "base";
        case _LOWER:
            return "lower";
    }
    return "unknown";
}


typedef struct {
    double h;
    double s;
    double v;
} hsv;

hsv current_layer_colour(void) {
    hsv out;
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            out.h = 0;
            out.s = 0;
            out.v = 3;
            return out;
        case _LOWER:
            out.h = 19.13;
            out.s = 255;
            out.v = 191.25;
            return out;
    }
    out.h = 0;
    out.s = 0;
    out.v = 3;
    return out;
}
