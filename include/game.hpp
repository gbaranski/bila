#pragma once

#include <vector>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include "ball.hpp"

class Game
{
public:
  void init(void);
  void run(void);

private:
  void handle_event( void );
  void handle_keydown( SDL_KeyboardEvent *event );
  void handle_keyup( SDL_KeyboardEvent *event );
  void draw();
  SDL_Window *window;
  SDL_Renderer *renderer;

  Ball ball;

  bool is_running;
};
