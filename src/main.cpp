#include <cstdio>
#include <stdio.h>
#include "game.hpp"

int main() {
  Game game;
  printf("starting game\n");
  try {
    game.init();
  } catch(const char* e) {
    printf("fail game init: %s\n", SDL_GetError());
    return 1;
  }

  game.run();
}
