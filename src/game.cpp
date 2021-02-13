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

#define WIDTH 1000
#define HEIGHT 1000

#define FPS 60

void Game::init(void)
{
  SDL_Init( SDL_INIT_VIDEO );
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 ); // setting draw color
  SDL_RenderClear( renderer );                    // Clear the newly created window
  SDL_RenderPresent( renderer );                  // Reflects the changes done in the
}

void Game::run(void)
{
  is_running = true;

  int32_t tick_interval = 1000/FPS;
  uint32_t last_update_time = 0;
  int32_t delta_time = 0;

  while ( is_running )
  {
    uint32_t current_time = SDL_GetTicks(  );
    delta_time = current_time - last_update_time;

    int32_t time_to_sleep = tick_interval - delta_time;
    if ( time_to_sleep > 0 ) {
      SDL_Delay(time_to_sleep);
    }

    handle_event();
    ball.update( delta_time );
    ball.draw( renderer );
    last_update_time = current_time;
  }

  SDL_DestroyWindow( window );
  SDL_DestroyRenderer( renderer );

  SDL_Quit();
}

void Game::handle_keydown( SDL_KeyboardEvent *event )
{
  if      ( event->keysym.sym == SDLK_a )      ball.push_left();
  else if ( event->keysym.sym == SDLK_d )      ball.push_right();
  else if ( event->keysym.sym == SDLK_w )      ball.push_up();
  else if ( event->keysym.sym == SDLK_s )      ball.push_down();
  else if ( event->keysym.sym == SDLK_ESCAPE ) is_running = false;
}

void Game::handle_keyup( SDL_KeyboardEvent *event )
{
  if      ( event->keysym.sym == SDLK_a || event->keysym.sym == SDLK_d ) ball.reset_x();
  else if ( event->keysym.sym == SDLK_w || event->keysym.sym == SDLK_s ) ball.reset_y();
}

void Game::handle_event(  ) {
  SDL_Event event;
  if ( !SDL_PollEvent( &event ) ) return;

  switch ( event.type )
  {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    handle_keydown( &event.key );
    break;
  case SDL_KEYUP:
    handle_keyup( &event.key );
    break;
  }
}

void Game::draw(void)
{
}
