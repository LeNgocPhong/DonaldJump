#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "DONALD JUMP";


const int FIRST_POS[2] = {SCREEN_WIDTH/5, SCREEN_HEIGHT/2};
const int DUCKSIZE[2] = {112,74};
const int GRAVITY = 2;
const int VELOCITY = 20;
const int GROUND = SCREEN_HEIGHT - 100;

const char* DUCK_RUNNING_FILE = "img\\run.png";

const int DUCK_CLIPS[][4] = {
    {2,3,56,37},
    {64,3,56,37},
    {117,3,56,37},
    {175,3,56,37},
    {238,3,56,37},
    {297,3,56,37},
    {353,3,56,37},
    {407,3,56,37},
};

const int DUCK_FRAMES = sizeof(DUCK_CLIPS)/sizeof(int)/4;


#endif // DEFS_H_INCLUDED
