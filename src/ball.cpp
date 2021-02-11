#include "ball.hpp"

void Ball::update( float seconds_passed ) {
  position_.y += velocity_.y * seconds_passed;
  position_.x += velocity_.x * seconds_passed;

}

void Ball::push_up() {
  velocity_.y = -1;
}
void Ball::push_down() {
  velocity_.y = 1;
}
void Ball::push_left() {
  velocity_.x = -1;
}
void Ball::push_right() {
  velocity_.x = 1;
}

void Ball::draw( SDL_Renderer* renderer ) {
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // Setting the color to be RED with 100% opaque (0% trasparent).
  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

  // Drawing circle
  for ( int x = position_.x - radius_; x <= position_.x + radius_; x++ )
  {
    for ( int y = position_.y - radius_; y <= position_.y + radius_; y++ )
    {
      if ( ( pow( position_.y - y, 2 ) + pow( position_.x - x, 2 ) ) <= pow( radius_, 2 ) )
      {
        SDL_RenderDrawPoint( renderer, x, y );
      }
    }
  }

  // Show the change on the screen
  SDL_RenderPresent( renderer );

}


