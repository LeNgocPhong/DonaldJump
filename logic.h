#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "defs.h"

struct Duck
{
    int x = FIRST_POS[0];
    int y = FIRST_POS[1];
    int Vx = 0;
    int Vy = VELOCITY;

    void Move()
    {
        Vy += GRAVITY;

        if (y>GROUND - DUCKSIZE[1])
        {
            Vy = 0;
        }

        y += Vy;
    }
};

#endif // LOGIC_H_INCLUDED
