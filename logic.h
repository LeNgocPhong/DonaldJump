#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "defs.h"
#include "player.h"

struct Duck
{
    int x = FIRST_POS[0];
    int y = FIRST_POS[1];
    int Vy = VELOCITY[1];

    void Move()
    {
        Vy += GRAVITY;

        if (y>=GROUND-DUCKSIZE[1] && Vy>=0)
        {
            Vy = 0;
        }

        y += Vy;
    }
};

struct Cactus
{
    int x = SCREEN_WIDTH;
    int y = GROUND - CACTUS_HEIGHT;
    int w = 0;

    void Move()
    {
        x-=(VELOCITY[0]+level);
        if (x<-(CACTUS_WIDTH[w]+level*10))
        {
            x = SCREEN_WIDTH;
            w = rand()%3;
        }
    }
};

#endif // LOGIC_H_INCLUDED
