#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"



enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  RGB_FF0000,
  RGB_0000FF,
  RGB_800080
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   |   1  |   2  |   3  |   4  |   5  | DEL  |           |      |   6  |   7  |   8  |   9  |   0  |  BS    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Bspace |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |;     | Enter  |
 * |--------+------+------+------+------+------|  L2  |           |  L2  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |/     | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl | Ins  |      |  Alt |Shift |                                       |Shift|      |   Up |  Dn  | TG3  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | <    |   >  |       | Home | Alt    |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | PgUp |       | End  |        |      |
 *                                 | Cmd  |Ctrl  |------|       |------|  LT1   |Enter |
 *                                 |      |      | PgDn |       | Tab  |        |      |
 *                                 `--------------------'       `----------------------'
 */


  [0] = LAYOUT_ergodox(
               /* 左手 */
               KC_ESCAPE,         KC_1, KC_2, KC_3, KC_4, KC_5, KC_DELETE,
               KC_TAB,            KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO,
               LCTL(KC_RBRACKET), KC_A, KC_S, KC_D, KC_F, KC_G,
               KC_LSHIFT,         KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO,

               KC_LCTL, KC_NO,   KC_NO,   KC_LALT, KC_LALT,

               KC_HOME,        KC_END,
               KC_PGUP,
               KC_LGUI, LT(2,     KC_SPACE),  KC_PGDOWN,

               /* 右手 */
               KC_F1, KC_6, KC_7, KC_8,     KC_9,      KC_0,     KC_BSPACE,
               KC_NO, KC_Y, KC_U, KC_I,     KC_O,      KC_P,     KC_NO,
               KC_H,  KC_J, KC_K, KC_L,     KC_SCOLON, KC_ENTER,
               KC_NO, KC_N, KC_M, KC_COMMA, KC_DOT,    KC_SLASH, KC_RSHIFT,

               KC_RSHIFT,      KC_UP,  KC_DOWN, TG(1),    TG(2),

               KC_LEFT, KC_RIGHT,
               KC_NO,
               LGUI(KC_SPACE),  KC_LCTL,     LT(1,     KC_SPACE)  ), /* ime切り替え、右CTRL、スペース（長押しでL1） */

/* layer0
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |  -   |  =   |  [    |   ]  |  \   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|  _   |  +   |  {   |    } |   |  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |  "   |  '   |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |     |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */



  [1] = LAYOUT_ergodox(
               /* 左手 */
               KC_TRANSPARENT, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3)/*#*/, LSFT(KC_4)/*$*/, LSFT(KC_5)/*%*/, RESET,
               KC_TRANSPARENT, KC_MINUS,   KC_7,       KC_8,       KC_9,                  KC_TILD,         KC_TRANSPARENT,
               KC_BSPACE,      KC_KP_PLUS, KC_4,       KC_5,       KC_6,                  KC_KP_ASTERISK,
               KC_TRANSPARENT, KC_EQUAL,   KC_1,       KC_2,       KC_3,                  KC_GRAVE,        KC_SLASH,

               KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_DOT, KC_0,
               RGB_MOD,        RGB_FF0000,
               RGB_0000FF,
               KC_TRANSPARENT, KC_TRANSPARENT, RGB_800080,

               /* 右手 */
               KC_TRANSPARENT, LSFT(KC_6),          LSFT(KC_7),          LSFT(KC_8),          LSFT(KC_9),          LSFT(KC_0),         KC_F1,
               KC_TRANSPARENT, KC_MINUS,       KC_EQUAL,       KC_LBRACKET,    KC_RBRACKET,    KC_BSLASH,      KC_F12,
                               KC_UNDS,        KC_KP_PLUS,     KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,
               KC_TRANSPARENT, KC_QUOTE,       KC_DQUO,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

               KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
               RGB_TOG,        RGB_SLD,
               KC_TRANSPARENT,
               KC_TRANSPARENT, RGB_HUD,        RGB_HUI),

  /* テンキー
   */
  [2] = LAYOUT_ergodox(
               /* 左手 */
               KC_TRANSPARENT,        KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
               KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
               KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
               KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

               KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,
               KC_TRANSPARENT, KC_TRANSPARENT,
               KC_TRANSPARENT,
               KC_TRANSPARENT,        KC_TRANSPARENT, KC_TRANSPARENT,

               /* 右手 */
               KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_SLASH,  LSFT(KC_8),  KC_TRANSPARENT,  KC_BSPACE,
               KC_HOME,  KC_TRANSPARENT,  KC_7,            KC_8,      KC_9,        KC_MINUS,        KC_TRANSPARENT,
                                KC_PGUP,  KC_4,            KC_5,      KC_6,        KC_KP_PLUS,      KC_ENTER,
               KC_END,  KC_PGDOWN,  KC_1,            KC_2,      KC_3,        KC_TRANSPARENT,  KC_TRANSPARENT,

               KC_0, KC_DOT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,

               KC_TRANSPARENT, KC_TRANSPARENT,
               KC_TRANSPARENT,
               KC_TRANSPARENT, KC_TRANSPARENT, KC_LALT),

  /*
  [3] = KEYMAP(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,


               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,


               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,
               KC_TRANSPARENT,
               KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),
  */

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;

    case RGB_FF0000:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0xff,0x00,0x00);
        #endif
      }
      return false;
      break;

    case RGB_0000FF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x00,0x00,0xff);
        #endif
      }
      return false;
      break;

    case RGB_800080:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x80,0x00,0x80);
        #endif
      }
      return false;
      break;

  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
#ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x00,0x00,0x00);
#endif
        break;
      case 1:
        //ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
#ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x00,0x00,0xff);
#endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
#ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x00,0xff,0x00);
#endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }
    return state;

};


/* テンプレート
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |     |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
