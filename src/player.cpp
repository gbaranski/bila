#include "player.hpp"

#include <algorithm>

#include <SDL_render.h>
#include "entity.hpp"
#include "globals.hpp"

static const int player_radius = 50;

Player::Player(World *_world, Point _position) noexcept
{
  mass = 100;
  position = _position;
  velocity = Point(0, 0);
  world = _world;
}

Player::~Player() noexcept
{
}

void Player::Entity::update(float seconds_passed)
{
  float distance_to_ground = world->height - position.y + (velocity.y * seconds_passed)  - player_radius; 


  if (distance_to_ground == 0) {
    // Check if is on the same level as ground
    velocity.y = 0;
  } else if (distance_to_ground < 0) {
    // Set Y velocity to distance to ground, so if he is below ground he will just pop out
    velocity.y = distance_to_ground;
  } else {
    // Set velocity to make object fall
    velocity.y += world->gravity * seconds_passed;
  }

  position.x += velocity.x * seconds_passed;
  position.y += velocity.y * seconds_passed;
}

void Player::Entity::draw( SDL_Renderer *renderer )
{
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // Setting the color to be RED with 100% opaque (0% trasparent).
  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

  // Drawing circle
  for ( int x = position.x - player_radius; x <= position.x + player_radius; x++ )
  {
    for ( int y = position.y - player_radius; y <= position.y + player_radius; y++ )
    {
      if ( ( pow( position.y - y, 2 ) + pow( position.x - x, 2 ) ) <= pow( player_radius, 2 ) )
      {
        SDL_RenderDrawPoint( renderer, x, y );
      }
    }
  }

  // Show the change on the screen
  SDL_RenderPresent( renderer );
}

void Player::jump() noexcept {
  printf("jump\n");
  position.y -= 1;
  velocity.y = -30;
}

void Player::moveLeft() noexcept {
  printf("move left\n");
  position.x -= 10;
}

void Player::moveRight() noexcept {
  printf("move right\n");
  position.x += 10;
}

