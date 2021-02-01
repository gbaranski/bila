#include "player.hpp"
#include "SDL_render.h"

Player::Player(int x, int y) noexcept {
  pos.x = x;
  pos.y = y;
}

Player::~Player() noexcept {
}

void Player::Entity::draw(SDL_Renderer *renderer ) {
  const int radius = 50;

  // Setting the color to be RED with 100% opaque (0% trasparent).
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Drawing circle
  for(int x=pos.x-radius; x<=pos.x+radius; x++){
    for(int y=pos.y-radius; y<=pos.y+radius; y++){
      if((pow(pos.y-y,2)+pow(pos.x-x,2)) <= 
          pow(radius,2)){
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }

  // Show the change on the screen
  SDL_RenderPresent(renderer);
}
