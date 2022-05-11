#ifndef CONF_H
#define CONF_H

// 11 x 8
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 880
#define TILE_SIZE 16
#define MONSTER_TILE_SIZE 64
#define ZOOM_FACTOR 5
#define FRAMES_PER_SECOND 60
#define VSYNC_CHOICE true 
#define EMPTY -1
#define WINDOW_NAME "rpg filler"
#define FONT_PATH "art/PressStart2P.ttf"
#define VERSION "version 0.1"

#define LAYERS 3
#define BG 0 
#define FG 1
#define COLLISION 2
#define COLLISION_WALKABLE -1
#define COLLISION_WALL 0

#define CHEST_OPEN_TEXTURE 47
#define TALL_GRASS_TEXTURE 43

#define TILEDAT_SEPERATOR '|'
#define TILEDAT_POS_SEPERATOR ","
#define TILEDAT_DOOR_PREFIX "--door"
#define TILEDAT_ITEM_PREFIX "--item"
#define TILEDAT_NPC_PREFIX "--npc"

#define RETURN_CODE_NOTHING -1 
#define RETURN_CODE_EXIT    0
#define RETURN_CODE_START   1
#define RETURN_CODE_BATTLESCENE 2 

#define MAX_PARTY_SIZE 6
#define MAX_ATTACK_LENGTH 26

enum directions {
    right = 0,
    left = 1,
    up = 2,
    down = 3,
};

enum maps {
    overworld = 0,
    subworld = 1,
    battlescene = 2, 
};

extern unsigned int global_tick;

#endif
