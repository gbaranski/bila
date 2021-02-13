#pragma once

#include <SDL_render.h>
#include "globals.hpp"

class Ball {
  private:
    Point velocity;
    Point acceleration;

    const int   radius       = 50;
    const float friction     = 0.1;
    const int   mass         = 10;
    const float push_factor  = 0.1;
    const Point max_velocity = Point(3, 3);
    Size window_size;

  public:
    // TODO: Change position accessor to private!
    Point position;
    void draw(SDL_Renderer *renderer);
    void update(float seconds_passed);
    void push_up() {
      acceleration.y -= push_factor;
    };
    void push_down() {
      acceleration.y += push_factor;
    }
    void push_left() {
      acceleration.x -= push_factor;
    }
    void push_right() {
      acceleration.x += push_factor;
    }
    void reset_acceleration_x() {
      acceleration.x = 0;
    }
    void reset_acceleration_y() {
      acceleration.y = 0;
    }

    void reset_pos() {
      position.x = window_size.width / 2.0f;
      position.y = window_size.height / 2.0f;
    }

    Ball(Size window_size_) {
      window_size  = window_size_;
      velocity     = Point(0,0);
      acceleration = Point(0,0);

      reset_pos();
    };
};
