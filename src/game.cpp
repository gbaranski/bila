#include "game.hpp"

#include "entity.hpp"
#include "player.hpp"
#include <vector>
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_video.h"

#define WIDTH 500
#define HEIGHT 500


void Game::init(void) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window_, &renderer_);
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);      // setting draw color
  SDL_RenderClear(renderer_);      // Clear the newly created window
  SDL_RenderPresent(renderer_);    // Reflects the changes done in the
  Player player; 
  entities_.push_back(player);
}

void Game::run(void) {
  is_running_ = true;

  while (is_running_) {
    handle_event();
    for (Entity entity : entities_) {
      entity.draw(renderer_);
    }
    SDL_Delay(16);
  }

  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);

  SDL_Quit();
}

void Game::handle_keydown(SDL_KeyboardEvent *event) {
  switch (event->keysym.sym) {
    case SDLK_ESCAPE:
      is_running_ = false;
  }
}

void Game::handle_event(void) {
  SDL_Event event;
  if (!SDL_PollEvent(&event)) return;
  switch (event.type) {
    case SDL_QUIT:
      is_running_ = false;
    case SDL_KEYDOWN:
      handle_keydown(&event.key);
  }
}

void Game::draw(void) {

}
