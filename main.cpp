#include <iostream>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"


using namespace std;

int main(int argc, char* argv[])
{
    Graphic graphics;
    graphics.InitSDL();

    Duck Donald;

    Sprite DonaldSprite;
    SDL_Texture* DonaldTexture;
    DonaldTexture = graphics.loadTexture(DUCK_RUNNING_FILE);
    DonaldSprite.init(DonaldTexture,DUCK_FRAMES,DUCK_CLIPS);

    Sprite JumpSprite;
    SDL_Texture* JumpTexture;
    JumpTexture = graphics.loadTexture(DUCK_JUMPING_FILE);
    JumpSprite.init(JumpTexture,JUMP_FRAMES,DUCK_JUMP_CLIPS);

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    ScrollingBackground matDat;
    matDat.setTexture(graphics.loadTexture(GROUND_IMG));

    bool running = true;

    while (running)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP && Donald.y>=GROUND-DUCKSIZE[1])
            {
                Donald.Vy = -VELOCITY;
                JumpSprite.currentFrame = 0;
            }
        }

        Donald.Move();
        graphics.prepareScene();

        background.scroll(1);
        graphics.render(background,0);

        matDat.scroll(10);
        graphics.render(matDat,GROUND);

        if(Donald.y<GROUND-DUCKSIZE[1])
        {
            graphics.DrawDuck(Donald.x, Donald.y,JumpSprite);

            if(Donald.Vy==-VELOCITY/1.5 || Donald.Vy==VELOCITY/2 || Donald.Vy==0)
            {
                JumpSprite.tick();
            }

        }
        else
        {
            graphics.DrawDuck(Donald.x, Donald.y,DonaldSprite);
            DonaldSprite.tick();
        }

        graphics.presentScene();
        SDL_Delay(60);

    }

    graphics.quit();
    return 0;
}
