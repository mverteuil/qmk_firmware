/* Copyright 2019-2020 DMQ Design
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

#define NUMPAD TO(_NUMPAD)
#define SPCTCLE TO(_SPECTACLE)
#define MINCRFT TO(_MINECRAFT)

#define MAXIMIZ A(G(KC_F))
#define NXTDSPL C(A(G(KC_RIGHT)))
#define BTMHALF A(G(KC_DOWN))
#define TOPHALF A(G(KC_UP))
#define NXTTHRD C(A(KC_RIGHT))
#define PRVTHRD C(A(KC_LEFT))
#define K_CUT  C(KC_X)
#define K_COPY C(KC_C)
#define K_PASTE C(KC_V)

enum layers {
    _NUMPAD,
    _SPECTACLE,
    _MINECRAFT,
};

uint8_t currentLayer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT(
        KC_7,    KC_8,    KC_9,    NUMPAD,
        KC_4,    KC_5,    KC_6,    SPCTCLE,
        KC_1,    KC_2,    KC_3,    MINCRFT,
        KC_0,    KC_DOT,  KC_ENT
    ),
    [_SPECTACLE] = LAYOUT(
        MAXIMIZ, NXTDSPL, K_CUT,   _______,
        BTMHALF, TOPHALF, K_COPY,  _______,
        NXTTHRD, PRVTHRD, K_PASTE, _______,
        RGB_TOG, RGB_MOD, RGB_M_P
    ),
    [_MINECRAFT] = LAYOUT(
        KC_RCTL, KC_ROPT, KC_RCMD, _______,
        KC_BTN5, KC_DEL,  KC_PDOT, _______,
        KC_NLCK, KC_PSLS, KC_NUBS, _______,
        KC_APP,  KC_PEQL, KC_BTN4
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (currentLayer) {     //break each encoder update into a switch statement for the current layer
        case _NUMPAD:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (index == 2) {
                if (clockwise) {
                    SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB) SS_UP(X_LGUI));
                } else {
                    SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSHIFT) SS_TAP(X_TAB) SS_UP(X_LGUI) SS_UP(X_LSHIFT));
                }
            }
            break;
        case _SPECTACLE:
        case _MINECRAFT:
            if (index == 0) { /* First encoder */
                if (clockwise) {
                    rgblight_increase_hue();  // Cycle through the RGB hue
                } else {
                    rgblight_decrease_hue();
                }
            } else if (index == 1) { /* Second encoder */
                if (clockwise) {
                    tap_code(KC_VOLU);  // Example of using tap_code which lets you use keycodes outside of the keymap
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (index == 2) { /* Third encoder */
                if (clockwise) {
                    rgblight_increase_val();  // Change brightness on the RGB LEDs
                } else {
                    rgblight_decrease_val();
                }
            }
            break;

    }
}


layer_state_t layer_state_set_user(layer_state_t state) { //This will run every time the layer is updated
    currentLayer = get_highest_layer(state);

    switch (currentLayer) {
        case _NUMPAD:
            setrgb(RGB_WHITE, &led[0]); //Set the top LED to white for the bottom layer
            setrgb(0, 0, 0, &led[1]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case _SPECTACLE:
            setrgb(0, 0, 0, &led[0]); //Set the middle LED to white for the middle layer
            setrgb(RGB_WHITE, &led[1]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case _MINECRAFT:
            setrgb(0, 0, 0, &led[0]);
            setrgb(0, 0, 0, &led[1]);
            setrgb(RGB_WHITE, &led[2]); //Set the bottom LED to white for the top layer
            break;
    }
    rgblight_set();
    return state;
}
