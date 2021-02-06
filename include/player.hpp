#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:
  Player(World *world, Point _position) noexcept;
  ~Player() noexcept;

  void jump() noexcept;
  void moveLeft() noexcept;
  void moveRight() noexcept;
};
