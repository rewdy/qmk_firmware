#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

// Tap dance declarations
enum { 
  TD_SHFT_CAPS
};

#define KC_LSFT_CAPS  TD(TD_SHFT_CAPS)

// Tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

/*
TODO: move right space over one, move special key to the first in R0. Figure out what to do with app keys.
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65_with_macro(
    KC_MUTE,            KC_ESC,   KC_GRV,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_DEL, \
    LSFT(KC_F1),        KC_BRIU,  KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_HOME, \
    LCTL(LCMD(KC_SPC)), KC_BRID,  KC_ESC,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,   KC_END, \
    LCMD(KC_LBRC),      KC_PGUP,  TD(TD_SHFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_UP,    TT(1), \
    LCMD(KC_R),         KC_PGDN,  KC_SPC,           KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,           KC_SPC,  KC_SPC,  KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  [_FN1] = LAYOUT_65_with_macro(
    _______,  _______,  RGB_TOG,  RGB_MODE_PLAIN,  RGB_MODE_BREATHE,  RGB_MODE_RAINBOW,  RGB_MODE_SWIRL,  RGB_MODE_SNAKE,  RGB_MODE_KNIGHT,  RGB_MODE_XMAS,  RGB_MODE_GRADIENT,  RGB_MODE_RGBTEST,   _______,   RGB_MODE_REVERSE,  RGB_MODE_FORWARD,  _______,  _______,  _______, \
    KC_F1,    KC_F2,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_P7,    KC_P8,    KC_P9,    _______,  _______,  _______, \
    KC_F3,    KC_F4,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_P4,    KC_P5,    KC_P6,    _______,  _______, \
    KC_F5,    KC_F6,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   KC_P1,    KC_P2,    KC_P3,    _______,  RGB_VAI,  _______, \
    KC_F7,    KC_F8,    _______,  _______,  _______,  _______,  _______,            _______,  KC_P0,     KC_PDOT,  RGB_SAD,  RGB_SAI,  RGB_HUD,  RGB_VAD,  RGB_HUI
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    // No need to check index since I only have one encoder
    if (IS_LAYER_ON(_FN1)) {
        if (clockwise) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
