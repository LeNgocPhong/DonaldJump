#include <iostream>
#include <SDL.h>


using namespace std;

int main(int argc, char* argv[])
{
    Graphic graphics;
    graphics.InitSDL();

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
        graphics.prepareScene();
        graphics.presentScene();
    }

    graphics.quit();
    return 0;
}
