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
#include "mverteuil.h"

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
    _SPECTACLE,
    _MINECRAFT,
    _RGB,
};

enum custom_keycodes {
    CURRENT_SELECTION = SAFE_RANGE,
    CLONE_SELECTION,
    CURRENT_PLACEMENT,
    LITEMATICA_OPTIONS,
    TWEAKEROO_OPTIONS,
    MINIHUD_OPTIONS,
    PERIODIC_USE,
    PERIODIC_ATTACK,
    SNEAK_PLACEMENT,
};

uint8_t currentLayer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_SPECTACLE] = LAYOUT(
        MAXIMIZ, NXTDSPL, _______, TO(_SPECTACLE),
        BTMHALF, TOPHALF, _______, TO(_MINECRAFT),
        NXTTHRD, PRVTHRD, _______, TO(_RGB),
        K_CUT,   K_COPY,  K_PASTE
    ),
    [_MINECRAFT] = LAYOUT(
        KC_RCTL,            KC_ROPT,           KC_RCMD,           _______,
        CURRENT_SELECTION,  CLONE_SELECTION,   CURRENT_PLACEMENT, _______,
        LITEMATICA_OPTIONS, TWEAKEROO_OPTIONS, MINIHUD_OPTIONS,   _______,
        PERIODIC_ATTACK,    PERIODIC_USE,      SNEAK_PLACEMENT
    ),
    [_RGB] = LAYOUT(
        RGB_HUI,  RGB_SAI, RGB_VAI, KC_TRNS,
        RGB_HUD,  RGB_SAD, RGB_VAD, KC_TRNS,
        KC_NO,    KC_NO,   KC_NO,   KC_TRNS,
        RGB_RMOD, RGB_TOG, RGB_MOD
    ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CURRENT_SELECTION: if (record->event.pressed) {
            register_code(KC_M);
            register_code(KC_C);
            tap_code(KC_S);
            unregister_code(KC_M);
            unregister_code(KC_C);
        } break;
        case CLONE_SELECTION: if (record->event.pressed) {
            register_code(KC_M);
            tap_code(KC_QUOTE);
            unregister_code(KC_M);
        } break;
        case CURRENT_PLACEMENT: if (record->event.pressed) {
            register_code(KC_M);
            register_code(KC_C);
            tap_code(KC_P);
            unregister_code(KC_M);
            unregister_code(KC_C);
        } break;
        case LITEMATICA_OPTIONS: if (record->event.pressed) {
            register_code(KC_M);
            tap_code(KC_C);
            unregister_code(KC_M);
        } break;
        case TWEAKEROO_OPTIONS: if (record->event.pressed) {
            register_code(KC_X);
            tap_code(KC_C);
            unregister_code(KC_X);
        } break;
        case MINIHUD_OPTIONS: if (record->event.pressed) {
            register_code(KC_H);
            tap_code(KC_C);
            unregister_code(KC_H);
        } break;
        case PERIODIC_ATTACK: if (record->event.pressed) {
            register_code(KC_X);
            register_code(KC_P);
            tap_code(KC_A);
            unregister_code(KC_X);
            unregister_code(KC_P);
        } break;
        case PERIODIC_USE: if (record->event.pressed) {
            register_code(KC_X);
            register_code(KC_P);
            tap_code(KC_U);
            unregister_code(KC_X);
            unregister_code(KC_P);
        } break;
        case SNEAK_PLACEMENT: if (record->event.pressed) {
            register_code(KC_X);
            register_code(KC_F);
            tap_code(KC_S);
            unregister_code(KC_X);
            unregister_code(KC_F);
        } break;
    }
    return true;
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        switch (get_highest_layer(layer_state)) {     //break each encoder update into a switch statement for the current layer
            case _SPECTACLE:
                if (clockwise) {
                    tap_code(KC_DOWN);
                } else {
                    tap_code(KC_UP);
                }
                break;
            case _MINECRAFT:
                if (clockwise) {
                    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_WH_U) SS_UP(X_LCTRL));
                } else {
                    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_WH_U) SS_UP(X_LCTRL));
                }
                break;
            case _RGB:
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
        }
    } else if (index == 1) { /* Second encoder */
        switch (get_highest_layer(layer_state)) {
            case _SPECTACLE:
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            case _MINECRAFT:
                register_code(KC_M);
                register_code(KC_COMMA);
                if (clockwise) {
                    tap_code(KC_UP);
                } else {
                    tap_code(KC_DOWN);
                }
                unregister_code(KC_M);
                unregister_code(KC_COMMA);
                break;
            case _RGB:
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                break;
        }
    } else if (index == 2) { /* Third encoder */
        switch (get_highest_layer(layer_state)) {
            case _SPECTACLE:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _MINECRAFT:
                register_code(KC_M);
                if (clockwise) {
                    tap_code(KC_UP);
                } else {
                    tap_code(KC_DOWN);
                }
                unregister_code(KC_M);
                break;
            case _RGB:
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
                break;
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) { //This will run every time the layer is updated
    switch (get_highest_layer(state)) {
        case _SPECTACLE:
            setrgb(RGB_WHITE, &led[0]); //Set the top LED to white for the bottom layer
            setrgb(0, 0, 0, &led[1]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case _MINECRAFT:
            setrgb(0, 0, 0, &led[0]); //Set the middle LED to white for the middle layer
            setrgb(RGB_WHITE, &led[1]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case _RGB:
            setrgb(0, 0, 0, &led[0]);
            setrgb(0, 0, 0, &led[1]);
            setrgb(RGB_WHITE, &led[2]); //Set the bottom LED to white for the top layer
            break;
    }
    rgblight_set();
    return state;
}

#ifdef OLED_DRIVER_ENABLE

static const char *ANIMATION_NAMES[] = {
	"unknown",
	"static",
	"breathing I",
	"breathing II",
	"breathing III",
	"breathing IV",
	"rainbow mood I",
	"rainbow mood II",
	"rainbow mood III",
	"rainbow swirl I",
	"rainbow swirl II",
	"rainbow swirl III",
	"rainbow swirl IV",
	"rainbow swirl V",
	"rainbow swirl VI",
	"snake I",
	"snake II",
	"snake III",
	"snake IV",
	"snake V",
	"snake VI",
	"knight I",
	"knight II",
	"knight III",
	"christmas",
	"static gradient I",
	"static gradient II",
	"static gradient III",
	"static gradient IV",
	"static gradient V",
	"static gradient VI",
	"static gradient VII",
	"static gradient VIII",
	"static gradient IX",
	"static gradient X",
	"rgb test",
	"alternating",
	"twinkle I",
	"twinkle II",
	"twinkle III",
	"twinkle IV",
	"twinkle V",
	"twinkle VI"
};

void rgblight_get_mode_name(uint8_t mode, size_t bufsize, char *buf) {
    snprintf(buf, bufsize, "%-25s", ANIMATION_NAMES[mode]);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef LEFT_HAND
    return OLED_ROTATION_180;
#else
    return OLED_ROTATION_0;
#endif
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _SPECTACLE:
            oled_write_P(PSTR("Spectacles\n"), false);
            break;
        case _MINECRAFT:
            oled_write_P(PSTR("Minecraft\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("RGB\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    static char rgb_mode_name[30];
    rgblight_get_mode_name(rgblight_get_mode(), sizeof(rgb_mode_name), rgb_mode_name);

    oled_write_P(PSTR("Mode: "), false);
    oled_write_ln(rgb_mode_name, false);
}
#endif
