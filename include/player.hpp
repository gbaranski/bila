#include "entity.hpp"

#pragma once

class Player: public Entity {
  public:
    Player(int x, int y) noexcept;
    ~Player() noexcept;
};
