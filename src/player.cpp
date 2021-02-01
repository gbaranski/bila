#include "player.hpp"
#include "SDL_render.h"

void Player::Entity::draw(SDL_Renderer *renderer ) {
  const int radius = 50;

  // Setting the color to be RED with 100% opaque (0% trasparent).
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  pos.x = 200;
  pos.y = 200;

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
