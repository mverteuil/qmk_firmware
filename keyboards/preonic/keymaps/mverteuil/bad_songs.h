#include "musical_notes.h"

#define BS_COIN_SOUND \
    E__NOTE(_A5  ),   \
    HD_NOTE(_E6  ),
#define BS_ONE_UP_SOUND \
    Q__NOTE(_G6  ),  \
    Q__NOTE(_E7  ),  \
    Q__NOTE(_E6  ),  \
    Q__NOTE(_C7  ),  \
    Q__NOTE(_D7  ),  \
    Q__NOTE(_G7  ),

#define BS_SONIC_RING \
    E__NOTE(_E6),  \
    E__NOTE(_G6),  \
    HD_NOTE(_C7),

#define BS_ZELDA_PUZZLE \
    Q__NOTE(_G5),     \
    Q__NOTE(_FS5),    \
    Q__NOTE(_DS5),     \
    Q__NOTE(_A4),    \
    Q__NOTE(_GS4),     \
    Q__NOTE(_E5),     \
    Q__NOTE(_GS5),     \
    HD_NOTE(_C6),

#define BS_ZELDA_TREASURE \
    Q__NOTE(_A4 ), \
    Q__NOTE(_AS4), \
    Q__NOTE(_B4 ), \
    HD_NOTE(_C5 ), \

#define BS_TERMINAL_SOUND \
    E__NOTE(_C5 )

#define BS_OVERWATCH_THEME \
    HD_NOTE(_A4 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_A4 ), \
    HD_NOTE(_B4 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_B4 ), \
    W__NOTE(_CS5),

#define BS_MARIO_THEME \
    Q__NOTE(_E5), \
    H__NOTE(_E5), \
    H__NOTE(_E5), \
    Q__NOTE(_C5), \
    H__NOTE(_E5), \
    W__NOTE(_G5), \
    Q__NOTE(_G4),

#define BS_MARIO_GAMEOVER \
    HD_NOTE(_C5 ), \
    HD_NOTE(_G4 ), \
    H__NOTE(_E4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_B4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_AF4), \
    H__NOTE(_BF4), \
    H__NOTE(_AF4), \
    WD_NOTE(_G4 ),

#define BS_MARIO_MUSHROOM \
    S__NOTE(_C5 ), \
    S__NOTE(_G4 ), \
    S__NOTE(_C5 ), \
    S__NOTE(_E5 ), \
    S__NOTE(_G5 ), \
    S__NOTE(_C6 ), \
    S__NOTE(_G5 ), \
    S__NOTE(_GS4), \
    S__NOTE(_C5 ), \
    S__NOTE(_DS5), \
    S__NOTE(_GS5), \
    S__NOTE(_DS5), \
    S__NOTE(_GS5), \
    S__NOTE(_C6 ), \
    S__NOTE(_DS6), \
    S__NOTE(_GS6), \
    S__NOTE(_DS6), \
    S__NOTE(_AS4), \
    S__NOTE(_D5 ), \
    S__NOTE(_F5 ), \
    S__NOTE(_AS5), \
    S__NOTE(_D6 ), \
    S__NOTE(_F6 ), \
    S__NOTE(_AS6), \
    S__NOTE(_F6 )

#define BS_E1M1_DOOM  \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_D4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_BF3), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_B3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_D4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    H__NOTE(_BF3),

#define BS_DISNEY_SONG \
    H__NOTE(_G3 ),  \
    H__NOTE(_G4 ),  \
    H__NOTE(_F4 ),  \
    H__NOTE(_E4 ),  \
    H__NOTE(_CS4),  \
    H__NOTE(_D4 ),  \
    W__NOTE(_A4 ),  \
    H__NOTE(_B3 ),  \
    H__NOTE(_B4 ),  \
    H__NOTE(_A4 ),  \
    H__NOTE(_G4 ),  \
    H__NOTE(_FS4),  \
    H__NOTE(_G4 ),  \
    W__NOTE(_C5 ),  \
    H__NOTE(_D5 ),  \
    H__NOTE(_C5 ),  \
    H__NOTE(_B4 ),  \
    H__NOTE(_A4 ),  \
    H__NOTE(_G4 ),  \
    H__NOTE(_F4 ),  \
    H__NOTE(_E4 ),  \
    H__NOTE(_D4 ),  \
    W__NOTE(_A4 ),  \
    W__NOTE(_B3 ),  \
    W__NOTE(_C4 ),

#define BS_NUMBER_ONE \
    HD_NOTE(_F4 ), \
    Q__NOTE(_C5 ), \
    E__NOTE(_B4 ), \
    E__NOTE(_C5 ), \
    E__NOTE(_B4 ), \
    E__NOTE(_C5 ), \
    Q__NOTE(_B4 ), \
    Q__NOTE(_C5 ), \
    H__NOTE(_AF4), \
    HD_NOTE(_F4 ), \
    Q__NOTE(_F4 ), \
    Q__NOTE(_AF4), \
    Q__NOTE(_C5 ), \
    H__NOTE(_DF5), \
    H__NOTE(_AF4), \
    H__NOTE(_DF5), \
    H__NOTE(_EF5), \
    Q__NOTE(_C5 ), \
    Q__NOTE(_DF5), \
    Q__NOTE(_C5 ), \
    Q__NOTE(_DF5), \
    H__NOTE(_C5 ),

#define BS_CABBAGE_SONG \
    H__NOTE(_C4),    \
    H__NOTE(_A4),    \
    H__NOTE(_B4),    \
    H__NOTE(_B4),    \
    H__NOTE(_A4),    \
    H__NOTE(_G4),    \
    H__NOTE(_E4),

#define BS_OLD_SPICE  \
    Q__NOTE(_A4 ), \
    Q__NOTE(_A4 ), \
    H__NOTE(_B4 ), \
    H__NOTE(_D5 ), \
    H__NOTE(_CS5), \
    Q__NOTE(_E5 ), \
    H__NOTE(_FS5), \
    H__NOTE(_D5 ), \

#define BS_VICTORY_FANFARE_SHORT \
    ED_NOTE(_C6), \
    ED_NOTE(_C6), \
    ED_NOTE(_C6), \
    ED_NOTE(_C6), \
    W__NOTE(_REST), \
    QD_NOTE(_GS5), \
    QD_NOTE(_AS5), \
    Q__NOTE(_C6), \
    Q__NOTE(_AS5), \
    Q__NOTE(_C6), \

#define BS_ALL_STAR \
    H__NOTE(_AS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), H__NOTE(_FS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), \
    H__NOTE(_FS4), W__NOTE(_FS4), W__NOTE(_FS4), QD_NOTE(_AS4), \
    H__NOTE(_AS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), H__NOTE(_FS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), \
    H__NOTE(_FS4), W__NOTE(_FS4), W__NOTE(_FS4), W__NOTE(_AS4), H__NOTE(_REST),\
    W__NOTE(_AS4), W__NOTE(_CS5), H__NOTE(_B4),  H__NOTE(_CS5), H__NOTE(_DS5), W__NOTE(_FS5), \
    H__NOTE(_GS5), W__NOTE(_GS5), H__NOTE(_FS4), H__NOTE(_FS4), H__NOTE(_GS4), H__NOTE(_FS4), \
    H__NOTE(_AS4), W__NOTE(_GS4), W__NOTE(_GS4), W__NOTE(_FS4), W__NOTE(_GS4), \
    H__NOTE(_AS4), WD_NOTE(_DS4)

#define BS_RICK_ROLL      \
    Q__NOTE(_F4),      \
    Q__NOTE(_G4),      \
    Q__NOTE(_BF4),     \
    Q__NOTE(_G4),      \
    HD_NOTE(_D5),      \
    HD_NOTE(_D5),      \
    W__NOTE(_C5),      \
    S__NOTE(_REST),    \
    Q__NOTE(_F4),      \
    Q__NOTE(_G4),      \
    Q__NOTE(_BF4),     \
    Q__NOTE(_G4),      \
    HD_NOTE(_C5),      \
    HD_NOTE(_C5),      \
    W__NOTE(_BF4),     \
    S__NOTE(_REST),    \
    Q__NOTE(_F4),      \
    Q__NOTE(_G4),      \
    Q__NOTE(_BF4),     \
    Q__NOTE(_G4),      \
    W__NOTE(_BF4),     \
    H__NOTE(_C5),      \
    H__NOTE(_A4),      \
    H__NOTE(_A4),      \
    H__NOTE(_G4),      \
    H__NOTE(_F4),      \
    H__NOTE(_F4),      \
    W__NOTE(_C5),      \
    W__NOTE(_BF4),

/* Prelude music from Final Fantasy */
#define BS_FF_PRELUDE \
  M__NOTE(_C3, 20), M__NOTE(_D3, 20), M__NOTE(_E3, 20), M__NOTE(_G3, 20), \
  M__NOTE(_C4, 20), M__NOTE(_D4, 20), M__NOTE(_E4, 20), M__NOTE(_G4, 20), \
  M__NOTE(_C5, 20), M__NOTE(_D5, 20), M__NOTE(_E5, 20), M__NOTE(_G5, 20), \
  M__NOTE(_C6, 20), M__NOTE(_D6, 20), M__NOTE(_E6, 20), M__NOTE(_G6, 20), \
  M__NOTE(_C7, 20), M__NOTE(_G6, 20), M__NOTE(_E6, 20), M__NOTE(_D6, 20), \
  M__NOTE(_C6, 20), M__NOTE(_G5, 20), M__NOTE(_E5, 20), M__NOTE(_D5, 20), \
  M__NOTE(_C5, 20), M__NOTE(_G4, 20), M__NOTE(_E4, 20), M__NOTE(_D4, 20), \
  M__NOTE(_C4, 20), M__NOTE(_G3, 20), M__NOTE(_E3, 20), M__NOTE(_D3, 20), \
  M__NOTE(_A2, 20), M__NOTE(_B2, 20), M__NOTE(_C3, 20), M__NOTE(_E3, 20), \
  M__NOTE(_A3, 20), M__NOTE(_B3, 20), M__NOTE(_C4, 20), M__NOTE(_E4, 20), \
  M__NOTE(_A4, 20), M__NOTE(_B4, 20), M__NOTE(_C5, 20), M__NOTE(_E5, 20), \
  M__NOTE(_A5, 20), M__NOTE(_B5, 20), M__NOTE(_C6, 20), M__NOTE(_E6, 20), \
  M__NOTE(_A6, 20), M__NOTE(_E6, 20), M__NOTE(_C6, 20), M__NOTE(_B5, 20), \
  M__NOTE(_A5, 20), M__NOTE(_E5, 20), M__NOTE(_C5, 20), M__NOTE(_B4, 20), \
  M__NOTE(_A4, 20), M__NOTE(_E4, 20), M__NOTE(_C4, 20), M__NOTE(_B3, 20), \
  M__NOTE(_A3, 20), M__NOTE(_E3, 20), M__NOTE(_C3, 20), M__NOTE(_B2, 20),

/* Melody from the main themes of Star Trek TNG and the original series */
#define BS_TO_BOLDLY_GO \
  W__NOTE(_BF3 ), \
  Q__NOTE(_EF4 ), \
  WD_NOTE(_AF4 ), \
  W__NOTE(_REST), \
  H__NOTE(_G4  ), \
  Q__NOTE(_EF4 ), \
  H__NOTE(_C4  ), \
  W__NOTE(_REST), \
  QD_NOTE(_F4  ), \
  M__NOTE(_BF4, 128),

#define BS_KATAWARE_DOKI \
  W__NOTE(_G5), HD_NOTE(_G5), Q__NOTE(_G5), H__NOTE(_G5), H__NOTE(_E5), H__NOTE(_D5), Q__NOTE(_D5), Q__NOTE(_C5), \
  B__NOTE(_E5), H__NOTE(_C5), W__NOTE(_G5), HD_NOTE(_G5), Q__NOTE(_C5), H__NOTE(_C6), Q__NOTE(_B5), \
  Q__NOTE(_A5), H__NOTE(_G5), Q__NOTE(_G5), Q__NOTE(_A5), W__NOTE(_G5), QD_NOTE(_E5), \
  QD_NOTE(_F5), Q__NOTE(_E5), WD_NOTE(_D5), H__NOTE(_C5), W__NOTE(_G5), HD_NOTE(_G5), Q__NOTE(_G5), \
  H__NOTE(_G5), H__NOTE(_E5), H__NOTE(_D5), Q__NOTE(_D5), Q__NOTE(_C5), B__NOTE(_E5), H__NOTE(_G4), \
  Q__NOTE(_C5), Q__NOTE(_D5), Q__NOTE(_E5), H__NOTE(_D5), Q__NOTE(_C5), Q__NOTE(_C5), \
  Q__NOTE(_A4), H__NOTE(_C5), Q__NOTE(_C5), W__NOTE(_C5), Q__NOTE(_F4), Q__NOTE(_C5), \
  Q__NOTE(_D5), Q__NOTE(_E5), H__NOTE(_D5), H__NOTE(_C5), Q__NOTE(_C5), H__NOTE(_G5), \
  Q__NOTE(_C5), HD_NOTE(_D5), H__NOTE(_G4), Q__NOTE(_C5), Q__NOTE(_D5), Q__NOTE(_E5), \
  H__NOTE(_D5), Q__NOTE(_C5), Q__NOTE(_C5), Q__NOTE(_A4), H__NOTE(_C5), Q__NOTE(_C5), \
  W__NOTE(_C5), Q__NOTE(_F4), Q__NOTE(_C5), Q__NOTE(_D5), Q__NOTE(_E5), H__NOTE(_D5), \
  H__NOTE(_C5), Q__NOTE(_C5), H__NOTE(_G5), Q__NOTE(_C5), HD_NOTE(_D5), \
  HD_NOTE(_G4), Q__NOTE(_C5), Q__NOTE(_D5), BD_NOTE(_C5),
