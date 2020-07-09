#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "custom_keycodes.h"



#define NN_SHIFT_NOT_FOUND -1
#define KC_M_KANA M_KANA
#define KC_M_KANA M_KANA
#define KC_M_EISU M_EISU
#define KC_M_EISU M_EISU

#define NN_NO_SHIFT 0
#define NN_SHIFT_MODE_MIDDLE 1
#define NN_SHIFT_MODE_MEDICINAL (1 << 1)


void der_init_variables(void);

int der_find_mapping_on_combinations(void);
bool der_all_key_released(void);
void der_update_shift(void);
bool der_process_nn(uint16_t keycode, keyrecord_t *record);


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _JAPANESE,
    _LOWER ,                     /* 1 */
    _RAISE,                     /* 2 */
    _ADJUST
};

/* #define _QWERTY 0 */
/* #define _LOWER 3 */
/* #define _RAISE 4 */
/* #define _JAPANESE 2 */
/* #define _ADJUST 16 */


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RSFT,
  LSFT,
  HACHIMITSU,
  RGBRST,
  TGL_KANA
};
 
enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 5
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |  INS |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Esc   | Alt  | Alt  | CMD |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
                     KC_ESC            ,  KC_1   ,    KC_2   ,    KC_3   ,    KC_4  ,    KC_5    ,   /* dummy , dummy          , */  KC_6      ,    KC_7  ,    KC_8    ,    KC_9    ,    KC_0    , KC_DEL   , \
                     KC_TAB            ,  KC_Q   ,    KC_W   ,    KC_E   ,    KC_R  ,    KC_T    ,   /* dummy , dummy          , */  KC_Y      ,    KC_U  ,    KC_I    ,    KC_O    ,    KC_P    , KC_BSPC  , \
                     LCTL(KC_RBRACKET) ,  KC_A   ,    KC_S   ,    KC_D   ,    KC_F  ,    KC_G    ,   /* dummy , dummy          , */  KC_H      ,    KC_J  ,    KC_K    ,    KC_L    ,    KC_SCLN , KC_ENT   , \
                     KC_LSFT           ,  KC_Z   ,    KC_X   ,    KC_C   ,    KC_V  ,    KC_B    ,LCTL(KC_RBRACKET), KC_F1     ,     KC_N      ,    KC_M  ,    MT(MOD_RCTL, KC_COMM) , KC_DOT     ,    KC_SLSH , KC_RSFT  , \
                     KC_LCTL           ,  ADJUST ,TG(_RAISE) ,TG(_LOWER) ,  KC_LALT ,    KC_LGUI ,   KC_LSFT  ,   TGL_KANA , LT(_RAISE,KC_SPACE),   KC_RCTRL,    KC_LEFT , KC_DOWN    ,    KC_UP , KC_RGHT \
                      ),

  [_JAPANESE] = LAYOUT( \
                       KC_ESC            ,  KC_1   ,    KC_2  ,    KC_3 ,    KC_4  ,    KC_5    ,   /* dummy , dummy , */  KC_6    ,    KC_7 ,    KC_8    ,    KC_9 ,    KC_0    , KC_DEL  , \
                       KC_TAB            ,  KC_Q   ,    KC_W  ,    KC_E ,    KC_R  ,    KC_T    ,   /* dummy , dummy , */  KC_Y    ,    KC_U ,    KC_I    ,    KC_O ,    KC_P    , KC_BSPC , \
                       LCTL(KC_RBRACKET) ,  KC_A   ,    KC_S  ,    KC_D ,    KC_F  ,    KC_G    ,   /* dummy , dummy , */  KC_H    ,    KC_J ,    KC_K    ,    KC_L ,    KC_SCLN , KC_ENT  , \
                       KC_LSFT           ,  KC_Z   ,    KC_X  ,    KC_C ,    KC_V  ,    KC_B    ,   KC_INS   , KC_F1 ,     KC_N    ,    KC_M ,    KC_COMM , KC_DOT  ,    KC_SLSH , KC_RSFT , \
                       KC_LCTL           ,  ADJUST ,  KC_LALT , KC_LALT ,  KC_LALT ,    KC_LGUI ,   LSFT     , RSFT  ,     _______ , _______ ,    KC_LEFT , KC_DOWN ,    KC_UP   , KC_RGHT \
                        ),
  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   F1 |  F2  | f3   |  f4  | f5   |             |   f6 |  f7  |  f8  |  f9  | f10  | f11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   -  |   7  |   8  |  9   |  -   | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   +  |   4  |   5  |  6   |  +   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |   /  |   1  |   2  |  3   |  =   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |   0  |      |  .   |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
                    _______ , KC_F1   ,   KC_F2    ,   KC_F3    ,   KC_F4 ,   KC_F5 ,                        KC_F6 ,   KC_F7   ,   KC_F8 ,   KC_F9 ,   KC_F10 ,    KC_F11 , \
                    _______ , _______ , _______    , _______    , _______ , _______ ,                        KC_MINUS , KC_7   ,   KC_8    , KC_9    , KC_MINUS ,  _______  , \
                    _______ , _______ , _______    , _______    , _______ , _______ ,                        KC_PLUS , KC_4    ,   KC_5    , KC_6    , KC_PLUS  ,   _______ , \
                    _______ , _______ , _______    , _______    , _______ , _______ , _______ ,    _______ , KC_SLSH , KC_1    ,   KC_2     ,KC_3      , KC_EQL  ,    _______ , \
                    _______ , _______ , _______    , _______    , _______ , _______ , _______ ,    _______ , _______ , KC_0    ,   _______,  KC_DOT   , _______ , _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Home |  ↑   |  !   |  @   |  ~   |             |  -   |   =  |   [  |  ]   |   \  | f12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  <=  |  ↓  |  =>   |  $   |  %   |             |  _   |   -  |   {  | }    |   :  |  |  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  End |  1   |  2   |  #   |  `   |      |      |  '   |   "  |   <   | >   |   ?  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |  0   |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
                    KC_TILD , KC_EXLM  , KC_AT       ,   KC_HASH   , KC_DLR  ,  KC_PERC ,                    KC_CIRC   , KC_AMPR , KC_ASTR  , KC_LPRN , KC_RPRN   , _______   , \
                    _______ , KC_HOME,  KC_UP        ,   KC_EXLM   ,  KC_AT  ,  KC_TILDE,                    KC_MINS  ,  KC_EQL  , KC_LBRC ,  KC_RBRC , KC_BSLASH , KC_F12    , \
                    _______ , KC_LEFT  ,KC_DOWN      ,   KC_RIGHT  ,  KC_DLR ,  KC_PERC ,                    KC_UNDS ,   KC_PLUS , KC_LCBR  , KC_RCBR , KC_COLN   , KC_PIPE    , \
                    _______ , KC_END   ,  KC_LT      ,   KC_GT     ,  KC_HASH,  KC_GRAVE,  KC_PGUP,_______,  KC_QUOT ,   KC_DQT  ,  KC_LT  , KC_GT    , KC_QUES ,    _______ , \
                    _______ , _______  , TO(_QWERTY) , TO(_QWERTY) , KC_0    ,   _______,  KC_PGDN,_______,  _______ , _______ , _______   , _______   , _______ ,    _______ \
      ),


  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff| Mac  |             | Win  |Qwerty|Colemk|Dvorak|      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      _______, RESET,   RGBRST,  _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL, \
      _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, QWERTY,  _______, _______,  _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool isHachimitsuPressed = false;
  static bool isControlPressed = false;
    switch (keycode) {
    case KC_LCTL:
      if (record->event.pressed){
        isControlPressed = true;
      }
      else{
        isControlPressed = false;
      }
      break;
    case KC_H:
      if (keymap_config.swap_lalt_lgui)  { /* windows */
        if (record->event.pressed && isControlPressed){
          unregister_code(KC_LCTL);
          tap_code(KC_BSPC);
          register_code(KC_LCTL);
          return false;
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
    case KC_A:
      if (keymap_config.swap_lalt_lgui)  { /* windows */
        if (record->event.pressed && isControlPressed){
          unregister_code(KC_LCTL);
          tap_code(KC_HOME);
          register_code(KC_LCTL);
          return false;
        }
      }
      break;
    case KC_B:
      if (keymap_config.swap_lalt_lgui)  { /* windows */
        if (record->event.pressed && isControlPressed){
          unregister_code(KC_LCTL);
          tap_code(KC_LEFT);
          register_code(KC_LCTL);
          return false;
        }
      }
      break;
    case KC_F:
      if (keymap_config.swap_lalt_lgui)  { /* windows */
        if (record->event.pressed && isControlPressed){
          unregister_code(KC_LCTL);
          tap_code(KC_RIGHT);
          register_code(KC_LCTL);
          return false;
        }
      }
      break;
    case KC_D:
      if (keymap_config.swap_lalt_lgui)  { /* windows */
        if (record->event.pressed && isControlPressed){
          unregister_code(KC_LCTL);
          tap_code(KC_DEL);
          register_code(KC_LCTL);
          return false;
        }
      }
      break;
    case KC_P:
      if (keymap_config.swap_lalt_lgui)  { /* windows */
        if (record->event.pressed && isControlPressed){
          unregister_code(KC_LCTL);
          tap_code(KC_UP);
          register_code(KC_LCTL);
          return false;
        }
      }
    case KC_N:
      if (keymap_config.swap_lalt_lgui)  { /* windows */
        if (record->event.pressed && isControlPressed){
          unregister_code(KC_LCTL);
          tap_code(KC_DOWN);
          register_code(KC_LCTL);
          return false;
        }
      }
      break;
    /* case KC_K: */
    /*   if (keymap_config.swap_lalt_lgui)  { /\* windows *\/ */
    /*     if (record->event.pressed && isControlPressed){ */
    /*       unregister_code(KC_LCTL); */
    /*       register_code(KC_LSFT); */
    /*       tap_code(KC_END); */
    /*       unregister_code(KC_LSFT); */
    /*       tap_code(KC_DEL); */
    /*       register_code(KC_LCTL); */
    /*       return false; */
    /*     } */
    /*   } */
      /* break; */
    case QWERTY:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        PLAY_SONG(tone_qwerty);
#endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
    return false;
    break;
    case LOWER:
    if (record->event.pressed) {
      //not sure how to have keyboard check mode and set it to a variable, so my work around
      //uses another variable that would be set to true after the first time a reactive key is pressed.
      if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
      } else {
        TOG_STATUS = !TOG_STATUS;
      }
      layer_on(_LOWER);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    } else {
      TOG_STATUS = false;
      layer_off(_LOWER);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;

    case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
    } else {
      layer_off(_RAISE);
      TOG_STATUS = false;
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

    case RGB_MOD:
    return false;
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
    case HACHIMITSU:
      if (record->event.pressed) {
        if (isHachimitsuPressed){
          if(keymap_config.swap_lalt_lgui==false){ /* Mac */
            register_code(KC_LANG2);
          }else{
            SEND_STRING(SS_LALT("`"));
          }
          layer_off(_JAPANESE);
        }else{
          if(keymap_config.swap_lalt_lgui==false){ /* Mac */
            /* 蜂蜜日本語入力へ */
            register_code(KC_LANG1);
            /*練習用に「ひらがな」固定に */
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_H);
          }else{
            SEND_STRING(SS_LALT("`"));
          }
          register_code(KC_LANG1);
          layer_on(_JAPANESE);
        }
        isHachimitsuPressed = !isHachimitsuPressed;
      }else{
        if(isHachimitsuPressed){
          /* 蜂蜜日本語入力解除 */
          unregister_code(KC_H);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCTL);
          unregister_code(KC_LANG2);
        }else{
          unregister_code(KC_LANG1);
        }
      }
    return false;
    break;
    case RGBRST:
    break;
    }

  uint8_t layer = biton32(layer_state);
  switch (layer) {
  case _JAPANESE:
    return der_process_nn(keycode, record); break;
  default:
    break;
  }


  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));

  for (int i = 31; i >= 0 ; i--  ){
    if (layer_state & (1UL << i)) {
      switch(i){
      case _QWERTY:
        matrix_write_P(matrix, PSTR("Qwerty"));
        break;
      case _LOWER:
        matrix_write_P(matrix, PSTR("LOWER"));
        break;
      case _RAISE:
        matrix_write_P(matrix, PSTR("RAISE"));
        break;
      case _JAPANESE:
        matrix_write_P(matrix, PSTR("HACHIMITSU"));
        break;
      case _ADJUST:
        matrix_write_P(matrix, PSTR("ADJUST"));
        break;
      default:
        matrix_write_P(matrix, PSTR("default"));
        break;
      }
      break;
    }
  }

    /* switch (layer_state) { */
    /*     case L_BASE: */
    /*        matrix_write_P(matrix, PSTR("Default")); */
    /*        break; */
    /* case (1UL<<_QWERTY): */
    /*   matrix_write_P(matrix, PSTR("Qwerty")); */
    /*   break; */
    /*     case L_RAISE: */
    /*        matrix_write_P(matrix, PSTR("Raise")); */
    /*        break; */
    /*     case L_LOWER: */
    /*        matrix_write_P(matrix, PSTR("Lower")); */
    /*        break; */
    /*     case L_ADJUST: */
    /*     case L_ADJUST_TRI: */
    /*        matrix_write_P(matrix, PSTR("Adjust")); */
    /*        break; */
    /*     default: */
    /*        matrix_write(matrix, buf); */
    /* } */

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif


/*******
        Definitions for NAGINATA-STYLE arrays
 *******/
/*
  Implementation memo for hachimitsu-koume layout.

  1. Time-base and pressed only detection
  2. Time-base and pressed and released detection
  3. No time-base and pressed and released detection

  If choose 1., this method has one advantage that is more simple 2. . But this method will cause more longer time to show character.
  If choose 2., this method has detail control between other methods. But this method will be more complex of implementation.
  If choose 3., this method will need large configuration for layout, But this method implementation will be more simply than other methods.
 */
enum der_nn_keys {
  NN_NO = 0x00,
  NN_A,
  NN_B,
  NN_C,
  NN_D,
  NN_E,
  NN_F,
  NN_G,
  NN_H,
  NN_I,
  NN_J,
  NN_K,
  NN_L,
  NN_M,               /* 0x10 */
  NN_N,
  NN_O,
  NN_P,
  NN_Q,
  NN_R,
  NN_S,
  NN_T,
  NN_U,
  NN_V,
  NN_W,
  NN_X,
  NN_Y,
  NN_Z,
  NN_SCOLON,          /* ; and : */
  NN_COMMA,           /* , and < */
  NN_DOT,             /* . and > */
  NN_SLASH,           /* / and ? */
  NN_ENT,
  NN_RSFT,
  NN_LSFT,
  NN_LAST_RANGE,
};


/* variables to implement same-key shift */
static bool nn_pressed[NN_LAST_RANGE] = {false};
static uint8_t nn_pressed_keys = 0;
const static uint8_t nn_max_combination = 3;
static uint8_t nn_shift_mode = NN_NO_SHIFT;
static bool nn_shift_continue = false;

/* key sequence mapped keycode what is shifted  */
typedef struct {
  uint8_t key_combo[3];
  uint16_t key_sequence[4];
} der_nn_key_combination_t;

/* Define keycode and sequence when some key shifted */
const der_nn_key_combination_t PROGMEM der_nn_key_combinations[] =
  {
   /* left hand */
   /* qwert */

   /* Q */
    {.key_combo = {NN_Q, NN_LSFT, NN_NO}, .key_sequence = KS_PE},
    {.key_combo = {NN_Q, NN_RSFT, NN_NO}, .key_sequence = KS_PA},
    {.key_combo = {NN_Q, NN_NO, NN_NO}, .key_sequence = {KC_DOT}},

   /* W */
    {.key_combo = {NN_W, NN_LSFT, NN_NO}, .key_sequence = KS_KE},
    {.key_combo = {NN_W, NN_RSFT, NN_NO}, .key_sequence = KS_GE},
    {.key_combo = {NN_W, NN_NO, NN_NO}, .key_sequence = KS_NA},

  /* E */
    {.key_combo = {NN_E, NN_LSFT, NN_NO}, .key_sequence = KS_YO},
    {.key_combo = {NN_E, NN_RSFT, NN_NO}, .key_sequence = KS_DE},
    {.key_combo = {NN_E, NN_NO, NN_NO}, .key_sequence = KS_TE},

  /* R */
    {.key_combo = {NN_R, NN_LSFT, NN_NO}, .key_sequence = {KC_MINS}},
    {.key_combo = {NN_R, NN_RSFT, NN_NO}, .key_sequence = KS_ZE},
    {.key_combo = {NN_R, NN_NO, NN_NO}, .key_sequence = KS_SE},


  /* T */
    {.key_combo = {NN_T, NN_LSFT, NN_NO}, .key_sequence = {KC_DOT,KC_DOT,KC_DOT}},
    {.key_combo = {NN_T, NN_RSFT, NN_NO}, .key_sequence = KS_ZO},
    {.key_combo = {NN_T, NN_NO, NN_NO}, .key_sequence = KS_SO},

  /* asdfg */

   /* A */
    {.key_combo = {NN_A, NN_LSFT, NN_NO}, .key_sequence = KS_ME},
    {.key_combo = {NN_A, NN_RSFT, NN_NO}, .key_sequence = KS_GO},
    {.key_combo = {NN_A, NN_NO, NN_NO}, .key_sequence = KS_KO},

   /* S */
    {.key_combo = {NN_S, NN_LSFT, NN_NO}, .key_sequence = KS_YA},
    {.key_combo = {NN_S, NN_RSFT, NN_NO}, .key_sequence = KS_DA},
    {.key_combo = {NN_S, NN_NO, NN_NO}, .key_sequence = KS_TA},


    /* D */
    {.key_combo = {NN_D, NN_LSFT, NN_NO}, .key_sequence = KS_MO},
    {.key_combo = {NN_D, NN_RSFT, NN_NO}, .key_sequence = KS_GA},
    {.key_combo = {NN_D, NN_NO, NN_NO}, .key_sequence = KS_KA},

    /* F */
    {.key_combo = {NN_F, NN_LSFT, NN_NO}, .key_sequence = KS_SA},
    {.key_combo = {NN_F, NN_RSFT, NN_NO}, .key_sequence = KS_ZA},
    {.key_combo = {NN_F, NN_NO, NN_NO}, .key_sequence = KS_RU},

    /* G */
    {.key_combo = {NN_G, NN_LSFT, NN_NO}, .key_sequence = KS_XU},
    {.key_combo = {NN_G, NN_RSFT, NN_NO}, .key_sequence = KS_BA},
    {.key_combo = {NN_G, NN_NO, NN_NO}, .key_sequence = KS_HA},

    /* Z */
    {.key_combo = {NN_Z, NN_LSFT, NN_NO}, .key_sequence = KS_XYU},
    {.key_combo = {NN_Z, NN_RSFT, NN_NO}, .key_sequence = KS_PO},
    {.key_combo = {NN_Z, NN_NO, NN_NO}, .key_sequence = KS_YU},

    /* X */
    {.key_combo = {NN_X , NN_LSFT , NN_NO} , .key_sequence = KS_XYA} ,
    {.key_combo = {NN_X , NN_RSFT , NN_NO} , .key_sequence = KS_BO} ,
    {.key_combo = {NN_X , NN_NO   , NN_NO} , .key_sequence = KS_HO} ,

    /* C */
    {.key_combo = {NN_C, NN_LSFT, NN_NO}, .key_sequence = KS_HU},
    {.key_combo = {NN_C, NN_RSFT, NN_NO}, .key_sequence = KS_BU},
    {.key_combo = {NN_C, NN_NO, NN_NO}, .key_sequence = KS_MA},

    /* V */
    {.key_combo = {NN_V, NN_LSFT, NN_NO}, .key_sequence = KS_XYO},
    {.key_combo = {NN_V, NN_RSFT, NN_NO}, .key_sequence = KS_PU},
    {.key_combo = {NN_V, NN_NO, NN_NO}, .key_sequence = KS_RO},

    /* B */
    {.key_combo = {NN_B, NN_LSFT, NN_NO}, .key_sequence = KS_XO},
    {.key_combo = {NN_B, NN_RSFT, NN_NO}, .key_sequence = KS_XWA},
    {.key_combo = {NN_B, NN_NO, NN_NO}, .key_sequence = {KC_TILDE}},

    /* Y */
    {.key_combo = {NN_Y, NN_NO, NN_NO}, .key_sequence = {KC_SLSH}},

    /* U */
    {.key_combo = {NN_U, NN_LSFT, NN_NO}, .key_sequence = KS_BI},
    {.key_combo = {NN_U, NN_RSFT, NN_NO}, .key_sequence = KS_HI},
    {.key_combo = {NN_U, NN_NO, NN_NO}, .key_sequence = KS_O},

    /* I */
    {.key_combo = {NN_I, NN_LSFT, NN_NO}, .key_sequence = KS_GI},
    {.key_combo = {NN_I, NN_RSFT, NN_NO}, .key_sequence = KS_KI},
    {.key_combo = {NN_I, NN_NO, NN_NO}, .key_sequence = KS_NO},

    /* O */
    {.key_combo = {NN_O, NN_LSFT, NN_NO}, .key_sequence = KS_DU},
    {.key_combo = {NN_O, NN_RSFT, NN_NO}, .key_sequence = KS_TU},
    {.key_combo = {NN_O, NN_NO, NN_NO}, .key_sequence = KS_NI},

    /* P */
    {.key_combo = {NN_P, NN_LSFT, NN_NO}, .key_sequence = {KC_RBRC}},
    {.key_combo = {NN_P, NN_RSFT, NN_NO}, .key_sequence = {KC_LBRC}},
    {.key_combo = {NN_P, NN_NO, NN_NO}, .key_sequence = {KC_LBRC,KC_RBRC}},

    /* H */
    {.key_combo = {NN_H, NN_LSFT, NN_NO}, .key_sequence = KS_XI},
    {.key_combo = {NN_H, NN_RSFT, NN_NO}, .key_sequence = KS_MU},
    {.key_combo = {NN_H, NN_NO, NN_NO}, .key_sequence = {KC_MINS}},

    /* J */
    {.key_combo = {NN_J, NN_LSFT, NN_NO}, .key_sequence = KS_XA},
    {.key_combo = {NN_J, NN_RSFT, NN_NO}, .key_sequence = KS_RE},
    {.key_combo = {NN_J, NN_NO, NN_NO}, .key_sequence = KS_NN},

    /* K */
    {.key_combo = {NN_K, NN_LSFT, NN_NO}, .key_sequence = KS_GU},
    {.key_combo = {NN_K, NN_RSFT, NN_NO}, .key_sequence = KS_KU},
    {.key_combo = {NN_K, NN_NO, NN_NO}, .key_sequence = KS_I},

    /* L */
    {.key_combo = {NN_L, NN_LSFT, NN_NO}, .key_sequence = KS_ZI},
    {.key_combo = {NN_L, NN_RSFT, NN_NO}, .key_sequence = KS_RI},
    {.key_combo = {NN_L, NN_NO, NN_NO}, .key_sequence = KS_SI},

    /* SCOLON */
    {.key_combo = {NN_SCOLON, NN_LSFT, NN_NO}, .key_sequence = KS_DO},
    {.key_combo = {NN_SCOLON, NN_RSFT, NN_NO}, .key_sequence = KS_WA},
    {.key_combo = {NN_SCOLON, NN_NO, NN_NO}, .key_sequence = KS_TO},

    /* ENT */
    {.key_combo = {NN_ENT, NN_LSFT, NN_NO}, .key_sequence = KS_PI},
    {.key_combo = {NN_ENT, NN_RSFT, NN_NO}, .key_sequence = KS_NE},
    {.key_combo = {NN_ENT, NN_NO, NN_NO}, .key_sequence = {KC_ENT}},

    /* N */
    {.key_combo = {NN_N, NN_LSFT, NN_NO}, .key_sequence = KS_XE},
    {.key_combo = {NN_N, NN_RSFT, NN_NO}, .key_sequence = KS_MI},
    {.key_combo = {NN_N, NN_NO, NN_NO}, .key_sequence = KS_XTU},

    /* M */
    {.key_combo = {NN_M, NN_LSFT, NN_NO}, .key_sequence = KS_VU},
    {.key_combo = {NN_M, NN_RSFT, NN_NO}, .key_sequence = KS_A},
    {.key_combo = {NN_M, NN_NO, NN_NO}, .key_sequence = KS_U},

    /* COMMA */
    {.key_combo = {NN_COMMA, NN_LSFT, NN_NO}, .key_sequence = KS_ZU},
    {.key_combo = {NN_COMMA, NN_RSFT, NN_NO}, .key_sequence = KS_E},
    {.key_combo = {NN_COMMA, NN_NO, NN_NO}, .key_sequence = KS_SU},

    /* DOT */
    {.key_combo = {NN_DOT, NN_LSFT, NN_NO}, .key_sequence = KS_DI},
    {.key_combo = {NN_DOT, NN_RSFT, NN_NO}, .key_sequence = KS_TI},
    {.key_combo = {NN_DOT, NN_NO, NN_NO}, .key_sequence = KS_RA},

    /* SLASH */
    {.key_combo = {NN_SLASH, NN_LSFT, NN_NO}, .key_sequence = KS_BE},
    {.key_combo = {NN_SLASH, NN_RSFT, NN_NO}, .key_sequence = KS_NU},
    {.key_combo = {NN_SLASH, NN_NO, NN_NO}, .key_sequence = KS_HE},


   /* special combination */
   {.key_combo = {NN_D, NN_K, NN_NO}, .key_sequence = KS_WO},
   /* {.key_combo = {NN_N, NN_J, NN_NO}, .key_sequence = {KC_SLSH}}, */

   /* {.key_combo = {NN_S, NN_A, NN_NO}, .key_sequence = KS_PO}, */
   /* {.key_combo = {NN_S, NN_F, NN_NO}, .key_sequence = KS_PE}, */
   /* {.key_combo = {NN_S, NN_V, NN_NO}, .key_sequence = KS_PU}, */
   /* {.key_combo = {NN_S, NN_Z, NN_NO}, .key_sequence = KS_PI}, */
   /* {.key_combo = {NN_S, NN_E, NN_NO}, .key_sequence = KS_PA}, */

   /* {.key_combo = {NN_L, NN_SCOLON, NN_NO}, .key_sequence = KS_XO}, */
   /* {.key_combo = {NN_L, NN_J, NN_NO}, .key_sequence = KS_XE}, */
   /* {.key_combo = {NN_L, NN_M, NN_NO}, .key_sequence = KS_XU}, */
   /* {.key_combo = {NN_L, NN_SLASH, NN_NO}, .key_sequence = KS_XI}, */
   /* {.key_combo = {NN_L, NN_I, NN_NO}, .key_sequence = KS_XA}, */

   /* {.key_combo = {NN_D, NN_K, NN_NO}, .key_sequence = KS_WO}, */
  };

/* Initialize variables for japanese implement */
void der_init_variables(void) {
  for (int i = 0; i < NN_LAST_RANGE; i++) {
    nn_pressed[i] = false;
  }
  nn_pressed_keys = 0;
  nn_shift_continue = false;
  nn_shift_mode = NN_NO_SHIFT;
}

/* convert keycode to shift id */
uint16_t der_conv_kc_to_custom_key(uint16_t keycode) {
  switch (keycode) {
  case KC_Q: return NN_Q; break;
  case KC_W: return NN_W; break;
  case KC_E: return NN_E; break;
  case KC_R: return NN_R; break;
  case KC_T: return NN_T; break;
  case KC_Y: return NN_Y; break;
  case KC_U: return NN_U; break;
  case KC_I: return NN_I; break;
  case KC_O: return NN_O; break;
  case KC_P: return NN_P; break;
  case KC_A: return NN_A; break;
  case KC_S: return NN_S; break;
  case KC_D: return NN_D; break;
  case KC_F: return NN_F; break;
  case KC_G: return NN_G; break;
  case KC_H: return NN_H; break;
  case KC_J: return NN_J; break;
  case KC_K: return NN_K; break;
  case KC_L: return NN_L; break;
  case KC_SCLN: return NN_SCOLON; break;
  case KC_Z: return NN_Z; break;
  case KC_X: return NN_X; break;
  case KC_C: return NN_C; break;
  case KC_V: return NN_V; break;
  case KC_B: return NN_B; break;
  case KC_N: return NN_N; break;
  case KC_M: return NN_M; break;
  case KC_COMM: return NN_COMMA; break;
  case KC_DOT: return NN_DOT; break;
  case KC_SLSH: return NN_SLASH; break;
  case KC_ENT: return NN_ENT; break;
  case RSFT: return NN_RSFT; break;
  case LSFT: return NN_LSFT; break;
  }

  return NN_NO;
}

der_nn_key_combination_t der_get_mapping(int index) {
  der_nn_key_combination_t data;
  memcpy_P(&data, &der_nn_key_combinations[index], sizeof(der_nn_key_combination_t));
  return data;
}

/* simple bubble sort */
void der_sort_key_combination(uint8_t* seq, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = size - 1; j > i; j--) {
      if (seq[j - 1] > seq[j]) {
        uint8_t tmp = seq[j];
        seq[j] = seq[j - 1];
        seq[j - 1] = tmp;
      }
    }
  }
}

/* find shift */
bool der_match_combination_pressed(der_nn_key_combination_t* combination, bool* key_pressed) {
  uint8_t combination_seq[3] = {NN_NO};
  uint8_t pressed_seq[3] = {NN_NO};
  memcpy(combination_seq, combination->key_combo, nn_max_combination * sizeof(uint8_t));

  uint8_t recorded = 0;
  for (int i = 0; i < NN_LAST_RANGE;i++) {
    if (recorded >= nn_max_combination) {
      break;
    }

    if (key_pressed[i]) {
      pressed_seq[recorded] = i;
      recorded++;
    }
  }

  der_sort_key_combination(combination_seq, nn_max_combination);
  der_sort_key_combination(pressed_seq, nn_max_combination);

  for (int i = 0; i < nn_max_combination; i++) {
    if (combination_seq[i] != pressed_seq[i]) {
      return false;
    }
  }

  return true;
}

/* return index of key_shifters if found shifter */
int der_find_mapping_on_combinations() {
  int length = sizeof(der_nn_key_combinations) / sizeof(der_nn_key_combination_t);
  for (int i = 0; i < length; i++) {
    der_nn_key_combination_t data = der_get_mapping(i);

    if (der_match_combination_pressed(&data, nn_pressed)) {
      return i;
    }
  }

  return NN_SHIFT_NOT_FOUND;
}

/* send keycodes in specified key mapping */
void der_send_key_sequence(int index) {

  if (NN_SHIFT_NOT_FOUND == index) {
    return;
  }

  der_nn_key_combination_t mapping = der_get_mapping(index);

  int length = sizeof(mapping.key_sequence) / sizeof(uint16_t);
  for (int i = 0; i < length; i++) {
    if (mapping.key_sequence[i] == KC_NO) {
      continue;
    }
    register_code(mapping.key_sequence[i]);
    unregister_code(mapping.key_sequence[i]);
  }
}

void der_update_shift() {
  uint8_t keys[] = {NN_K, NN_L, NN_I, NN_O, NN_D, NN_W};

  int new_status = NN_NO_SHIFT;
  int size = sizeof(keys) / sizeof(uint8_t);
  for (int i = 0; i < size; i++) {
    switch (keys[i]) {
    case NN_K:
      if (nn_pressed[keys[i]]) {
        new_status |= NN_SHIFT_MODE_MIDDLE;
      }
      break;
    case NN_L:
      if (nn_pressed[keys[i]]) {
        new_status |= NN_SHIFT_MODE_MEDICINAL;
      }
      break;
    case NN_D:
      if (nn_pressed[keys[i]]) {
        new_status |= NN_SHIFT_MODE_MIDDLE;
      }
      break;
    case NN_S:
      if (nn_pressed[keys[i]]) {
        new_status |= NN_SHIFT_MODE_MEDICINAL;
      }
      break;
    default:
      break;
    }
  }

  nn_shift_mode = new_status;
}

/* Process to resolve key combination from user pressed key */
bool der_process_nn_combination_pressed(uint16_t keycode, uint8_t custom_key) {

  /* can not handle key pressing if current index arise maximum of combination  */
  if (nn_pressed_keys >= nn_max_combination) {
    return false;
  }

  nn_pressed_keys++;
  nn_pressed[custom_key] = true;

  der_update_shift();

  return false;
}

/* check to all key released */
bool der_all_key_released() {
  for (int i = 0; i < NN_LAST_RANGE; i++) {
    if (nn_pressed[i]) {
      return false;
    }
  }
  return true;
}

/* Process to resolve key sequence when user released key */
bool der_process_nn_combination_released(uint16_t keycode, uint16_t custom_key) {

  if (der_all_key_released()) {
    return true;
  }

  /* get current combination, and release current key. */
  int index = der_find_mapping_on_combinations();
  int previous_mode = nn_shift_mode;

  nn_pressed_keys--;
  nn_pressed[custom_key] = false;
  der_update_shift();

  if (nn_shift_continue) {
    if (nn_pressed_keys == 0) {
      der_init_variables();
      return false;
    }

  }

  der_send_key_sequence(index);

  // when release shift key
  if (previous_mode != nn_shift_mode) {
    der_init_variables();
    return false;
  }

  if (nn_shift_mode != NN_NO_SHIFT) {
    nn_shift_continue = true;
  } else {
    der_init_variables();
  }

  return false;
}

/* Process keycodes as hachimitsu-koume keycodes */
bool der_process_nn(uint16_t keycode, keyrecord_t *record) {
  if (has_anymod()) {
    return true;
  }

  uint16_t custom_key = der_conv_kc_to_custom_key(keycode);
  if (record->event.pressed) {

    switch (custom_key) {
    case NN_NO:
      der_init_variables();
      break;
    default:
      return der_process_nn_combination_pressed(keycode, custom_key);
    }
  } else {
    /* If key released when current shifter is NOSHIFT, pass through keycode to common process.  */
    switch (custom_key) {
    case NN_NO:
      /* initialize all variables */
      der_init_variables();
      break;
    default:
      return der_process_nn_combination_released(keycode, custom_key);
    }
  }

  return true;
}
