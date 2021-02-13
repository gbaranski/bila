#include "ball.hpp"

#include <algorithm>

void Ball::update( float seconds_passed ) {
  // for debugging
  system("clear");
  printf("x: %f\n", position.x);
  printf("y: %f\n", position.y);
  printf("vx: %f\n", velocity.x);
  printf("vy: %f\n", velocity.y);
  printf("ax: %f\n", acceleration.x);
  printf("ay: %f\n", acceleration.y);
  printf("s: %f\n", seconds_passed);

  velocity.x += acceleration.x * seconds_passed;
  velocity.y += acceleration.y * seconds_passed;

  // add friction on x
  if      ( velocity.x > 0 ) velocity.x = std::max(velocity.x - friction, 0.0f);
  else if ( velocity.x < 0 ) velocity.x = std::min(velocity.x + friction, 0.00f);

  // add friction on y
  if      ( velocity.y > 0 ) velocity.y = std::max(velocity.y - friction, 0.0f);
  else if ( velocity.y < 0 ) velocity.y = std::min(velocity.y + friction, 0.00f);

  // fix x velocity if its above maximum value
  if      ( velocity.x > max_velocity.x ) velocity.x = max_velocity.x;
  else if ( velocity.x < -max_velocity.x ) velocity.x = -max_velocity.x;
  // fix y velocity if its above maximum value
  if      ( velocity.y > max_velocity.y ) velocity.y = max_velocity.y;
  else if ( velocity.y < -max_velocity.y ) velocity.y = -max_velocity.y;


  position.x += velocity.x * seconds_passed;
  position.y += velocity.y * seconds_passed;

}

void Ball::push_up() {
  acceleration.y = -0.1;
}
void Ball::push_down() {
  acceleration.y = 0.1;
}
void Ball::push_left() {
  acceleration.x = -0.1;
}
void Ball::push_right() {
  acceleration.x = 0.1;
}

void Ball::reset_x() {
  acceleration.x = 0;
}

void Ball::reset_y() {
  acceleration.y = 0;
}

void Ball::draw( SDL_Renderer* renderer ) {
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // Setting the color to be RED with 100% opaque (0% trasparent).
  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

  // Drawing circle
  for ( int x = position.x - radius; x <= position.x + radius; x++ )
  {
    for ( int y = position.y - radius; y <= position.y + radius; y++ )
    {
      if ( ( pow( position.y - y, 2 ) + pow( position.x - x, 2 ) ) <= pow( radius, 2 ) )
      {
        SDL_RenderDrawPoint( renderer, x, y );
      }
    }
  }

  // Show the change on the screen
  SDL_RenderPresent( renderer );

}


