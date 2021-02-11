#pragma once

#include <SDL_render.h>
#include "globals.hpp"

class Ball {
  private:
    Point position_;
    Point velocity_;
    const int radius_ = 50;

  public:
    void draw(SDL_Renderer *renderer);
    void update(float seconds_passed);
    void push_up();
    void push_down();
    void push_left();
    void push_right();

    Ball() {
      position_ = Point(radius_, radius_);
      velocity_ = Point(0,0);
    };
};
