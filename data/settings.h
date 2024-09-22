#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

const int WINDOW_WIDTH =  640;
const int WINDOW_HEIGHT =  480;
const int TILE_SIZE = 32;
const int SCALE = 1;
const int player_speed =  8;
const float gravity = 0.6;
const int jump_limit = -14;

struct block{
    int x;
    int y;
};

const bool testing_camera = false;


#endif // SETTINGS_H_INCLUDED
