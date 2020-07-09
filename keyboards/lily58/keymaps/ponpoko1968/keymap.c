#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE,
  LOWER,
  ADJUST,
  TGL_KANA

};

extern const char *read_mode_icon(bool swap);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    | kana  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,   KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,   KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,   KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
  KC_LCTRL,  KC_Z,   KC_X,   KC_C,    KC_V,   KC_B, LCTL(KC_RBRACKET), OSL(_LOWER),KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
  /*                   */MO(_LOWER), KC_LALT,  KC_LGUI, KC_LSFT,    TGL_KANA, LT(_RAISE,KC_SPACE),KC_RCTL, ADJUST \
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP|  RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
                  KC_TILD, KC_EXLM  , KC_AT    ,  KC_HASH   , KC_DLR  , KC_PERC ,                    KC_CIRC   , KC_AMPR , KC_ASTR  , KC_LPRN , KC_RPRN   , _______   , \
                  KC_F1  , KC_HOME ,  KC_UP ,     KC_EXLM   , KC_AT   , KC_TILDE,                    KC_MINS  ,  KC_EQL  , KC_LBRC ,  KC_RBRC , KC_BSLASH , KC_F12    , \
                  KC_F2  , KC_LEFT,   KC_DOWN,    KC_RIGHT,   KC_F4,    KC_F5 ,               KC_UNDS ,   KC_PLUS , KC_LCBR  , KC_RCBR , KC_COLN   , KC_PIPE    , \
                  KC_F3  , KC_END,    KC_F6,      KC_F7,      KC_F8,    KC_GRAVE, KC_PGUP, KC_BSPC,   KC_QUOT ,   KC_DQT  , KC_LT  ,   KC_GT   , KC_QUES ,   _______ , \
                                                KC_F9, KC_F10, _______, KC_PGDN, _______,  _______, _______, _______\
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |   7  |   8  |   9  |   (  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   4  |   5  |   6  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   1  |   2  |   3  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  \
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_MINUS,KC_7,    KC_8,    KC_9,   KC_LPRN, KC_F12, \
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_PLUS, KC_4,    KC_5,    KC_6,   KC_RPRN, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_EQL,  KC_SLSH, KC_1,    KC_2,    KC_3,   XXXXXXX, XXXXXXX, \
  /*                    */KC_TRNS, _______, _______, _______, KC_ASTR, LT(_RAISE,KC_0),  _______, KC_DOT \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_NORM,                   AG_SWAP, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool isControlPressed = false;

  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
  case KC_LCTL:
    if (record->event.pressed){
      isControlPressed = true;
    }
    else{
      isControlPressed = false;
    }
    break;
  case QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;
  case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_LOWER);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_RAISE);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case ADJUST:
    if (record->event.pressed) {
      layer_on(_ADJUST);
    } else {
      layer_off(_ADJUST);
    }
    return false;
    break;

  case KC_H:
    if (keymap_config.swap_lalt_lgui)  { /* windows */
      if (record->event.pressed && isControlPressed){
        unregister_code(KC_H);
        unregister_code(KC_LCTL);
        tap_code(KC_BSPC);
        register_code(KC_LCTL);
        return false;// keyrepeat
      }
    }
    break;

  case KC_E:
    if (keymap_config.swap_lalt_lgui)  { /* windows */
      if (record->event.pressed && isControlPressed){
        unregister_code(KC_LCTL);
        tap_code(KC_END);
        register_code(KC_LCTL);
        return false;
      }
    }
    break;

  case TGL_KANA:
    if (!record->event.pressed) {
      if(keymap_config.swap_lalt_lgui==false){ /* Mac */
        register_code(KC_LGUI);
        register_code(KC_SPACE);
        unregister_code(KC_SPACE);
        unregister_code(KC_LGUI);
      }else{
        SEND_STRING(SS_LALT("`"));
      }
    }
    break;
  }
  return true;
}
