#pragma once

struct Point
{
  float x;
  float y;

  Point();

  Point(float _x, float _y);
};

enum Side {
  Left,
  Right,
  Top,
  Bottom,
  None,
};
