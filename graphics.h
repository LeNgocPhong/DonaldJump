#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <sdl_ttf.h>
#include "defs.h"
#include "logic.h"

using namespace std;

struct ScrollingBackground
{
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture)
    {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance)
    {
        scrollingOffset -= distance;
        if(scrollingOffset < 0)
        {
            scrollingOffset = width;
        }
    }
};


struct Sprite
{
    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips[][4])
    {
        texture = _texture;
        SDL_Rect clip;
        for (int i=0; i<frames; i++)
        {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }

    void tick()
    {
        currentFrame = (currentFrame + 1) % clips.size();
    }

    const SDL_Rect* getCurrentClip() const
    {
        return &(clips[currentFrame]);
    }
};

struct Graphic
{
  SDL_Window *window;
  SDL_Renderer *renderer;

  void InitSDL()
  {
      if(SDL_Init(SDL_INIT_VIDEO)!=0)
      {
          cerr << "InitSDL" << SDL_GetError();
      }
      window = SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
      if(window == nullptr)
      {
          cerr << "CreateWindow " << SDL_GetError();
      }
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if(renderer == nullptr)
      {
          cerr << "CreateRenderer " << SDL_GetError();
      }
      if(TTF_Init() == -1)
      {
          cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
      }
      if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
      {
          cerr << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError();
      }


  }

  void prepareScene()
  {
      SDL_SetRenderDrawColor(renderer,0,0,0,255);
      SDL_RenderClear(renderer);
  }

  void presentScene()
  {
      SDL_RenderPresent(renderer);
  }

  SDL_Texture *loadTexture(const char *filename)
  {
      SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
      if(texture == NULL)
      {
          cerr << "Load texture " << IMG_GetError();
      }
      return texture;
  }

  void renderTexture(SDL_Texture *texture, int x, int y)
  {
      SDL_Rect dest;
      dest.x = x;
      dest.y = y;
      SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

      SDL_RenderCopy(renderer, texture, NULL, &dest);
  }

  void DrawDuck(int x, int y, const Sprite& sprite)
  {
      const SDL_Rect* clip = sprite.getCurrentClip();
      SDL_Rect renderQuad = {x, y, DUCKSIZE[0], DUCKSIZE[1]};
      SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
  }

  void DrawCactus(int x, int y, const Sprite& sprite)
  {
      const SDL_Rect* clip = sprite.getCurrentClip();
      SDL_Rect renderQuad = {x, y, clip->w, clip->h};
      SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
  }

  void render(const ScrollingBackground& bgr, const int y)
  {
      renderTexture(bgr.texture,bgr.scrollingOffset,y);
      renderTexture(bgr.texture,bgr.scrollingOffset-bgr.width,y);
  }

  TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            cerr << "Load font %s" << TTF_GetError();
        }
    }

  SDL_Texture* renderText(const string text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
        if( textSurface == nullptr ) {
            cerr << "Render text surface %s" << TTF_GetError();
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            cerr << "Create texture from text %s" << SDL_GetError();
        }

        SDL_FreeSurface( textSurface );
        return texture;
    }

   Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            cerr << "Could not load music! SDL_mixer Error: %s" << Mix_GetError();
        }
        return gMusic;
    }

   void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }

   Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            cerr << "Could not load sound! SDL_mixer Error: %s" << Mix_GetError();
        }
    }
   void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }


  void quit()
  {
      TTF_Quit();
      IMG_Quit();
      Mix_Quit();
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      SDL_Quit();
  }
};

#endif // GRAPHICS_H_INCLUDED
