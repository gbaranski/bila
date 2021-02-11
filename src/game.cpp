#include "game.hpp"

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <vector>

#include "ball.hpp"

#define WIDTH 500
#define HEIGHT 500

#define FPS 60

void Game::init(void)
{
  SDL_Init( SDL_INIT_VIDEO );
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window_, &renderer_ );
  SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 0 ); // setting draw color
  SDL_RenderClear( renderer_ );                    // Clear the newly created window
  SDL_RenderPresent( renderer_ );                  // Reflects the changes done in the
}

void Game::run(void)
{
  is_running_ = true;

  int32_t tick_interval = 1000/FPS;
  uint32_t last_update_time = 0;
  int32_t delta_time = 0;

  while ( is_running_ )
  {
    uint32_t current_time = SDL_GetTicks(  );
    delta_time = current_time - last_update_time;

    int32_t time_to_sleep = tick_interval - delta_time;
    if ( time_to_sleep > 0 ) {
      SDL_Delay(time_to_sleep);
    }

    handle_event();
    ball_.update( delta_time );
    ball_.draw( renderer_ );
    last_update_time = current_time;
  }

  SDL_DestroyWindow( window_ );
  SDL_DestroyRenderer( renderer_ );

  SDL_Quit();
}

void Game::handle_keydown( SDL_KeyboardEvent *event )
{
  switch ( event->keysym.sym )
  {
  case SDLK_ESCAPE:
    is_running_ = false;
    break;
  case SDLK_w:
    ball_.push_up();
    break;
  case SDLK_s:
    ball_.push_down();
    break;
  case SDLK_a:
    ball_.push_left();
    break;
  case SDLK_d:
    ball_.push_right();
    break;

  }
}

void Game::handle_event(  ) {
  SDL_Event event;
  if ( !SDL_PollEvent( &event ) )
    return;
  switch ( event.type )
  {
  case SDL_QUIT:
    is_running_ = false;
    break;
  case SDL_KEYDOWN:
    handle_keydown( &event.key );
    break;
  }
}

void Game::draw(void)
{
}
