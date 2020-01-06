#include QMK_KEYBOARD_H
#include <print.h>

#define MAXIMIZ A(G(KC_F))
#define NXTDSPL C(A(G(KC_RIGHT)))
#define BTMHALF A(G(KC_DOWN))
#define TOPHALF A(G(KC_UP))
#define NXTTHRD SS_DOWN(X_LCTRL)SS_DOWN(X_LALT)SS_TAP(X_RIGHT)SS_UP(X_LALT)SS_UP(X_LCTRL)
#define PRVTHRD C(A(KC_LEFT))

#define LT_MSTP LT(3, KC_MSTP)
#define LT_ESC  LT(3, KC_ESC)
#define LT_NXTH TD(TD_SPEC)

enum {
  TD_SPEC = 0
};

void td_spectacles_finish(qk_tap_dance_state_t *state, void *user_data);
void td_spectacles_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SPEC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_spectacles_finish, td_spectacles_reset)
};


void led_set_layer(int layer);

/* clang-format off */
/*
 *   Key Layout
 *	 _____	 _____	 _____
 *	| 	  | | 	  | | 	  |
 *	|  1  | |  2  | |  3  |
 *	|_____| |_____| |_____|
 *	 _____	 _____	 _____
 *	| 	  | | 	  | | 	  |
 *	|  4  | |  5  | |  6  |
 *	|_____| |_____| |_____|
 *
 *  Each Layout row below keys. 1,2,3,4,5,6
 *
 *  Hold 3 when powering on for DFU Program Mode
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     *   Layer 0 (Media Keys)
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	 Stop    VolUp   Play
     *	|_____| |_____| |_____|
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	 Prev    VolDwn  Next
     *	|_____| |_____| |_____|
     *
     */
    LAYOUT(
        LT_MSTP, KC_VOLU, KC_MPLY,
        KC_MPRV, KC_VOLD, KC_MNXT
    ),

    /*
     *   Layer 1 (Copy and Paste Macros)
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	  ESC    Ctl+Z   CSf+Z
     *	|_____| |_____| |_____|
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	 Ctl+X   Ctl+C   Ctl+V
     *	|_____| |_____| |_____|
     *
     */

    LAYOUT(
        LT_ESC,  C(KC_Z), C(S(KC_Z)),
        C(KC_X), C(KC_C), C(KC_V)
    ),

    /*
     *   Layer 2 (Spectacles Macros)
     *	 _LT&__	 _____	 _____
     *	| Win | | Win | | Win |
     *	| Next| | Top | |Mximze
     *	|_1/3_| |_1/2_| |_____|
     *	 _____	 _____	 _____
     *	| Win | | Win | | Win |
     *	| Prev| | Bot | | Next|
     *	|_1/3_| |_1/2_| |Displ|
     *
     */
    LAYOUT(
        LT_NXTH,TOPHALF,MAXIMIZ,
        PRVTHRD,BTMHALF,NXTDSPL
    ),

    /*
     *  Layer 3 (Layer Select/Reset)
     *	 _____	 _____	 _____
     *	| 	  | | 	  | |     |
     *	|None | |None | |Reset|
     *	|_____| |_____| |_____|
     *	 _____	 _____	 _____
     *	|Layer| |Layer| |Layer|
     *  |  0  | |  1  | |  2  |
     *	|_____| |_____| |_____|
     *
     *  Layers 0, 1, and 2 have the top left button held to activate this layer.
     *  Then press the specific layer to switch to it.
     *
     */
    LAYOUT(
        _______, _______, RESET,
        TO(0),   TO(1),   TO(2)
    )

};
/* clang-format on */

/*
 *	Knops Mini LED Numbers:
 *	 _____	 _____	 _____
 *	| 	  | | 	  | | 	  |
 *	|  1  | |  2  | |  3  |    <---
 *	|_____| |_____| |_____|       |      These LEDs are called 'Switch LEDs'
 *	 _____	 _____	 _____        |----- To turn on/off these leds, use:
 *	| 	  | | 	  | | 	  |       |	  set_switch_led( [1-6], [true/false]);
 *	|  4  | |  5  | |  6  |    <---
 *	|_____| |_____| |_____|
 *
 *	 < 0 >   < 1 >   < 2 >     <---      These front-LEDs are called 'Layer LEDs'
 *							             To turn one of them on, use:
 *										 set_layer_led( [0-2] );
 */

void set_switch_led(int ledId, bool state) {
    if (state) {
        switch (ledId) {
            case 1:
                PORTD |= (1 << 7);
                break;
            case 2:
                if ((PINB & (1 << 7)) != 0) {
                    PORTC |= (1 << 6);
                } else {
                    PORTC |= (1 << 7);
                }
                break;
            case 3:
                PORTD |= (1 << 4);
                break;
            case 4:
                PORTE |= (1 << 6);
                break;
            case 5:
                PORTB |= (1 << 4);
                break;
            case 6:
                PORTD |= (1 << 6);
                break;
        }
    } else {
        switch (ledId) {
            case 1:
                PORTD &= ~(1 << 7);
                break;
            case 2:
                if ((PINB & (1 << 7)) != 0) {
                    PORTC &= ~(1 << 6);
                } else {
                    PORTC &= ~(1 << 7);
                }
                break;
            case 3:
                PORTD &= ~(1 << 4);
                break;
            case 4:
                PORTE &= ~(1 << 6);
                break;
            case 5:
                PORTB &= ~(1 << 4);
                break;
            case 6:
                PORTD &= ~(1 << 6);
                break;
        }
    }
}

void set_layer_led(int layerId, bool layerState) {
	PORTD |= (1<<5);
	PORTB &= ~(1<<6);
	PORTB |= (1<<0);

    if (layerState) {
        switch (layerId) {
            case 0:
                PORTD &= ~(1 << 5);
                break;
            case 1:
                PORTB |= (1 << 6);
                break;
            case 2:
                PORTB &= ~(1 << 0);
                break;
            case 3:
                PORTD &= ~(1 << 5);
                PORTB |= (1 << 6);
                PORTB &= ~(1 << 0);
                break;
        }
    } else {
        switch (layerId) {
            case 0:
                PORTD |= (1 << 5);
                break;
            case 1:
                PORTB &= ~(1 << 6);
                break;
            case 2:
                PORTB |= (1 << 0);
                break;
            case 3:
                PORTD |= (1 << 5);
                PORTB &= ~(1 << 6);
                PORTB |= (1 << 0);
                break;
        }
    }
}

/*
 * This function led_set_layer gets called when you switch between layers.
 * It allows you to turn on and off leds for each different layer and do
 * other cool stuff.
 */
void led_set_layer(int layer) {
    switch (layer) {
        case 0:
            set_switch_led(1, true);
            set_switch_led(2, true);
            set_switch_led(3, true);
            set_switch_led(4, true);
            set_switch_led(5, false);
            set_switch_led(6, false);
            break;

        case 1:
            set_switch_led(1, true);
            set_switch_led(2, true);
            set_switch_led(3, true);
            set_switch_led(4, false);
            set_switch_led(5, true);
            set_switch_led(6, false);
            break;

        case 2:
            set_switch_led(1, true);
            set_switch_led(2, true);
            set_switch_led(3, true);
            set_switch_led(4, false);
            set_switch_led(5, false);
            set_switch_led(6, true);
            break;

        case 3:
            set_switch_led(1, false);
            set_switch_led(2, false);
            set_switch_led(3, true);
            set_switch_led(4, true);
            set_switch_led(5, true);
            set_switch_led(6, true);
            break;
    }
}

void led_init_ports() {
	PORTB |= (1 << 7);
	DDRB &= ~(1<<7);

	DDRD |= (1<<7);
	DDRC |= (1<<6);
	DDRC |= (1<<7);
	DDRD |= (1<<4);
	DDRE |= (1<<6);
	DDRB |= (1<<4);
	DDRD |= (1<<6);

	DDRD |= (1<<5);
	DDRB |= (1<<6);
	DDRB |= (1<<0);

    led_set_layer(0);
    _delay_ms(200);
    led_set_layer(1);
    _delay_ms(200);
    led_set_layer(2);
    _delay_ms(200);
    led_set_layer(0);
}


// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
layer_state_t layer_state_set_user(layer_state_t state) {
    // There is no layer "0", it's always at least 1
    if (state == 0) state = 1;

    // Check for active layers, layers are indicated by active bits
    // i.e. 0001 = just 1, 0011 = 1 and 2, 0010 = just 2, etc.
    for (int i = 0; i < 4; i++) {
        bool isActive = (state & 1 << i) == 1 << i;
        set_layer_led(i, isActive);
        if (isActive) led_set_layer(i);
    }

    return state;
}

// Runs state check and changes underglow color and animation
layer_state_t default_layer_state_set_user(layer_state_t state) {
    return state;
}

void matrix_init_kb(void) {
    led_init_ports();

    PORTB |= (1 << 7);
    DDRB &= ~(1 << 7);

    PORTD |= (1 << 7);
    PORTC |= (1 << 6);
    PORTC |= (1 << 7);
    PORTD |= (1 << 4);
    PORTE |= (1 << 6);
    PORTB |= (1 << 4);
    PORTD |= (1 << 6);

    led_set_layer(0);
}

void matrix_scan_user(void) {
}

void td_spectacles_finish(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(3);
    } else {
        SEND_STRING(NXTTHRD);
    }
}

void td_spectacles_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_off(3);
}
