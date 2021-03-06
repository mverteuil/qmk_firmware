/* Copyright 2015-2017 Jack Humbert, 2019 Matthew de Verteuil
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
#include "mverteuil.h"

/* Layer Aliases */
#define NUMBERS MO(_NUMBERS)

/* TapDance Aliases */
#define TD_CLES TD(TD_CONTROL_ESCAPE)
#define TD_BSPI TD(TD_BACKSLASH_PIPE)
#define TD_LBRK TD(TD_BRACKETS_LEFT)
#define TD_PLEQ TD(TD_PLUS_EQUALS)
#define TD_RBRK TD(TD_BRACKETS_RIGHT)
#define TD_SCOL TD(TD_SEMICOLON_COLON)
#define TD_SLQU TD(TD_SLASH_QUESTION)
#define TD_SQDQ TD(TD_QUOTE_DOUBLEQUOTE)
#define TD_USMI TD(TD_UNDERSCORE_MINUS)

/* Sentinel value for invalid tap dance exit */
#define TAP_DANCE_NO_MATCH 64

enum preonic_layers {
    _QWERTY,
    _NUMBERS,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum preonic_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    SPCSPAM,
    MOUSE1H,
    MS2SPAM,
};

enum tapdance_keycodes {
    TD_BACKSLASH_PIPE,
    TD_BRACKETS_LEFT,
    TD_BRACKETS_RIGHT,
    TD_CONTROL_ESCAPE,
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
    t_tap_state right_brackets;
} t_tap;

t_tap_state get_tapdance_state(qk_tap_dance_state_t *state);

void td_brackets_left_finished(qk_tap_dance_state_t *state, void *user_data);
void td_brackets_left_reset(qk_tap_dance_state_t *state, void *user_data);
void td_brackets_right_finished(qk_tap_dance_state_t *state, void *user_data);
void td_brackets_right_reset(qk_tap_dance_state_t *state, void *user_data);

/* Tap Dance Definitions */
qk_tap_dance_action_t tap_dance_actions[] = {
    /* Tap once for backslash, twice for pipe */
    [TD_BACKSLASH_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
    /* Tap once for left parenthesis, twice for left bracket, thrice for left brace */
    [TD_BRACKETS_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_left_finished, td_brackets_left_reset),
    /* Tap once for right parenthesis, twice for right bracket, thrice for right brace */
    [TD_BRACKETS_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_right_finished, td_brackets_right_reset),
    /* Tap once for control, twice for escape */
    [TD_CONTROL_ESCAPE] = ACTION_TAP_DANCE_DOUBLE(KC_LCTRL, KC_ESCAPE),
    /* Tap once for plus, twice for equals */
    [TD_PLUS_EQUALS] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_EQUAL),
    /* Tap once for single quote, twice for double quote */
    [TD_QUOTE_DOUBLEQUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE),
    /* Tap once for semicolon, twice for colon */
    [TD_SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
    /* Tap once for slash, twice for question mark */
    [TD_SLASH_QUESTION] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_QUESTION),
    /* Tap once for underscore, twice for minus */
    [TD_UNDERSCORE_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_UNDERSCORE, KC_MINUS),
};

/* Jetpack Spacebar spamming */
static bool is_spam_space_active  = false;
static bool is_spam_mouse2_active = false;
uint16_t    spam_timer            = 0;

/* Click and hold */
static bool is_lclick_and_hold_active = false;

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   '  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Jetpk|^Numbr| Alt  | GUI  |Lower |    Space    |Raise | Left | Down | Up   |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_1x2uC (
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
  TD_CLES, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,
  SPCSPAM, NUMBERS, KC_LALT, KC_LGUI, LOWER,        KC_SPC,      RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Numpad Numbers
 * ,-----------------------------------------------------------------------------------.
 * |      |   N1 |   N2 |   N3 |   N4 |   N5 |   N6 |   N7 |  N8  |   N9 |   N0 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  N-  |  N+  |  N*  |  N/  |NEnter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |  N.  |      |RCtrl |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  \ | |      |HoldM1|HoldM1|      |  Mouse2Spam |      |Insert|PrtScr|Pause |Menu  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBERS] = LAYOUT_preonic_1x2uC (
  _______, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_9,    KC_P0,   _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_PMNS, KC_PPLS, KC_PAST, KC_PSLS, KC_PENT,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PDOT, _______, KC_RCTL,
  TD_BSPI, _______, MOUSE1H, MOUSE1H, _______,      MS2SPAM,     _______, KC_INS,  KC_PSCR, KC_PAUS, KC_MENU
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  | _  - | +  = |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol+ |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- |      |      |      |   ?  |   _  |   +  |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mute |      |      |      | ROpt |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_1x2uC (
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    TD_USMI, TD_PLEQ, KC_DEL,
  _______, _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______,
  _______, _______, KC_VOLD, _______, _______, _______, KC_QUES, KC_UNDS, KC_PLUS, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, _______, KC_RALT,
  _______, _______, _______, _______, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F11 |  F12 |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | [ { (| ) } ]|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |  |   | RGUI |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_1x2uC (
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, TD_LBRK, TD_RBRK, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RGUI,
  _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |AudTog|RgbTog|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX| Debug| Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ClkTog|ClkFq-|ClkFq+|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|TermOn|TermOf|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |MusTog|Voice- Voice+|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|AGnorm|AGswap|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |MidTog|Rplain|Rbreat|Rrainb|Rswirl|Rsnake|Rkridr|Rxmas |Rgrad |RGBtst|XXXXXX|Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |RGBmod|RGBhue|RBGsat|RGBval|      |    Jetpack  |      |XXXXXX|XXXXXX|XXXXXX|XXXXXX|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_1x2uC (
  AU_TOG,  RGB_TOG, XXXXXXX, XXXXXXX, RGB_HUI, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,   RESET,
  CK_TOGG, CK_DOWN, CK_UP,   XXXXXXX, RGB_SAI, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TERM_ON, TERM_OFF,
  MU_TOG,  MUV_DE,  MUV_IN,  XXXXXXX, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_NORM, AG_SWAP,
  MI_TOG,  RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_SPI, KC_LSHIFT,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,      _______,     _______, XXXXXXX,RGB_RMOD, RGB_SPD, RGB_MOD
)

};
/* clang-format on */

float s_audio_on[][2]      = AUDIO_ON_SONG;
float s_layer_lower[][2]   = LAYER_LOWER_SONG;
float s_layer_numbers[][2] = LAYER_NUMBERS_SONG;
float s_layer_raise[][2]   = LAYER_RAISE_SONG;

void audio_on_user() { PLAY_SONG(s_audio_on); };

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
        case SPCSPAM:
            is_spam_space_active = record->event.pressed;
            spam_timer           = timer_read();
            return false;
            break;
        case MS2SPAM:
            if (record->event.pressed) {
                is_spam_mouse2_active = !is_spam_mouse2_active;
                spam_timer            = timer_read();
                return false;
                break;
            }
        case MOUSE1H:
            if (record->event.pressed) {
                is_lclick_and_hold_active = !is_lclick_and_hold_active;
                if (is_lclick_and_hold_active) {
                    register_code(KC_BTN1);
                } else {
                    unregister_code(KC_BTN1);
                }
            }
            return false;
            break;
    }
    return true;
};

/* Global TapDance State */
static t_tap qk_tap_state = {
    .left_brackets  = 0,
    .right_brackets = 0,
};

t_tap_state get_tapdance_state(qk_tap_dance_state_t *state) {
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
    } else
        return TAP_DANCE_NO_MATCH;
}

void td_brackets_left_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_state.left_brackets = get_tapdance_state(state);
    switch (qk_tap_state.left_brackets) {
        case SINGLE_TAP:
            register_code16(KC_LEFT_PAREN);
            break;
        case DOUBLE_TAP:
            register_code(KC_LBRACKET);
            break;
        case TRIPLE_TAP:
            register_code16(KC_LEFT_CURLY_BRACE);
            break;
        default:
            break;
    }
}

void td_brackets_left_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (qk_tap_state.left_brackets) {
        case SINGLE_TAP:
            unregister_code16(KC_LEFT_PAREN);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_LBRACKET);
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_LEFT_CURLY_BRACE);
            break;
        default:
            break;
    }
    qk_tap_state.left_brackets = 0;
}

void td_brackets_right_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_state.right_brackets = get_tapdance_state(state);
    switch (qk_tap_state.right_brackets) {
        case SINGLE_TAP:
            register_code16(KC_RIGHT_PAREN);
            break;
        case DOUBLE_TAP:
            register_code(KC_RBRACKET);
            break;
        case TRIPLE_TAP:
            register_code16(KC_RIGHT_CURLY_BRACE);
            break;
        default:
            break;
    }
}

void td_brackets_right_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (qk_tap_state.right_brackets) {
        case SINGLE_TAP:
            unregister_code16(KC_RIGHT_PAREN);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_RBRACKET);
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_RIGHT_CURLY_BRACE);
            break;
        default:
            break;
    }
    qk_tap_state.right_brackets = 0;
}

void matrix_scan_user(void) {
    if (is_spam_space_active) {
        if (timer_elapsed(spam_timer) > 500) {
            tap_code(KC_SPC);
        }
    } else if (is_spam_mouse2_active) {
        if (timer_elapsed(spam_timer) > 1500) {
            tap_code(KC_BTN2);
        }
    }
    if (is_lclick_and_hold_active) {
        register_code(KC_BTN1);
    }
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
