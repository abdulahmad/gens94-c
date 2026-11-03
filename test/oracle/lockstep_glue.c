/* What ninety-four's host (native/) needs that gens94-c cut from the game, for the lockstep build
 * only (test/oracle/build.sh). Compiled with ninety-four's headers. Under lockstep the host plays
 * the cartridge's teams and art only, which is all gens94-c plays. */
#include <stdio.h>
#include "rosters.h"
#include "rom.h"
#include "game.h"
#include "symbols_gen.h"
#include "view.h"

const uint8_t *rom_art;                                    /* (no roster set's art: the cartridge's) */
uint32_t rom_limit = ROM_SIZE;

/* the cartridge's roster set, as ninety-four's src/rosters.c has it */
#define RETAIL { { SYM_TeamList, SYM_TeamPalettes, SYM_TeamLogoBitmaps, SYM_TeamGfxList, SYM_TeamSongs, SYM_TeamRatings, \
                   SYM_TeamLogoPalettes, SYM_FeaturedPictures, SYM_playoffseats, SYM_PlayerRecordOffsets, SYM_Teamblocksmap, 0, 0 }, \
                 SYM_NumTeams, SYM_NumPlayoffTeams, SYM_PlayoffRows, \
                 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, \
                   28, 29, 30, 31 }, \
                 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, \
                   28, 29, 30, 31 }, { 0 }, { 0 }, \
                 { SYM_GameSetUpMap, SYM_GameSetUpMap2, SYM_TitleScreenImg, SYM_NHLShieldImg, \
                   SYM_PAlogoImg, SYM_TitleImg, SYM_ScoutMap, SYM_FramerMap, SYM_FaceOffMap, \
                   SYM_Rinktilelist, SYM_Rinktiles, SYM_RefsMap, SYM_RefMap2, SYM_Sprites, \
                   SYM_Spritetiles, SYM_CrowdFrameList, SYM_FaceOffSprites, SYM_ZamFrameList, \
                   SYM_BigFontMap, SYM_SmallFontMap, SYM_EnergyBarMap, SYM_EASNmap, SYM_Arrowsmap, \
                   SYM_RonBarrMap, SYM_ScoresMap, SYM_EASportsMap, SYM_RevRinkTilelist, \
                   SYM_RevRinkTiles, SYM_ReplayMap, SYM_HorRinkMap, SYM_HorRinkTiles, \
                   SYM_PrintFont2Map, SYM_SetupMenuMap, SYM_SetupFramerMap, SYM_LogoBoxMap, \
                   SYM_PicturePalette, SYM_NoPicSkater1, SYM_NoPicSkater2, SYM_NoPicGoalie1, \
                   SYM_NoPicGoalie2, SYM_PlayerCardsScreenPic, SYM_CornerLogoMap, SYM_ArenaGfxBank, \
                   SYM_PlayoffSprite, SYM_HiScoreImg, SYM_HotIconMap, SYM_ColdIconMap, \
                   SYM_TeamBitmaps }, \
                 { { 14, 3 }, { 16, 16 } } }              /* (title94.asm's HiScoreScreen places) */

struct rosters rosters = RETAIL;                           /* (the cartridge's from the start) */
const struct rosters rosters_cartridge = RETAIL;

void rosters_retail(void) { rosters = rosters_cartridge; rosters_read(); }

/* the wide view is off under lockstep: nothing to put back */
void view_rink_resume(void) {}

/* restart_at drops the C frames above run68k; ninety-four's tells the lockstep player so (its
 * run68k_unwind), gens94-c's does not, so every call to it goes through here (-Wl,--wrap) */
void __real_restart_at(void (*entry)(void));
void __wrap_restart_at(void (*entry)(void));
void __wrap_restart_at(void (*entry)(void)) { run68k_unwind(); __real_restart_at(entry); }
