#pragma once

#include <vector>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include "ball.hpp"

class Game
{
public:
  Game() noexcept;
  void init(void);
  void run(void);

private:
  void handle_event( void );
  void handle_keydown( SDL_KeyboardEvent *event );
  void handle_keyup( SDL_KeyboardEvent *event );
  void handle_balls_collision( Ball& b1, Ball& b2 );
  void draw();
  SDL_Window *window;
  SDL_Renderer *renderer;

  std::vector<Ball> balls;

  bool is_running;
};
