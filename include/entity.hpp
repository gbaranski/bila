#pragma once

#include "SDL_render.h"
#include "globals.hpp"
#include "world.hpp"

class Entity
{
public:
  virtual void draw(SDL_Renderer *renderer);
  virtual void update(float second_passed);

protected:
  World *world;

  int mass;
  Point position;
  Point velocity;
};
