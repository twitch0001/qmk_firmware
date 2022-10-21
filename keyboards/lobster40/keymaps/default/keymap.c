#include QMK_KEYBOARD_H

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
     * │  FN  │ CTRL  │  ALT  │  WIN  │ LOWER │ SPACE │ RAISE │ LEFT  │ DOWN  │   UP  │ RIGHT │ CTRL  │
     * └──────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_ENTER,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,    KC_DOT,    KC_SLSH,    KC_QUOT,
        FUNC,    KC_LCTL,    KC_LALT,    KC_LGUI,    LOWER,    KC_SPC,    _______,    RAISE,    KC_LEFT,    KC_DOWN,    KC_UP ,    KC_RGHT
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
        KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    QK_BOOT,
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_K,    KC_ENTER,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_NUBS,    KC_B,    KC_N,    KC_M,    KC_I,    KC_J,    KC_K,    KC_L,
        KC_A,    KC_LCTL,    KC_LALT,    KC_LGUI,    _______,    KC_SPC,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RGHT ,    KC_LCTL
    ),
    /*
     * ┌──────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     * │  `   │       │   [   │   ]   │       │       │       │       │       │       │       │  DEL  │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │ TAB  │   A   │   (   │   )   │   F   │   G   │   H   │   J   │   K   │   L   │       │ ENTER │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │LSHIFT│   Z   │   X   │   C   │   V   │   B   │   N   │   M   │       │       │       │  BKSP │
     * ├──────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼
     * │      │       │       │       │       │       │       │       │       │       │       │  BKSP │
     * └──────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
     */
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_GRV ,    _______,    KC_LBRC,    KC_RBRC,    _______,    _______,   _______,    _______,    _______,    _______,  _______,    KC_DEL  ,
        _______,    _______,    KC_LPRN,    KC_RPRN,    _______,    _______,   _______,    _______,    _______,    _______,  _______,    KC_ENTER,
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
