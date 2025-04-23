#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "score.h"

void DrawText(string text, int x, int y, int fontSize, SDL_Color &color, Graphic &graphics)
{
    TTF_Font* font = graphics.loadFont("assets\\Purisa-BoldOblique.ttf", fontSize);
    SDL_Texture* Text = graphics.renderText(text, font, color);
    graphics.renderTexture(Text, x, y);
    SDL_DestroyTexture(Text);
    TTF_CloseFont(font);
}

void resetGame(Duck& Donald, Cactus &cactus)
{
    Donald.x = FIRST_POS[0];
    Donald.y = FIRST_POS[1];
    Donald.Vy = VELOCITY[1];
    cactus.x = SCREEN_WIDTH;
    cactus.w = 0;
    score = 0;
    level = 0;
}

bool collision(const Duck& Donald, const Cactus& cactus)
{
    return (Donald.x + REALSIZE[0] >= cactus.x &&
            Donald.x <= cactus.x + CACTUS_WIDTH[cactus.w] &&
            Donald.y + REALSIZE[1] >= cactus.y);
}

void backgroundScroll(Graphic& graphics, Cactus& cactus, ScrollingBackground& background, ScrollingBackground& matDat, Sprite& CactusSprite)
{
    score++;
    if(score%100==0){
        level++;
    }
    background.scroll(1);
    matDat.scroll(VELOCITY[0]+level);
    CactusSprite.currentFrame = cactus.w;
    cactus.Move();
    graphics.render(background, 0);
    graphics.render(matDat, GROUND);
    graphics.DrawCactus(cactus.x, cactus.y, CactusSprite);
    DrawText("Score:"+to_string(score), 0, 0, 30, WHITE , graphics);
    DrawText("||", SCREEN_WIDTH-40, 0, 30,WHITE,graphics);
}


bool inMenu(Graphic& graphics,Mix_Music *gMusic)
{
    SDL_Texture* background = graphics.loadTexture(MENU_BACKGROUND);
    while (true){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                    return false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX>100 && mouseX<225 && mouseY>225 && mouseY<300)
                {
                    isInMenu = false;
                    return true;
                }
                else if (mouseX>100 && mouseX<225 && mouseY>150 && mouseY<200)
                {
                    isInMenu = false;
                    isInHelp = true;
                    return true;
                }
                else if (mouseX>100 && mouseX<300 && mouseY>375 && mouseY<425)
                {
                    if (isPlaySound)
                    {
                        isPlaySound = false;
                        Mix_HaltMusic();
                    }
                    else
                    {
                        isPlaySound = true;
                        graphics.play(gMusic);
                    }
                }
            }
        }
        graphics.prepareScene();
        graphics.renderTexture(background,0,0);
        DrawText("Donald Jump", 100, 25, 75, WHITE, graphics);
        DrawText("Help", 100, 150, 50, WHITE, graphics);
        DrawText("Play",100,225,50,WHITE,graphics);
        DrawText("HighScore:" + to_string(highscore) ,100,300,50,WHITE,graphics);
        if (isPlaySound)
        {
            DrawText("Sound: ON",100,375,50,WHITE,graphics);
        }
        else
        {
            DrawText("Sound: OFF",100,375,50,WHITE,graphics);
        }

        graphics.presentScene();

    }
    SDL_DestroyTexture(background);

}

bool inHelp(Graphic &graphics)
{
    while (true){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                    return false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX>0 && mouseX<125 && mouseY>0 && mouseY<60)
                {
                    isInMenu = true;
                    isInHelp = false;
                    return true;
                }
            }
        }
        graphics.prepareScene();
        DrawText("Just press key up or 'w' to jump and survival.", 100, 300, 20, WHITE, graphics);
        DrawText("Good luck!", 600, 350, 20, WHITE, graphics);
        DrawText("Back",0,0,50,WHITE,graphics);
        graphics.presentScene();
    }
}

bool inPause(Graphic &graphics,Mix_Music *gMusic,Duck &Donald,Cactus &cactus)
{
    while (true){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) return false;
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX>250 && mouseX<450 && mouseY>100 && mouseY<175){
                    if (isPlaySound)
                    {
                        isPlaySound = false;
                        Mix_HaltMusic();
                    }
                    else
                    {
                        isPlaySound = true;
                        graphics.play(gMusic);
                    }
                }
                else if (mouseX>250 && mouseX<475 && mouseY>200 && mouseY<275)
                {
                    isPause = false;
                    resetGame(Donald,cactus);
                    return true;
                }
                else if (mouseX>250 && mouseX<515 && mouseY>300 && mouseY<375)
                {
                    isPause = false;
                    resetGame(Donald,cactus);
                    isInMenu = true;
                    return true;
                }
                else if (mouseX>125 && mouseX<675 && mouseY>400 && mouseY<500)
                {
                    isPause = false;
                    return true;
                }
            }
        }
        graphics.prepareScene();

        if (isPlaySound)
        {
            DrawText("Sound: ON",250,100,50,WHITE,graphics);
        }
        else
        {
            DrawText("Sound: OFF",250,100,50,WHITE,graphics);
        }
        DrawText("ReStart",250,200,50,WHITE,graphics);
        DrawText("BackMenu",250,300,50,WHITE,graphics);
        DrawText("BackToGame",125,400,75,WHITE,graphics);
        graphics.presentScene();
    }
}

bool handleGameOver(Graphic& graphics, Duck& Donald, Cactus& cactus, ScrollingBackground& background, ScrollingBackground& matDat, Sprite& CactusSprite, Sprite& DeathSprite, Mix_Chunk *gDeathsound)
{
    if (score > highscore) {
    highscore = score;
    saveHighScore("highscore.txt", highscore);
    }
    if(isPlaySound){
        graphics.play(gDeathsound);
    }
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return false;
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX>440 && mouseX<660 && mouseY>185 && mouseY<225)
                {
                    resetGame(Donald,cactus);
                    isInMenu = true;
                    return true;
                }
                else if (mouseX>200 && mouseX<340 && mouseY>185 && mouseY<225)
                {
                    resetGame(Donald,cactus);
                    return true;
                }
            }
        }

        graphics.prepareScene();
        graphics.render(background, 0);
        graphics.render(matDat, GROUND);
        graphics.DrawCactus(cactus.x, cactus.y, CactusSprite);
        graphics.DrawDuck(Donald.x, Donald.y, DeathSprite);
        DrawText("GAME OVER", 215, 0, 60, WHITE, graphics);
        DrawText("Score:"+to_string(score), 250, 75, 40, WHITE , graphics);
        DrawText("HighScore:"+to_string(highscore),250,125,40,WHITE,graphics);
        DrawText("Replay   BackMenu",200,185,40,WHITE,graphics);
        DeathSprite.tick();
        graphics.presentScene();
        SDL_Delay(100);
    }
}

bool jump(Graphic& graphics, Duck& Donald, Cactus& cactus, ScrollingBackground& background, ScrollingBackground& matDat, Sprite& CactusSprite, Sprite& JumpSprite, Mix_Chunk *gJump)
{
    JumpSprite.currentFrame = 0;
    if (isPlaySound){
        graphics.play(gJump);
    }
    while (Donald.y < GROUND - DUCKSIZE[1]) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return false;
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX>SCREEN_WIDTH-40 && mouseX<SCREEN_WIDTH && mouseY>0 && mouseY<30){
                    isPause = true;
                    return true;
                }
            }
        }
        if (collision(Donald, cactus)) return true;

        Donald.Move();
        graphics.prepareScene();
        backgroundScroll(graphics, cactus, background, matDat, CactusSprite);
        graphics.DrawDuck(Donald.x, Donald.y, JumpSprite);
        if (abs(Donald.Vy + VELOCITY[1] / 1.5) < 0.001 || Donald.Vy == VELOCITY[1] / 2 || Donald.Vy == 0)
            JumpSprite.tick();
        graphics.presentScene();
        SDL_Delay(50);
    }
    return true;
}

bool run(Graphic& graphics, Duck& Donald, Cactus& cactus, ScrollingBackground& background, ScrollingBackground& matDat, Sprite& CactusSprite, Sprite& DonaldSprite)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return false;
        else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) && Donald.y >= GROUND - DUCKSIZE[1]) {
            Donald.Vy = -VELOCITY[1];
            Donald.Move();
            return true;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX>SCREEN_WIDTH-40 && mouseX<SCREEN_WIDTH && mouseY>0 && mouseY<30){
                    isPause = true;
                    return true;
                }
            }
    }

    if (collision(Donald, cactus)) return true;

    Donald.Move();
    graphics.prepareScene();
    backgroundScroll(graphics, cactus, background, matDat, CactusSprite);
    graphics.DrawDuck(Donald.x, Donald.y, DonaldSprite);
    DonaldSprite.tick();
    graphics.presentScene();
    SDL_Delay(50);

    return true;
}

#endif // GAME_H_INCLUDED
