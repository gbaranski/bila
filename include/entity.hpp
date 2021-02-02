#include "SDL_render.h"

#pragma once

struct Position {
  int x;
  int y;
};

class Entity {
  public:
    virtual void draw(SDL_Renderer *renderer);
    virtual void update();
    Position pos;
};
