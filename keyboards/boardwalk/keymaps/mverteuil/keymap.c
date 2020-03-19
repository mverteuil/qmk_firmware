/*
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
#include "config.h"
#include "mverteuil.h"


/* TapDance Aliases */
#define TD_LBRK TD(TD_BRACKETS_LEFT)
#define TD_RBRK TD(TD_BRACKETS_RIGHT)
#define TD_PLEQ TD(TD_PLUS_EQUALS)
#define TD_SCOL TD(TD_SEMICOLON_COLON)
#define TD_SLQU TD(TD_SLASH_QUESTION)
#define TD_SQDQ TD(TD_QUOTE_DOUBLEQUOTE)
#define TD_USMI TD(TD_UNDERSCORE_MINUS)


/* Sentinel value for invalid tap dance exit */
#define TAP_DANCE_NO_MATCH 64

enum unicode_names {
    CAT,
    CAT2,
};

const uint32_t PROGMEM unicode_map[] = {
    [CAT]  = 0x1F431,
    [CAT2] = 0x1F408,
};

enum boardwalk_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _ARROWS
};

enum boardwalk_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    ARROWS
};

/* Layer Aliases */
#define LT_LWSP LT(_LOWER, KC_SPACE)
#define LT_RSSP LT(_RAISE, KC_SPACE)
#define MO_LUDR MO(_ARROWS)

/* Mod-Tap Aliases */
#define MT_CESC CTL_T(KC_ESCAPE)

enum tapdance_keycodes {
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
    /* Tap once for left parenthesis, twice for left bracket, thrice for left brace */
    [TD_BRACKETS_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_left_finished, td_brackets_left_reset),
    /* Tap once for right parenthesis, twice for right bracket, thrice for right brace */
    [TD_BRACKETS_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_right_finished, td_brackets_right_reset),
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

// Mac sleep
#define __SLEEP S(LCTL(KC_POWER))

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | `      | !      | @      | #      | $      | %      | -      | =      | ^      | &      | *      | _ -    | + =    | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | HOME   | END    | Y      | U      | I      | O      | P      | ' "    |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------+-----------------+--------|
     * | CTL/ESC| A      | S      | D      | F      | G      +--------+--------+ H      | J      | K      | L      | ; :    | ENTER  |
     * |--------+--------+--------+--------+--------+--------| ( [ {  | ) ] }  |--------+--------+--------------------------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      |        |        | N      | M      | ,      | .      | / ?    | RSHIFT |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
     * | 🐱     | ADJUST | LALT   | ARROWS | GUI    | LOWER/SPACE     | RAISE/SPACE     | LEFT   | UP     | DOWN   | RIGHT  |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_ortho_2u_ergo(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_MINS, KC_EQL,  KC_CIRC, KC_AMPR, KC_ASTR, TD_USMI, TD_PLEQ, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_HOME, KC_END,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD_SQDQ,
        MT_CESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    TD_SCOL, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TD_LBRK, TD_RBRK, KC_N,    KC_M,    KC_COMM, KC_DOT,  TD_SLQU, KC_RSFT,
        X(CAT),  ADJUST,  KC_LALT, MO_LUDR, KC_LGUI,     LT_LWSP,          LT_RSSP,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
    ),

    /* Lower Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * |        | 1      | 2      | 3      | 4      | 5      | (      | )      | 6      | 7      | 8      | 9      | 0      | DELETE |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        |        | PREV   | NEXT   |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------+-----------------+--------|
     * |        | VOL -  | VOL +  | MUTE   | PLAY   |        +--------+--------+        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
     * | 🐈     |        |        |        |        |                 |                 | HOME   | PGDN   | PGUP   | END    |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_ortho_2u_ergo(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LPRN, KC_RPRN, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DELT,
        _______, _______, _______, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______,
        X(CAT2), _______, _______, _______, _______,     _______,          _______,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______
    ),


    /* Raise Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * |        | F1     | F2     | F3     | F4     | F5     |        |        | F6     | F7     | F8     | F9     | F10    |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        +--------+--------+ -      | =      | {      | }      |        |        |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        | `      | \      |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
     * | 🐈     |        |        |        |        |                 |                 |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_ortho_2u_ergo(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_GRV,  KC_BSLS, _______, KC_PIPE, _______,
        X(CAT2), _______, _______, _______, _______,     _______,          _______,      _______, _______, _______, _______, _______
    ),

    /* Adjust Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | SLEEP  |        |        |        |        |        |RGBTOGGL| MODE - |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        |        |        |        | SAT +  | SAT -  | HUE -  | HUE +  |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        +--------+--------+        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------| VAL -  | VAL +  |--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
     * | RESET  |        |        |        |        |                 |                 |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_ortho_2u_ergo(
        __SLEEP, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, RGB_SAI, RGB_SAD, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______,
        RESET,   _______, _______, _______, _______,     _______,          _______,      _______, _______, _______, _______, _______
    ),

    /* Arrows Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        |        |        |        |        |        |        |        |        | UP     |        |        |        |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        +--------+--------+        | LEFT   | DOWN   | RIGHT  |        |        |
     * |--------+--------+--------+--------+--------+--------|        |        |--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |                 |                 |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_ARROWS] = LAYOUT_ortho_2u_ergo(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______,          _______,      _______, _______, _______, _______, _______
    )
};
/* clang-format on */

void matrix_init_user() {
    wait_ms(500); // USB init time
    set_unicode_input_mode(UC_OSX);
}

layer_state_t layer_state_set_user (layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
        case RAISE:
            return false;
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
