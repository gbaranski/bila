#include "ball.hpp"
#include "types.hpp"

#include <algorithm>

void Ball::update_friction(  ) 
{
  // add friction on x
  if      ( velocity.x > 0 ) velocity.x = std::max(velocity.x - friction, 0.0f);
  else if ( velocity.x < 0 ) velocity.x = std::min(velocity.x + friction, 0.00f);

  // add friction on y
  if      ( velocity.y > 0 ) velocity.y = std::max(velocity.y - friction, 0.0f);
  else if ( velocity.y < 0 ) velocity.y = std::min(velocity.y + friction, 0.00f);
}

void Ball::update_position( float delta_time ) 
{
  position.x += velocity.x * delta_time;
  position.y += velocity.y * delta_time;
}

void Ball::update_velocity( float delta_time ) 
{
  velocity.x += acceleration.x * delta_time;
  velocity.y += acceleration.y * delta_time;
}

// Fix velocity fixes velocity if it is above maximum values
void Ball::limit_velocity( ) 
{
  // fix x velocity if its above maximum value
  if      ( velocity.x > max_velocity.x ) velocity.x = max_velocity.x;
  else if ( velocity.x < -max_velocity.x ) velocity.x = -max_velocity.x;
  // fix y velocity if its above maximum value
  if      ( velocity.y > max_velocity.y ) velocity.y = max_velocity.y;
  else if ( velocity.y < -max_velocity.y ) velocity.y = -max_velocity.y;
}

// Returns pair of Side, first one on x axis, seocnd on y axis
std::vector<Side> Ball::get_wall_collisions( Point new_pos ) 
{
  std::vector<Side> collisions;

  if      ( new_pos.x + radius > window_size.width ) collisions.push_back(Side::Left);
  else if ( radius - new_pos.x > 0 )                 collisions.push_back(Side::Right);

  // Detect collision on Y axis walls, if collides prevent overflow
  if      ( new_pos.y + radius > window_size.height ) collisions.push_back(Side::Bottom);
  else if ( radius - new_pos.y > 0 )                  collisions.push_back(Side::Top);

  return collisions;
}


void Ball::handle_wall_collisions( float delta_time )
{
  Point new_pos = Point(
      position.x + velocity.x * delta_time, 
      position.y + velocity.y * delta_time
      );

  for ( Side collision : get_wall_collisions( new_pos ) ) {
    printf("Collision: %d\n", collision);
    switch ( collision ) {
      case Side::Bottom: 
        position.y += window_size.height - new_pos.y - radius;
        break;
      case Side::Top: 
        position.y += radius - new_pos.y;
        break;
      case Side::Left: 
        position.x += window_size.width - new_pos.x - radius;
        break;
      case Side::Right: 
        position.x += radius - new_pos.x;
        break;
      case Side::None:
        break;
    }
  }
}


void Ball::update( float delta_time ) {
  system("clear");
  update_velocity( delta_time );
  update_friction();
  limit_velocity();
  handle_wall_collisions( delta_time );
  update_position( delta_time );
  printf("x: %f\n", position.x);
  printf("y: %f\n", position.y);
}

void Ball::draw( SDL_Renderer* renderer ) {
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
}


