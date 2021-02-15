#pragma once

#include <SDL_render.h>
#include <vector>
#include "globals.hpp"
#include "types.hpp"

class Ball {
  public:
    const u32   radius       = 50;
    const f32   friction     = 0.1;
    const u32   mass         = 10;
    const f32   push_factor  = 0.1;
    const Point max_velocity = Point(3, 3);

    Point position;

    void draw(SDL_Renderer *renderer);
    void update(f32 seconds_passed);
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

    Ball(Size window_size_, std::vector<Ball> *balls_) {
      balls = balls_;
      window_size  = window_size_;
      velocity     = Point(0,0);
      acceleration = Point(0,0);

      reset_pos();
    };

  private:
    void update_friction();
    void update_position( f32 delta_time );
    void update_velocity( f32 delta_time );
    std::vector<Side> get_wall_collisions( Point new_pos );
    void handle_wall_collisions( f32 delta_time );
    void limit_velocity( );
    std::pair<Side, Side> get_wall_collision( Point new_pos );

    Point velocity;
    Point acceleration;
    bool colliding;
    Size window_size;
    std::vector<Ball> *balls;

};
