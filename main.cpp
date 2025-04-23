#include <iostream>
#include <string>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include "player.h"
#include "Game.h"
#include "score.h"

using namespace std;

int main(int argc, char* argv[])
{
    Graphic graphics;
    graphics.InitSDL();

    Duck Donald;
    Cactus cactus;

    Sprite DonaldSprite, JumpSprite, DeathSprite, CactusSprite;
    SDL_Texture* DonaldTexture = graphics.loadTexture(DUCK_RUNNING_FILE);
    SDL_Texture* JumpTexture   = graphics.loadTexture(DUCK_JUMPING_FILE);
    SDL_Texture* DeathTexture  = graphics.loadTexture(DUCK_DEATH_FILE);
    SDL_Texture* CactusTexture = graphics.loadTexture(CACTUS_IMG);

    DonaldSprite.init(DonaldTexture, DUCK_FRAMES, DUCK_CLIPS);
    JumpSprite.init(JumpTexture, JUMP_FRAMES, DUCK_JUMP_CLIPS);
    DeathSprite.init(DeathTexture, DEATH_FRAMES, DUCK_DEATH_CLIPS);
    CactusSprite.init(CactusTexture, CACTUS_FRAMES, CACTUS_CLIPS);

    ScrollingBackground background, matDat;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));
    matDat.setTexture(graphics.loadTexture(GROUND_IMG));

    Mix_Music *gMusic = graphics.loadMusic(MUSIC_MP3);
    Mix_Chunk *gJump = graphics.loadSound(JUMP_MP3);
    Mix_Chunk *gDeathsound = graphics.loadSound(DEATHSOUND_MP3);
    graphics.play(gMusic);

    highscore = loadHighScore("highscore.txt");

    bool running = true;
    while (running)
    {
        if(isInMenu){
            running = inMenu(graphics,gMusic);
        }
        else if(isInHelp)
        {
            running = inHelp(graphics);
        }
        else if(isPause)
        {
            running = inPause(graphics, gMusic, Donald, cactus);
        }
        else if (collision(Donald, cactus)) {
            running = handleGameOver(graphics, Donald, cactus, background, matDat, CactusSprite, DeathSprite, gDeathsound);
        }
        else if (Donald.y < GROUND - DUCKSIZE[1]) {
            running = jump(graphics, Donald, cactus, background, matDat, CactusSprite, JumpSprite, gJump);
        }
        else {
            running = run(graphics, Donald, cactus, background, matDat, CactusSprite, DonaldSprite);
        }
    }

    SDL_DestroyTexture(DonaldTexture);
    SDL_DestroyTexture(JumpTexture);
    SDL_DestroyTexture(DeathTexture);
    SDL_DestroyTexture(CactusTexture);
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gJump);
    graphics.quit();
    SDL_Quit();

    return 0;
}


