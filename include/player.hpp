#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:
  Player(Point _pos) noexcept;
  ~Player() noexcept;
};
