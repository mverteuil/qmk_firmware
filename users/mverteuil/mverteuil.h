#include QMK_KEYBOARD_H
#include "bad_songs.h"
#include "muse.h"
#include "song_list.h"

#pragma once
#define LOWER_SOUND S__NOTE(_EF5), W__NOTE(_REST), Q__NOTE(_E4)
#define NUMPAD_SOUND S__NOTE(_DF5), S__NOTE(_REST), S__NOTE(_C6)
#define RAISE_SOUND S__NOTE(_E4), W__NOTE(_REST), Q__NOTE(_EF5)

#define AUDIO_ON_SONG SONG(BS_ZELDA_PUZZLE)
#define GOODBYE_SONG SONG(BS_COIN_SOUND)
#define LAYER_FUNCROW_ON_SONG SONG(COLEMAK_SOUND)
#define LAYER_FUNCROW_OFF_SONG SONG(QWERTY_SOUND)
#define LAYER_NMPAD_SONG SONG(NUMPAD_SOUND)
#define LAYER_LOWER_SONG SONG(LOWER_SOUND)
#define LAYER_RAISE_SONG SONG(RAISE_SOUND)
#define STARTUP_SONG SONG(WORKMAN_SOUND)

void register_left_brace(void);
void register_left_paren(void);
void register_right_brace(void);
void register_right_paren(void);

void unregister_left_brace(void);
void unregister_left_paren(void);
void unregister_right_brace(void);
void unregister_right_paren(void);
