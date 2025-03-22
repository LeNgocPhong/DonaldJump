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
        }

        Donald.Move();
        graphics.prepareScene();
        graphics.DrawDuck(Donald.x, Donald.y,DonaldSprite);
        graphics.presentScene();
        SDL_Delay(60);
        DonaldSprite.tick();
    }

    graphics.quit();
    return 0;
}
