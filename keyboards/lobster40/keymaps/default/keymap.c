#include QMK_KEYBOARD_H

LEADER_EXTERNS();


enum layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FUNC,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define FUNC   MO(_FUNC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌──────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │ ESC  │   Q   │   W   │   E   │   R   │   T   │   Y   │   U   │   I   │   O   │   P   │  BKSP │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │ TAB  │   A   │   S   │   D   │   F   │   G   │   H   │   J   │   K   │   L   │   ;   │ ENTER │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │LSHIFT│   Z   │   X   │   C   │   V   │   B   │   N   │   M   │   ,   │   .   │   /   │  '    │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │  FN  │ CTRL  │  ALT  │  WIN  │ LOWER │ SPACE │ LEAD  │ RAISE │  LEFT │  DOWN │ UP    │ RIGH  │
     * └──────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_ENTER,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,    KC_DOT,    KC_SLSH,    KC_QUOT,
        FUNC,    KC_LCTL,    KC_LALT,    KC_LGUI,    LOWER,    KC_SPC,    QK_LEAD,    RAISE,    KC_LEFT,    KC_DOWN,    KC_UP ,    KC_RGHT
    ),
    /*
     * ┌──────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │ ESC  │   Q   │   W   │   E   │   R   │   T   │   Y   │   U   │   I   │   O   │   P   │  BOOT │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │ TAB  │   A   │   S   │   D   │   F   │   G   │   H   │   J   │   K   │   L   │       │ ENTER │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │LSHIFT│   Z   │   X   │   C   │   V   │   B   │   N   │   M   │       │       │       │  BKSP │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │      │       │       │       │       │       │       │       │       │       │       │  BKSP │
     * └──────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [_LOWER] = LAYOUT_ortho_4x12(
        PB_1,    DB_TOGG,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    QK_BOOT,
        PB_2,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_K,    KC_ENTER,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_NUBS,    KC_B,    KC_N,    KC_M,    KC_I,    KC_J,    KC_K,    KC_L,
         _______,    _______,    _______,    _______,    _______,    _______,   _______,    _______,   _______,    _______,   _______,    KC_LCTL
    ),
    /*
     * ┌──────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │  `   │       │   [   │   ]   │       │       │       │       │       │       │       │  DEL  │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │ TAB  │   A   │   (   │   )   │   F   │   G   │   H   │   J   │   K   │   L   │       │  HOME │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │LSHIFT│   Z   │   X   │   C   │   V   │   B   │   N   │   M   │       │       │       │  BKSP │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │      │       │       │       │       │       │       │       │       │       │       │  BKSP │
     * └──────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_GRV ,    _______,    KC_LBRC,    KC_RBRC,    _______,    _______,   _______,    _______,    _______,    _______,  _______,    KC_DEL  ,
        _______,    _______,    KC_LPRN,    KC_RPRN,    _______,    _______,   _______,    _______,    _______,    _______,  _______,    KC_HOME,
        _______,    _______,    KC_LCBR,    KC_RCBR,    _______,    _______,   _______,    _______,    _______,    _______,  _______,    KC_L    ,
        _______,    _______,    _______,    _______,    _______,    _______,   _______,    _______,   _______,    _______,   _______,    KC_LCTL
    ),
    /*
     * ┌──────┬───────┬───────┬──────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │ ESC  │   Q   │   W   │  E   │   R   │   T   │   Y   │   U   │   I   │   O   │   P   │  BOOT │
     * ├──────┼───────┼───────┼──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │ TAB  │   A   │   S   │  D   │   F   │   G   │   H   │   J   │   K   │   L   │       │ ENTER │
     * ├──────┼───────┼───────┼──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │LSHIFT│   Z   │   X   │  C   │   V   │   B   │   N   │   M   │       │       │       │  BKSP │
     * ├──────┼───────┼───────┼──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │      │       │       │      │       │       │       │       │       │       │       │  BKSP │
     * └──────┴───────┴───────┴──────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [_FUNC] = LAYOUT_ortho_4x12(
        KC_F1  , KC_F2  , KC_F3   , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12,
        KC_1   , KC_2   , KC_3    , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, _______,
        _______, KC_PIPE, KC_GRAVE, KC_NUHS, KC_ASTR, KC_MINS, KC_EQL , KC_PIPE, _______, _______, KC_QUOT, _______,
        _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};


const char *current_layer_string(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            return "base";
        case _LOWER:
            return "lower";
         case _RAISE:
            return "raise";
         case _FUNC:
            return "function";
        case _ADJUST:
            return "adjust";
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
        case _QWERTY:
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


void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_TWO_KEYS(KC_L, KC_F) {
        register_code(KC_NONUS_BACKSLASH);
        unregister_code(KC_NONUS_BACKSLASH);
        SEND_STRING("frac{");
    }
  }
}
