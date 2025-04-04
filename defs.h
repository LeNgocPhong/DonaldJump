#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "DONALD JUMP";
 const int FRAME_DELAY = 1000 / 24;


const int FIRST_POS[2] = {SCREEN_WIDTH/5, SCREEN_HEIGHT/2};
const int DUCKSIZE[2] = {112,98};
const int REALSIZE[2]={60,90};
const int GRAVITY = 1;
const int VELOCITY[2] = {10,18};
const int GROUND = SCREEN_HEIGHT - 100;

const int CACTUS_HEIGHT = 90;
const int CACTUS_WIDTH[3] = {50, 100, 150};

const char* DUCK_RUNNING_FILE = "img\\run.png";
const char* DUCK_JUMPING_FILE = "img\\jump.png";
const char* DUCK_DEATH_FILE = "img\\death.png";
const char* BACKGROUND_IMG = "img\\desert.png";
const char* GROUND_IMG = "img\\ground.png";
const char* CACTUS_IMG = "img\\cactus.png";

const int CACTUS_CLIPS[][4] = {
    {0,0,50,100},
    {50,0,100,100},
    {150,0,150,100},
};

const int CACTUS_FRAMES = sizeof(CACTUS_CLIPS)/sizeof(int)/4;

const int DUCK_DEATH_CLIPS[][4] = {
    {0,0,56,50},
    {54,0,56,50}
};

const int DEATH_FRAMES = sizeof(DUCK_DEATH_CLIPS)/sizeof(int)/4;

const int DUCK_JUMP_CLIPS[][4] = {
    {10,3,56,49},
    {74,3,56,49},
    {135,3,56,49},
    {201,3,56,49},
};

const int JUMP_FRAMES = sizeof(DUCK_JUMP_CLIPS)/sizeof(int)/4;

const int DUCK_CLIPS[][4] = {
    {2,3,56,49},
    {64,3,56,49},
    {117,3,56,49},
    {175,3,56,49},
    {238,3,56,49},
    {297,3,56,49},
    {353,3,56,49},
    {407,3,56,49},
};

const int DUCK_FRAMES = sizeof(DUCK_CLIPS)/sizeof(int)/4;


#endif // DEFS_H_INCLUDED
