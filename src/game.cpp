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

#define GRAVITY 10

#define WIDTH 500
#define HEIGHT 500

void Game::init(void)
{
  SDL_Init( SDL_INIT_VIDEO );
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 ); // setting draw color
  SDL_RenderClear( renderer );                    // Clear the newly created window
  SDL_RenderPresent( renderer );                  // Reflects the changes done in the

  world = new World( GRAVITY, WIDTH, HEIGHT );
  player = new Player( world, Point(WIDTH/2.0, HEIGHT-50) );
}

void Game::run(void)
{
  is_running = true;

  while (is_running)
  {
    handle_event();
    player->update(16.0 / 1000);
    player->draw(renderer);
    SDL_Delay(15);
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
}

void Game::handle_keydown(SDL_KeyboardEvent *event)
{
  switch (event->keysym.sym)
  {
  case SDLK_ESCAPE:
    is_running = false;
  case SDLK_w:
    player->jump();
    break;
  case SDLK_a:
    player->moveLeft();
    break;
  case SDLK_d:
    player->moveRight();
    break;
  }
}

void Game::handle_event(void)
{
  SDL_Event event;
  if (!SDL_PollEvent(&event))
    return;
  switch (event.type)
  {
  case SDL_QUIT:
    is_running = false;
  case SDL_KEYDOWN:
    handle_keydown(&event.key);
  }
}

void Game::draw(void)
{
}
