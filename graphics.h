#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "defs.h"
#include "logic.h"

using namespace std;

struct Graphic
{
  SDL_Window *window;
  SDL_Renderer *renderer;

  void InitSDL()
  {
      if(SDL_Init(SDL_INIT_VIDEO)!=0)
      {
          cout << "InitSDL" << SDL_GetError();
      }
      window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
      if(window = nullptr)
      {
          cout << "CreateWindow " << SDL_GetError();
      }
      renderer SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if(renderer = nullptr)
      {
          cout << "CreateRenderer " << SDL_GetError();
      }
  }
  void prepareScene()
  {
      SDL_SetRenderDrawColor(renderer,0,0,255);
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
          cout << "Load texture " << IMG_GetError();
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
  void quit()
  {
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      SDL_Quit();
  }
};

#endif // GRAPHICS_H_INCLUDED
