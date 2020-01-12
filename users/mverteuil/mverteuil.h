#include QMK_KEYBOARD_H
#pragma once


#if AUDIO_ENABLE
    #if __has_include("copyright.h")
    #include "copyright.h"
    #endif

    #define LOWER_SOUND S__NOTE(_EF5), W__NOTE(_REST), Q__NOTE(_E4)
    #define NUMPAD_SOUND S__NOTE(_DF5), S__NOTE(_REST), S__NOTE(_C6)
    #define RAISE_SOUND S__NOTE(_E4), W__NOTE(_REST), Q__NOTE(_EF5)

    #define AUDIO_ON_SONG SONG(ZELDA_PUZZLE)
    #define LAYER_FUNCROW_ON_SONG SONG(COLEMAK_SOUND)
    #define LAYER_FUNCROW_OFF_SONG SONG(QWERTY_SOUND)
    #define LAYER_NMPAD_SONG SONG(NUMPAD_SOUND)
    #define LAYER_LOWER_SONG SONG(LOWER_SOUND)
    #define LAYER_RAISE_SONG SONG(RAISE_SOUND)
#else
    #ifndef PLAY_SONG
    // No-op version of PLAY_SONG instead of many checks for AUDIO_ENABLED
    #define PLAY_SONG(ARG) // ARG
    #endif
#endif

/* Keypad aliases */
#define KC_DOLR         KC_DOLLAR
#define KC_NAST         KC_KP_ASTERISK
#define KC_NMIN         KC_KP_MINUS
#define KC_NPLU         KC_KP_PLUS
#define KC_NENT         KC_KP_ENTER
#define KC_NDOT         KC_KP_DOT
#define KC_PCNT         KC_PERCENT


void register_left_brace(void);
void register_left_paren(void);
void register_right_brace(void);
void register_right_paren(void);
void unregister_left_brace(void);
void unregister_left_paren(void);
void unregister_right_brace(void);
void unregister_right_paren(void);
