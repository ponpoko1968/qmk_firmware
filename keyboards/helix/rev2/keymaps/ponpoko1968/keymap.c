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
    _LOWER,                     /* 1 */
    _RAISE,                     /* 2 */
    _OYA,                       /* 3 */
    _ADJUST                     /* 4*/
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST,
  OYAYUBI
};

 /* https://github.com/nishio/qmk_firmware/blob/thumb_shift/keyboards/ergodox/keymaps/thumb_shift/keymap.c */

bool isOyayubiPressed   = false;

bool isLeftShiftPressed = false;
bool isRightShiftPressed = false;

bool isLeftCtrlPressed = false;


typedef struct {
  uint8_t macro_id;
  uint16_t base[3];
  uint16_t lshift[3];
  uint16_t rshift[3];
  uint16_t lctl[3];
} macro_to_sequence_t;



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
   * | Ctrl |Adjust| Lower|Raise |  Alt |  Cmd |Lower |KANA  |Raise |to_OYA| Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
                     KC_ESC             ,  KC_1   ,    KC_2  ,    KC_3 ,    KC_4  ,    KC_5   ,   /* dummy , dummy          , */  KC_6 ,    KC_7   ,    KC_8    ,    KC_9 ,    KC_0    , KC_DEL , \
                     KC_TAB             ,  KC_Q   ,    KC_W  ,    KC_E ,    KC_R  ,    KC_T   ,   /* dummy , dummy          , */  KC_Y ,    KC_U   ,    KC_I    ,    KC_O ,    KC_P    , KC_BSPC  , \
                     LCTL(KC_RBRACKET)  ,  KC_A   ,    KC_S  ,    KC_D ,    KC_F,      KC_G ,   /* dummy , dummy          , */    KC_H ,    KC_J   ,    KC_K    ,    KC_L ,LCTL_T(KC_SCLN) , KC_ENT  , \
                     KC_LSFT            ,  KC_Z   ,    KC_X  ,    KC_C ,    KC_V  ,    KC_B   ,     KC_INS  ,KC_F1,               KC_N ,    KC_M   ,    KC_COMM , KC_DOT  ,    KC_SLSH , KC_RSFT , \
                    KC_LCTL,               ADJUST ,    LOWER ,    RAISE,  KC_LALT , KC_LGUI,     LOWER  , LGUI(KC_SPACE),     LT(_RAISE,KC_SPACE),      OYAYUBI ,    KC_LEFT , KC_DOWN ,    KC_UP   , KC_RGHT \
                      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   F1 |  F2  | f3   |  f4  | f5   |             |   f6 |  f7  |  f8  |  f9  | f10  | f11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   /  |   7  |   8  |  9   |  -   | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   *  |   4  |   5  |  6   |  +   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |   1  |   2  |  3   |  =   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |   0  |      |  .   |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
                    _______ , KC_F1   ,   KC_F2    ,   KC_F3    ,   KC_F4 ,   KC_F5 ,                        KC_F6 ,   KC_F7    ,  KC_F8 ,   KC_F9 ,   KC_F10 ,    KC_F11 , \
                    _______ , _______ , _______    , _______    , _______ , _______ ,                        KC_SLSH , KC_7       ,KC_8    , KC_9    , KC_MINUS ,  KC_F12   , \
                    _______ , _______ , _______    , _______    , _______ , _______ ,                        KC_ASTR , KC_4       ,KC_5    , KC_6    , KC_PLUS  ,   _______ , \
                    _______ , _______ , _______    , _______    , _______ , _______ , _______ ,    _______ , _______ , KC_1    ,   KC_2     ,KC_3      , KC_EQL  ,    _______ , \
                    _______ , _______ ,TO(_QWERTY) ,TO(_QWERTY) , _______ , _______ , _______ ,    _______ , _______ , KC_0    ,   _______,  KC_DOT   , _______ , _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |  7   |  8   |  0   |  ~   |             |  -   |   =  |   [  |  ]   |   \  | f12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |  4   |  5   |  6   |      |             |  _   |   -  |   {  | }    |   |  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  1   |  2   |  3   |  `   |      |      |  '   |   "  |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |  0   |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
                    KC_TILD , KC_EXLM  , KC_AT       ,   KC_HASH   , KC_DLR  ,  KC_PERC  ,                    KC_CIRC   , KC_AMPR , KC_ASTR  , KC_LPRN , KC_RPRN   , _______   , \
                    _______ ,  KC_HOME, KC_UP        ,   KC_8      ,   KC_9  ,  KC_TILDE ,                    KC_MINS  ,  KC_EQL  , KC_LBRC ,  KC_RBRC , KC_BSLASH , KC_F12    , \
                    _______ , KC_LEFT  ,KC_DOWN      ,   KC_RIGHT      ,    KC_6 ,  _______  ,                    KC_UNDS ,   KC_PLUS , KC_LCBR  , KC_RCBR , KC_PIPE   ,   _______ , \
                    _______ , KC_END   ,  KC_1       ,   KC_2      ,    KC_3 ,  KC_GRAVE ,  KC_PGUP,_______,  KC_QUOT ,   KC_DQT  ,  _______  , _______   , _______ ,    _______ , \
                    _______ , _______  , TO(_QWERTY) , TO(_QWERTY) , KC_0    ,   _______ ,  KC_PGDN,_______,  _______ , _______ , _______   , _______   , _______ ,    _______ \
      ),

#if 0

    qmk_firmware/keymap.c at thumb_shift · nishio/qmk_firmware
    https://github.com/nishio/qmk_firmware/blob/thumb_shift/keyboards/ergodox/keymaps/thumb_shift/keymap.c

    [BASE] = KEYMAP(
    // layer 0: Thumb Shift
    // left hand
    KC_ESC,  M(0),  M(1) , M(2),  M(3),  M(4),  KC_NO,
    KC_TAB,  M(10), M(11), M(12), M(13), M(14), KC_UP,
    KC_TAB,  M(20), M(21), M(22), M(23), M(24),
    KC_LSFT, M(30), M(31), M(32), M(33), M(34), KC_DOWN,
    TO(1),   KC_NO, KC_NO, KC_NO, KC_NO,

    /*   */ KC_NO,    KC_NO,
  /*           */   KC_NO,
  M(100), KC_SPACE, KC_NO,

  // right hand
  KC_NO,   M(5),  M(6),    M(7),     M(8),  M(9),  KC_BSPACE,
  KC_NO,   M(15), M(16),   M(17),    M(18), M(19), KC_NO,
  /*    */ M(25), M(26),   M(27),    M(28), M(29), KC_NO,
  KC_NO,   M(35), M(36),   M(37),    M(38), M(39), KC_NO,
  /*           */ KC_LEFT, KC_RIGHT, KC_NO, KC_NO, KC_NO,

  KC_NO, KC_NO,
  KC_NO,
  KC_NO, KC_ENTER, M(101)
  ),
#endif

  /* 親指シフト（ベース）
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_OYA] =  LAYOUT( \
                   _______ ,    M(0)   ,     M(1),      M(2),      M(3),        M(4),                                 M(5)   ,    M(6),       M(7),       M(8),      M(9),      _______, \
                   _______ ,   M(10)   ,    M(11),     M(12),     M(13),       M(14),                                M(15)   ,   M(16),      M(17),      M(18),     M(19),      _______ , \
                   _______ ,   M(20)   ,    M(21),     M(22),     M(23),       M(24),                                M(25)   ,   M(26),      M(27),      M(28),     M(29),      _______ , \
                   _______ ,   M(30)   ,    M(31),     M(32),     M(33),       M(34),  _______ ,   _______,          M(35)   ,   M(36),      M(37),      M(38),     M(39),      _______ , \
                   M(102)  ,   _______ ,   _______ ,   _______ , _______ ,   _______ ,   M(100),    M(101),          _______ , _______ ,   _______ ,   _______ ,  _______ ,   _______ \
                       ),
  /* 親指シフト（右）
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */

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



const macro_to_sequence_t macro_to_sequence[] = {
  /*M(0):  1 ? ?       */ {.base={KC_1}       , .lshift={KC_NO, 1}         , .rshift={KC_NO, 2}         ,  .lctl={KC_NO,0}},
  /*M(1):  2 ? ?       */ {.base={KC_2}       , .lshift={KC_NO, 3}         , .rshift={KC_NO, 4}         ,  .lctl={KC_NO,0}},
  /*M(2):  3 ? ?       */ {.base={KC_3}       , .lshift={KC_NO, 5}         , .rshift={KC_NO, 6}         ,  .lctl={KC_NO,0}},
  /*M(3):  4 ? ?       */ {.base={KC_4}       , .lshift={KC_NO, 7}         , .rshift={KC_NO, 8}         ,  .lctl={KC_NO,0}},
  /*M(4):  5 ? ?       */ {.base={KC_5}       , .lshift={KC_NO, 9}         , .rshift={KC_NO, 10}        ,  .lctl={KC_NO,0}},
  /*M(5):  6 ? ?       */ {.base={KC_6}       , .lshift={KC_NO, 11}        , .rshift={KC_NO, 12}        ,  .lctl={KC_NO,0}},
  /*M(6):  7 ? ?       */ {.base={KC_7}       , .lshift={KC_NO, 13}        , .rshift={KC_NO, 14}        ,  .lctl={KC_NO,0}},
  /*M(7):  8 ? ?       */ {.base={KC_8}       , .lshift={KC_NO, 15}        , .rshift={KC_NO, 16}        ,  .lctl={KC_NO,0}},
  /*M(8):  9 ? ?       */ {.base={KC_9}       , .lshift={KC_NO, 17}        , .rshift={KC_NO, 18}        ,  .lctl={KC_NO,0}},
  /*M(9):  0 ? ?       */ {.base={KC_0}       , .lshift={KC_NO, 19}        , .rshift={KC_NO, 20}        ,  .lctl={KC_NO,0}},

  /*M(10): ? xa ?      */ {.base={KC_NO, 21}  , .lshift={KC_X, KC_A}       , .rshift={KC_NO, 22}        ,  .lctl={KC_Q}},
  /*M(11): ka e ga     */ {.base={KC_K, KC_A} , .lshift={KC_E}             , .rshift={KC_G, KC_A}       ,  .lctl={KC_W}},
  /*M(12): ta ri da    */ {.base={KC_T, KC_A} , .lshift={KC_R, KC_I}       , .rshift={KC_D, KC_A}       ,  .lctl={KC_E}},
  /*M(13): ko xya go   */ {.base={KC_K, KC_O} , .lshift={KC_X, KC_Y, KC_A} , .rshift={KC_G, KC_O}       ,  .lctl={KC_R}},
  /*M(14): sa re za    */ {.base={KC_S, KC_A} , .lshift={KC_R, KC_E}       , .rshift={KC_Z, KC_A}       ,  .lctl={KC_T}},
  /*M(15): ra pa yo    */ {.base={KC_R, KC_A} , .lshift={KC_P, KC_A}       , .rshift={KC_Y, KC_O}       ,  .lctl={KC_Y}},
  /*M(16): ti di ni    */ {.base={KC_T, KC_I} , .lshift={KC_D, KC_I}       , .rshift={KC_N, KC_I}       ,  .lctl={KC_U}},
  /*M(17): ku gu ru    */ {.base={KC_K, KC_U} , .lshift={KC_G, KC_U}       , .rshift={KC_R, KC_U}       ,  .lctl={KC_I}},
  /*M(18): tu du ma    */ {.base={KC_T, KC_U} , .lshift={KC_D, KC_U}       , .rshift={KC_M, KC_A}       ,  .lctl={KC_O}},
  /*M(19): ? pi xe     */ {.base={KC_NO, 23}  , .lshift={KC_P, KC_I}       , .rshift={KC_X, KC_E}       ,  .lctl={KC_P}},

  /*M(20): u wo vu     */ {.base={KC_U}       , .lshift={KC_W, KC_O}       , .rshift={KC_V, KC_U}       ,  .lctl={KC_A}},
  /*M(21): si a ji     */ {.base={KC_S, KC_I} , .lshift={KC_A}             , .rshift={KC_J, KC_I}       ,  .lctl={KC_S}},
  /*M(22): te na de    */ {.base={KC_T, KC_E} , .lshift={KC_N, KC_A}       , .rshift={KC_D, KC_E}       ,  .lctl={KC_D}},
  /*M(23): ke xyu ge   */ {.base={KC_K, KC_E} , .lshift={KC_X, KC_Y, KC_U} , .rshift={KC_G, KC_E}       ,  .lctl={KC_F}},
  /*M(24): se mo ze    */ {.base={KC_S, KC_E} , .lshift={KC_M, KC_O}       , .rshift={KC_Z, KC_E}       ,  .lctl={KC_G}},
  /*M(25): ha ba mi    */ {.base={KC_H, KC_A} , .lshift={KC_B, KC_A}       , .rshift={KC_M, KC_I}       ,  .lctl={KC_H}},
  /*M(26): to do o     */ {.base={KC_T, KC_O} , .lshift={KC_D, KC_O}       , .rshift={KC_O}             ,  .lctl={KC_J}},
  /*M(27): ki gi no    */ {.base={KC_K, KC_I} , .lshift={KC_G, KC_I}       , .rshift={KC_N, KC_O}       ,  .lctl={KC_K}},
  /*M(28): i po xyo    */ {.base={KC_I}       , .lshift={KC_P, KC_O}       , .rshift={KC_X, KC_Y, KC_O} ,  .lctl={KC_L}},
  /*M(29): nn ? xtu    */ {.base={KC_N, KC_N} , .lshift={KC_NO, 24}        , .rshift={KC_X, KC_T, KC_U} ,  .lctl={KC_NO}},

  /*M(30): ? xu ?     */ {.base={KC_NO, 25}   , .lshift={KC_X, KC_U}       , .rshift={KC_NO, 26}        ,  .lctl={KC_Z}},
  /*M(31): hi - bi     */ {.base={KC_H, KC_I} , .lshift={KC_MINUS}         , .rshift={KC_B, KC_I}       ,  .lctl={KC_X}},
  /*M(32): su ro zu    */ {.base={KC_S, KC_U} , .lshift={KC_R, KC_O}       , .rshift={KC_Z, KC_U}       ,  .lctl={KC_C}},
  /*M(33): fu ya bu    */ {.base={KC_F, KC_U} , .lshift={KC_Y, KC_A}       , .rshift={KC_B, KC_U}       ,  .lctl={KC_V}},
  /*M(34): he xi be    */ {.base={KC_H, KC_E} , .lshift={KC_X, KC_I}       , .rshift={KC_B, KC_E}       ,  .lctl={KC_B}},
  /*M(35): me pu nu    */ {.base={KC_M, KC_E} , .lshift={KC_P, KC_U}       , .rshift={KC_N, KC_U}       ,  .lctl={KC_N}},
  /*M(36): so zo yu    */ {.base={KC_S, KC_O} , .lshift={KC_Z, KC_O}       , .rshift={KC_Y, KC_U}       ,  .lctl={KC_M}},
  /*M(37): ne pe mu    */ {.base={KC_N, KC_E} , .lshift={KC_P, KC_E}       , .rshift={KC_M, KC_U}       ,  .lctl={KC_NO,0}},
  /*M(38): ho bo wa    */ {.base={KC_H, KC_O} , .lshift={KC_B, KC_O}       , .rshift={KC_W, KC_A}       ,  .lctl={KC_NO,0}},
  /*M(39): ? ? xo      */ {.base={KC_NO, 27}  , .lshift={KC_NO, 28}        , .rshift={KC_X, KC_O}       ,  .lctl={KC_NO,0}},
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  if(id < 40){
    if (record->event.pressed) {
      const uint16_t* seq;
      if(isLeftShiftPressed){
        seq = macro_to_sequence[id].lshift;
      }else if(isRightShiftPressed){
        seq = macro_to_sequence[id].rshift;
      }else if(isLeftCtrlPressed){
        seq = macro_to_sequence[id].lctl;
      }else{
        seq = macro_to_sequence[id].base;
      }
      // special commands
      if(seq[0] == KC_NO && seq[1] > 0){
        switch(seq[1]){
        case 1: // "？?"
          register_code(KC_LSHIFT);
          register_code(KC_SLASH);
          unregister_code(KC_SLASH);
          unregister_code(KC_LSHIFT);
          break;
        case 21: // "・/"
          register_code(KC_SLASH);
          unregister_code(KC_SLASH);
          break;
        case 23: // "、,"
          register_code(KC_COMMA);
          unregister_code(KC_COMMA);
          break;
        case 27: // "。."
          register_code(KC_DOT);
          unregister_code(KC_DOT);
          break;
        case 7: // "「["
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 8: // "『"
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 9: // "」]"
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 10: // "』"
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          break;
        case 11: // "["
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          register_code(KC_F10);
          unregister_code(KC_F10);
          break;
        case 12: // "("
          register_code(KC_LSHIFT);
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_code(KC_LSHIFT);
          break;
        case 13: // "]"
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          register_code(KC_F10);
          unregister_code(KC_F10);
          break;
        case 14: // ")"
          register_code(KC_LSHIFT);
          register_code(KC_0);
          unregister_code(KC_0);
          unregister_code(KC_LSHIFT);
          break;
        case 20: // F10
          register_code(KC_F10);
          unregister_code(KC_F10);
          break;
        case 25: // Undo: Ctrl-Z
          register_code(KC_LCTRL);
          register_code(KC_Z);
          unregister_code(KC_Z);
          unregister_code(KC_LCTRL);
          break;
        case 26: // Redo: Ctrl-Y
          register_code(KC_LCTRL);
          register_code(KC_Y);
          unregister_code(KC_Y);
          unregister_code(KC_LCTRL);
          break;
        }
        return MACRO_NONE;
      }
      // finish special commands

      // send normal sequence
      for (int i = 0; i < 3; i++) {
        if (seq[i] == KC_NO) {
          break;
        }
        if(isLeftCtrlPressed){
          register_code(KC_LCTRL);
          register_code(seq[i]);
          unregister_code(seq[i]);
          unregister_code(KC_LCTRL);
        }else{
          register_code(seq[i]);
          unregister_code(seq[i]);
        }
      }
    }
    return MACRO_NONE;
  }

  // update thumb shift status
  switch(id) {
  case 100:
    if(record->event.pressed){
      isLeftShiftPressed = true;
    }else{
      isLeftShiftPressed = false;
    }
    break;
  case 101:
    if(record->event.pressed){
      isRightShiftPressed = true;
    }else{
      isRightShiftPressed = false;
    }
    break;

  case 102:
    if(record->event.pressed){
      isLeftCtrlPressed = true;
    }else{
      isLeftCtrlPressed = false;
    }
    break;
  }

  return MACRO_NONE;
};


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
  switch (keycode) {
  case QWERTY:
    if (record->event.pressed) {
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
      //not sure how to have keyboard check mode and set it to a variable, so my work around
      //uses another variable that would be set to true after the first time a reactive key is pressed.
      /* if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false */
      /* } else { */
      /*   TOG_STATUS = !TOG_STATUS; */
      /*   #ifdef RGBLIGHT_ENABLE */
      /*     //rgblight_mode(RGBLIGHT_MODE_SNAKE); */
      /*   #endif */
      /* } */
      layer_on(_RAISE);
      /* update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
    } else {
#ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
#endif
      layer_off(_RAISE);
      TOG_STATUS = false;
      /* update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
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
    //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
  case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed) {
      rgblight_mode(RGB_current_mode);
      rgblight_step();
      RGB_current_mode = rgblight_config.mode;
    }
#endif
    return false;
    break;
  case EISU:
    if (record->event.pressed) {
      if(keymap_config.swap_lalt_lgui==false){
        register_code(KC_LANG2);
      }else{
        SEND_STRING(SS_LALT("`"));
      }
    } else {
      unregister_code(KC_LANG2);
    }
    return false;
    break;
  case KANA:
    if (record->event.pressed) {
      if(keymap_config.swap_lalt_lgui==false){
        register_code(KC_LANG1);
      }else{
        SEND_STRING(SS_LALT("`"));
      }
    } else {
      unregister_code(KC_LANG1);
    }
    return false;
    break;
  case OYAYUBI:
    if (record->event.pressed) {
      if (isOyayubiPressed){
        //SEND_STRING(SS_LGUI(" "));
        register_code(KC_LANG2);
        /* if(keymap_config.swap_lalt_lgui==false){ */
        /*   register_code(KC_LANG2); */
        /* }else{ */
        /*   SEND_STRING(SS_LALT("`")); */
        /* } */
        layer_off(_OYA);
      }else{
        /* if(keymap_config.swap_lalt_lgui==false){ */
        /*   register_code(KC_LANG1); */
        /* }else{ */
        /*   SEND_STRING(SS_LALT("`")); */
        /* } */
        register_code(KC_LANG1);
        //SEND_STRING(SS_LGUI(" "));
        layer_on(_OYA);
      }
      isOyayubiPressed = !isOyayubiPressed;
    }else{
      if(isOyayubiPressed){
        unregister_code(KC_LANG2);
      }else{
        unregister_code(KC_LANG1);
      }
    }
    break;
  case RGBRST:
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed) {
      eeconfig_update_rgblight_default();
      rgblight_enable();
      RGB_current_mode = rgblight_config.mode;
    }
#endif
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
#define L_OYA (1<<_OYA)
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
  switch (layer_state) {
  case L_BASE:
    matrix_write_P(matrix, PSTR("Default"));
    break;
  case L_RAISE:
    matrix_write_P(matrix, PSTR("Raise"));
    break;
  case L_LOWER:
    matrix_write_P(matrix, PSTR("Lower"));
    break;
  case L_ADJUST:
  case L_ADJUST_TRI:
    matrix_write_P(matrix, PSTR("Adjust"));
    break;
  case L_OYA:
    matrix_write_P(matrix, PSTR("OYA"));
    break;
  default:
    matrix_write(matrix, buf);
  }

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
