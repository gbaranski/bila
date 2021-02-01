#include <vector>
#include "entity.hpp"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_video.h"

#pragma once

class Game {
  public:
    void init(void);
    void run(void);
  private:
    void handle_event(void);
    void handle_keydown(SDL_KeyboardEvent *event);
    void draw();
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    std::vector<Entity> entities_;
    bool is_running_;
};
