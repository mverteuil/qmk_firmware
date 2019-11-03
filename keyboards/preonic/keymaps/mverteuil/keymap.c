/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD,
  LOWER,
  RAISE,
  BACKLIT
};

enum tapdance_keycodes {
  TD_SEMICOLON_COLON,
  TD_SLASH_QUESTION
};

/* Tap Dance Definitions */
qk_tap_dance_action_t tap_dance_actions[] = {
                          /* Tap once for semicolon, twice for colon */
  [TD_SEMICOLON_COLON]  = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
                          /* Tap once for slash, twice for question mark */
  [TD_SLASH_QUESTION]   = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_QUESTION)
};


/* Keypad aliases */
#define KC_NAST         KC_KP_ASTERISK
#define KC_NMIN         KC_KP_MINUS
#define KC_NPLU         KC_KP_PLUS
#define KC_NENT         KC_KP_ENTER
#define KC_NDOT         KC_KP_DOT
#define TD_SCOL         TD(TD_SEMICOLON_COLON)
#define TD_SLQU         TD(TD_SLASH_QUESTION)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   "  |   #  |   $  |   %  |   ^  |   &  |   *  |   _  |   -  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   "  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | ;  : | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | /  ? |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Numpad| Esc  | Alt  | GUI  |Lower |    Space    |Raise |  GUI | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_EXLM, KC_DQUO, KC_HASH,KC_DOLLAR,KC_PERCENT,KC_CIRC,KC_AMPR,KC_ASTR, KC_UNDS, KC_MINS, KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT, \
  KC_LCTRL,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD_SCOL, KC_ENT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   TD_SLQU, \
  NUMPAD,  KC_ESC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT  \
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |  Tab |   /  |   *  | Bksp |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |   7  |   8  |   9  |   -  |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |   4  |   5  |   6  |   +  |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |   1  |   2  |   3  | Enter|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      0      |   .  | Enter|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, KC_TAB,  KC_SLSH, KC_NAST, KC_BSPC, _______, _______, _______,  \
  _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_NMIN, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_NPLU, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_NENT, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_KP_0, KC_KP_0, KC_NDOT, KC_NENT, _______, _______, _______  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol+ |      |      |      |      |      |      |      | Play |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Prev | Vol- | Next |      |      |   ?  |   _  |   +  |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mute |      |      | PgUp |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
  _______, _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, \
  _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, KC_QUES, KC_UNDS, KC_PLUS, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, KC_PGUP, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END   \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |   {  |   }  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Insert|      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, \
  _______, _______, _______, _______, _______, _______, KC_SLSH, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, \
  _______, KC_INS,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |             |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|Clk on|ClkOff|ClkFq-|ClkFq+|      |TermOn|TermOf|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, RESET,   DEBUG,   CK_ON,   CK_OFF,  CK_DOWN, CK_UP,   _______, TERM_ON,TERM_OFF, _______, _______, \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case NUMPAD:
          if (record->event.pressed) {
            layer_on(_NUMPAD);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_NUMPAD);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
