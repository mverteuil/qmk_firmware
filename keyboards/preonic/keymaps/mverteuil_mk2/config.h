#pragma once

#include "bad_songs.h"
#include "song_list.h"

#ifdef AUDIO_ENABLE
    #define AUDIO_CLICKY_FREQ_MIN 60.0f
    #define AUDIO_CLICKY_FREQ_DEFAULT 60.0f
    #define DAC_SAMPLE_MAX 16383U

    #define STARTUP_SONG SONG(PLANCK_SOUND)
    #define GOODBYE_SONG SONG(BS_COIN_SOUND)
    #define AUDIO_ON_SONG SONG(BS_ZELDA_PUZZLE)
    #define LAYER_LOWER_SONG SONG(NUM_LOCK_ON_SOUND)
    #define LAYER_RAISE_SONG SONG(NUM_LOCK_OFF_SOUND)

#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2
