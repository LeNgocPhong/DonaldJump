#include <iostream>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"

using namespace std;

bool handleGameOver(Graphic& graphics, Duck& Donald, Cactus& cactus,
                    ScrollingBackground& background, ScrollingBackground& matDat,
                    Sprite& CactusSprite, Sprite& DeathSprite)
{
    bool gameOver = true;
    while (gameOver) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                Donald.x = FIRST_POS[0];
                Donald.y = FIRST_POS[1];
                Donald.Vy = VELOCITY[1];
                cactus.x = SCREEN_WIDTH;
                return true;
            }
        }

        graphics.prepareScene();
        graphics.render(background, 0);
        graphics.render(matDat, GROUND);
        graphics.DrawCactus(cactus.x, cactus.y, CactusSprite);
        graphics.DrawDuck(Donald.x, Donald.y, DeathSprite);
        DeathSprite.tick();
        graphics.presentScene();

        SDL_Delay(100);
    }
    return true;
}

int main(int argc, char* argv[])
{
    // Khởi tạo đồ họa
    Graphic graphics;
    graphics.InitSDL();

    // Nhân vật & chướng ngại vật
    Duck Donald;
    Cactus cactus;

    // Sprite nhân vật
    Sprite DonaldSprite, JumpSprite, DeathSprite, CactusSprite;
    SDL_Texture* DonaldTexture = graphics.loadTexture(DUCK_RUNNING_FILE);
    SDL_Texture* JumpTexture   = graphics.loadTexture(DUCK_JUMPING_FILE);
    SDL_Texture* DeathTexture  = graphics.loadTexture(DUCK_DEATH_FILE);
    SDL_Texture* CactusTexture = graphics.loadTexture(CACTUS_IMG);

    DonaldSprite.init(DonaldTexture, DUCK_FRAMES, DUCK_CLIPS);
    JumpSprite.init(JumpTexture, JUMP_FRAMES, DUCK_JUMP_CLIPS);
    DeathSprite.init(DeathTexture, DEATH_FRAMES, DUCK_DEATH_CLIPS);
    CactusSprite.init(CactusTexture, CACTUS_FRAMES, CACTUS_CLIPS);

    // Background & mặt đất
    ScrollingBackground background, matDat;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));
    matDat.setTexture(graphics.loadTexture(GROUND_IMG));

    bool running = true;

    while (running)
    {
        Uint32 frameStart = SDL_GetTicks();

        // Xử lý sự kiện
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP && Donald.y >= GROUND - DUCKSIZE[1]) {
                Donald.Vy = -VELOCITY[1];
                JumpSprite.currentFrame = 0;
            }
        }

        // Logic di chuyển
        Donald.Move();
        cactus.Move();
        CactusSprite.currentFrame = cactus.w;

        // Vẽ khung cảnh
        graphics.prepareScene();
        background.scroll(1);
        graphics.render(background, 0);
        matDat.scroll(VELOCITY[0]);
        graphics.render(matDat, GROUND);
        graphics.DrawCactus(cactus.x, cactus.y, CactusSprite);

        // Kiểm tra va chạm
        bool collision =
            (Donald.x + REALSIZE[0] >= cactus.x && Donald.x <= cactus.x + cactus.w &&
             Donald.y + REALSIZE[1] >= cactus.y);

        if (collision) {
            running = handleGameOver(graphics, Donald, cactus, background, matDat, CactusSprite, DeathSprite);
            continue;
        }

        // Vẽ nhân vật
        if (Donald.y < GROUND - DUCKSIZE[1]) {
            graphics.DrawDuck(Donald.x, Donald.y, JumpSprite);
            if (Donald.Vy == -VELOCITY[1] / 1.5 || Donald.Vy == VELOCITY[1] / 2 || Donald.Vy == 0) {
                JumpSprite.tick();
            }
        } else {
            graphics.DrawDuck(Donald.x, Donald.y, DonaldSprite);
            DonaldSprite.tick();
        }

        graphics.presentScene();

        // Giới hạn tốc độ khung hình
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    // Giải phóng bộ nhớ
    SDL_DestroyTexture(DonaldTexture);
    SDL_DestroyTexture(JumpTexture);
    SDL_DestroyTexture(DeathTexture);
    SDL_DestroyTexture(CactusTexture);
    graphics.quit();
    SDL_Quit();

    return 0;
}
