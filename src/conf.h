#ifndef CONF_H
#define CONF_H

// 11 x 8
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 880
#define TILE_SIZE 16
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

#define RETURN_CODE_NOTHING -1 
#define RETURN_CODE_EXIT    0
#define RETURN_CODE_START   1

enum directions {
    left = 0,
    right = 1,
    up = 2,
    down = 3,
};

extern unsigned int global_tick;

#endif
