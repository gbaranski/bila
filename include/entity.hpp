#pragma once

#include "SDL_render.h"
#include "globals.hpp"

class Entity
{
public:
  virtual void draw(SDL_Renderer *renderer);
  virtual void update();
  Point pos;
  Point vel;

protected:
  int mass;
};
