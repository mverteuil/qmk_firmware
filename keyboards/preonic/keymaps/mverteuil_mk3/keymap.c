/* Copyright 2015-2017 Jack Humbert
 * Copyright 2019 M. de Verteuil
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mverteuil.h"

/* Keypad aliases */
#define KC_DOLR         KC_DOLLAR
#define KC_NAST         KC_KP_ASTERISK
#define KC_NMIN         KC_KP_MINUS
#define KC_NPLU         KC_KP_PLUS
#define KC_NENT         KC_KP_ENTER
#define KC_NDOT         KC_KP_DOT
#define KC_PCNT         KC_PERCENT

/* TapDance Aliases */
#define TD_LBRK         TD(TD_BRACKETS_LEFT)
#define TD_RBRK         TD(TD_BRACKETS_RIGHT)
#define TD_CLES         TD(TD_CONTROL_ESCAPE)
#define TD_NPFR         TD(TD_NUMPAD_FUNCTIONROW)
#define TD_PLEQ         TD(TD_PLUS_EQUALS)
#define TD_SCOL         TD(TD_SEMICOLON_COLON)
#define TD_SLQU         TD(TD_SLASH_QUESTION)
#define TD_SQDQ         TD(TD_QUOTE_DOUBLEQUOTE)
#define TD_USMI         TD(TD_UNDERSCORE_MINUS)

/* Sentinel value for invalid tap dance exit */
#define TAP_DANCE_NO_MATCH 64

enum preonic_layers {
  _QWERTY,
  _FUNCTIONROW,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD,
  LOWER,
  RAISE,
  BACKLIT,
};

enum tapdance_keycodes {
  TD_BRACKETS_LEFT,
  TD_BRACKETS_RIGHT,
  TD_CONTROL_ESCAPE,
  TD_NUMPAD_FUNCTIONROW,
  TD_PLUS_EQUALS,
  TD_QUOTE_DOUBLEQUOTE,
  TD_SEMICOLON_COLON,
  TD_SLASH_QUESTION,
  TD_UNDERSCORE_MINUS,
};

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP,
  TRIPLE_HOLD,
} t_tap_state;

typedef struct {
  t_tap_state left_brackets;
  t_tap_state numpad_funcrow;
  t_tap_state right_brackets;
} t_tap;

t_tap_state get_tapdance_state (qk_tap_dance_state_t *state);
void td_numpad_funcrow_finished (qk_tap_dance_state_t *state, void *user_data);
void td_numpad_funcrow_reset (qk_tap_dance_state_t *state, void *user_data);
void td_brackets_left_finished (qk_tap_dance_state_t *state, void *user_data);
void td_brackets_left_reset (qk_tap_dance_state_t *state, void *user_data);
void td_brackets_right_finished (qk_tap_dance_state_t *state, void *user_data);
void td_brackets_right_reset (qk_tap_dance_state_t *state, void *user_data);

/* Tap Dance Definitions */
qk_tap_dance_action_t tap_dance_actions[] = {
                          /* Tap once for left parenthesis, twice for left bracket, thrice for left brace */
  [TD_BRACKETS_LEFT]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_left_finished, td_brackets_left_reset),
                          /* Tap once for right parenthesis, twice for right bracket, thrice for right brace */
  [TD_BRACKETS_RIGHT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_right_finished, td_brackets_right_reset),
                          /* Tap once for control, twice for escape */
  [TD_CONTROL_ESCAPE]     = ACTION_TAP_DANCE_DOUBLE(KC_LCTRL, KC_ESCAPE),
                          /* Tap once for plus, twice for equals */
  [TD_PLUS_EQUALS]        = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_EQUAL),
                          /* Hold for numpad, tap twice to toggle function row, double hold for temporary function row */
  [TD_NUMPAD_FUNCTIONROW] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_numpad_funcrow_finished, td_numpad_funcrow_reset),
                          /* Tap once for single quote, twice for double quote */
  [TD_QUOTE_DOUBLEQUOTE]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE),
                          /* Tap once for semicolon, twice for colon */
  [TD_SEMICOLON_COLON]    = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
                          /* Tap once for slash, twice for question mark */
  [TD_SLASH_QUESTION]     = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_QUESTION),
                          /* Tap once for underscore, twice for minus */
  [TD_UNDERSCORE_MINUS]   = ACTION_TAP_DANCE_DOUBLE(KC_UNDERSCORE, KC_MINUS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  | _  - | +  = | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | '  " |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CtlEsc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | ;  : | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | GUI  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |NP FRw| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | /  ? | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_1x2uC ( \
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DOLR, KC_PCNT, KC_CIRC, KC_AMPR, KC_ASTR, TD_USMI, TD_PLEQ, KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD_SQDQ, \
  TD_CLES, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD_SCOL, KC_ENT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RGUI, \
  TD_NPFR, KC_LCTL, KC_LALT, KC_LGUI, LOWER,        KC_SPC,      RAISE,   TD_SLQU, KC_LEFT, KC_DOWN, KC_RGHT  \
),

/* Function Row
 * ,-----------------------------------------------------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTIONROW] = LAYOUT_preonic_1x2uC ( \
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______  \
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |  Tab |   /  |   *  | Bksp | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |   -  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  | PgUp |Insert|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |   0  |   .  | Home | PgDn |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_1x2uC ( \
  _______, _______, _______, _______, _______, _______, _______, KC_TAB,  KC_SLSH, KC_NAST, KC_BSPC, KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_NMIN, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_NPLU, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PGUP, KC_INS,  \
  _______, _______, _______, _______, _______,     _______,      KC_KP_0, KC_NDOT, KC_HOME, KC_PGDN, KC_END   \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol+ |      |      |      |      |      |      |      | Play |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Prev | Vol- | Next |      |      |   ?  |   _  |   +  |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mute |      |      | PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   \  | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_1x2uC ( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, \
  _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, KC_QUES, KC_UNDS, KC_PLUS, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, KC_PGUP, _______, \
  _______, _______, _______, _______, _______,     _______,      _______, KC_BSLS, KC_HOME, KC_PGDN, KC_END   \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | [ { (| ) } ]|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   |  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_1x2uC ( \
  KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, TD_LBRK, TD_RBRK, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______,     _______, KC_PIPE, _______, _______, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |AudTog|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX| Debug| Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ClkTog|ClkFq-|ClkFq+|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|TermOn|TermOf|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |MusTog|Voice- Voice+|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|AGnorm|AGswap|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |MidTog|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |XXXXXX|XXXXXX|XXXXXX|XXXXXX|      |             |      |XXXXXX|XXXXXX|XXXXXX|XXXXXX|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_1x2uC ( \
  AU_TOG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,   RESET,   \
  CK_TOGG, CK_DOWN, CK_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TERM_ON, TERM_OFF,\
  MU_TOG,  MUV_DE,  MUV_IN,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_NORM, AG_SWAP, \
  MI_TOG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,      XXXXXXX,     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
)

};

float s_audio_on[][2] = AUDIO_ON_SONG;
float s_layer_lower[][2] = LAYER_LOWER_SONG;
float s_layer_raise[][2] = LAYER_RAISE_SONG;

void audio_on_user() {
    PLAY_SONG(s_audio_on);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            PLAY_SONG(s_layer_lower);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            PLAY_SONG(s_layer_raise);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

/* Global TapDance State */
static t_tap qk_tap_state = {
    .left_brackets = 0,
    .numpad_funcrow = 0,
    .right_brackets = 0,
};

float s_functionrow_on[][2] = LAYER_FUNCROW_ON_SONG;
float s_functionrow_off[][2] = LAYER_FUNCROW_OFF_SONG;
float s_numpad_toggle[][2] = LAYER_NMPAD_SONG;

t_tap_state get_tapdance_state (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    if (state->interrupted || !state->pressed) {
      return DOUBLE_TAP;
    } else {
      return DOUBLE_HOLD;
    }
  } else if (state->count == 3) {
    if (state->interrupted || !state->pressed) {
       return TRIPLE_TAP;
    } else {
       return TRIPLE_HOLD;
    }
  }
  else return TAP_DANCE_NO_MATCH;
}

void td_numpad_funcrow_finished (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_state.numpad_funcrow = get_tapdance_state(state);
  switch (qk_tap_state.numpad_funcrow) {
    case SINGLE_TAP ... SINGLE_HOLD:
      layer_on(_NUMPAD);
      PLAY_SONG(s_numpad_toggle);
      break;
    case DOUBLE_HOLD:
      layer_on(_FUNCTIONROW);
      break;
    case DOUBLE_TAP:
      if (layer_state_is(_FUNCTIONROW)) {
        layer_off(_FUNCTIONROW);;
        PLAY_SONG(s_functionrow_off);
      } else {
        layer_on(_FUNCTIONROW);
        PLAY_SONG(s_functionrow_on);
      }
      break;
    default: break;
  }
}

void td_numpad_funcrow_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (qk_tap_state.numpad_funcrow) {
    case SINGLE_HOLD:
      layer_off(_NUMPAD);
      break;
    case DOUBLE_HOLD:
      layer_off(_FUNCTIONROW);
      break;
    default: break;
  }
}


void td_brackets_left_finished (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_state.left_brackets = get_tapdance_state(state);
  switch (qk_tap_state.left_brackets) {
      case SINGLE_TAP: register_left_paren(); break;
      case DOUBLE_TAP: register_code(KC_LBRC); break;
      case TRIPLE_TAP: register_left_brace(); break;
      default: break;
  }
}

void td_brackets_left_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (qk_tap_state.left_brackets) {
      case SINGLE_TAP: unregister_left_paren(); break;
      case DOUBLE_TAP: unregister_code(KC_LBRC); break;
      case TRIPLE_TAP: unregister_left_brace(); break;
      default: break;
  }
  qk_tap_state.left_brackets = 0;
}

void td_brackets_right_finished (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_state.right_brackets = get_tapdance_state(state);
  switch (qk_tap_state.right_brackets) {
      case SINGLE_TAP: register_right_paren(); break;
      case DOUBLE_TAP: register_code(KC_RBRC); break;
      case TRIPLE_TAP: register_right_brace(); break;
      default: break;
  }
}

void td_brackets_right_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (qk_tap_state.right_brackets) {
      case SINGLE_TAP: unregister_right_paren(); break;
      case DOUBLE_TAP: unregister_code(KC_RBRC); break;
      case TRIPLE_TAP: unregister_right_brace(); break;
      default: break;
  }
  qk_tap_state.right_brackets = 0;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
