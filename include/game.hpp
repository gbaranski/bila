#pragma once

#include <vector>
#include "player.hpp"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_video.h"

class Game
{
public:
  void init(void);
  void run(void);

private:
  void handle_event(void);
  void handle_keydown(SDL_KeyboardEvent *event);
  void draw();
  SDL_Window *window;
  SDL_Renderer *renderer;

  Player *player;
  bool is_running;
};
