#include "game.hpp"

#include <SDL.h>
#include <vector>

#include "types.hpp"

#include "ball.hpp"

const u16 WIDTH = 1000;
const u16 HEIGHT = 1000;
const u16 MAX_FPS = 144;
const f32 TICKS_PER_FRAME = 1000.0f / MAX_FPS;

Game::Game() noexcept {
  balls.push_back( Ball( Size( WIDTH, HEIGHT ), &balls ) );
}

void Game::init()
{
  SDL_Init( SDL_INIT_VIDEO );
  window = SDL_CreateWindow( "openbilliard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_VULKAN);
  if ( window == NULL ) throw SDL_GetError();
  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if ( renderer == NULL ) throw SDL_GetError();

  if ( SDL_RenderClear( renderer ) != 0 ) throw SDL_GetError();
  SDL_RenderPresent( renderer );
}

void Game::run(void)
{
  is_running = true;

  while ( is_running )
  {
    u64 start_perf = SDL_GetPerformanceCounter();

    handle_event();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    // Setting the color to be RED with 100% opaque (0% trasparent).
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

    for ( Ball &b1 : balls ) {
      b1.update( 10 );
      for ( Ball &b2 : balls ) {
        // skip if its the same
        if ( &b2 == &b1  ) continue;

        f32 distance = 
          std::pow(b2.position.x - b1.position.x, 2) +
          std::pow(b2.position.y - b1.position.y, 2);

        if ( distance < std::pow(b1.radius + b2.radius, 2) ) {
          printf("collision occured\n");
        } 

      }

      b1.draw( renderer );
    }

    // Show the change on the screen
    SDL_RenderPresent( renderer );

    u64 end_perf = SDL_GetPerformanceCounter();
    f32 elapsed = ( end_perf - start_perf ) / (float)SDL_GetPerformanceFrequency();
    printf("fps: %f\n", 1.0f / elapsed);
  }

  SDL_DestroyWindow( window );
  SDL_DestroyRenderer( renderer );

  SDL_Quit();
}

void Game::handle_keydown( SDL_KeyboardEvent *event )
{
  if      ( event->keysym.sym == SDLK_a )      balls[0].push_left();
  else if ( event->keysym.sym == SDLK_d )      balls[0].push_right();
  else if ( event->keysym.sym == SDLK_w )      balls[0].push_up();
  else if ( event->keysym.sym == SDLK_s )      balls[0].push_down();
  else if ( event->keysym.sym == SDLK_r )      balls[0].reset_pos(); 
  else if ( event->keysym.sym == SDLK_ESCAPE ) is_running = false;
  else if ( event->keysym.sym == SDLK_SPACE )  balls.push_back( Ball( Size( WIDTH, HEIGHT ), &balls ) );
  // Just for testing
  else if ( event->keysym.sym == SDLK_LEFT )   balls[0].position.x -= 10;
  else if ( event->keysym.sym == SDLK_RIGHT )  balls[0].position.x += 10;
  else if ( event->keysym.sym == SDLK_UP )     balls[0].position.y -= 10;
  else if ( event->keysym.sym == SDLK_DOWN )   balls[0].position.y += 10;
}

void Game::handle_keyup( SDL_KeyboardEvent *event )
{
  if      ( event->keysym.sym == SDLK_a || event->keysym.sym == SDLK_d ) balls[0].reset_acceleration_x();
  else if ( event->keysym.sym == SDLK_w || event->keysym.sym == SDLK_s ) balls[0].reset_acceleration_y();
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
