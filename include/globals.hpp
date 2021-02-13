#pragma once

struct Point
{
  float x;
  float y;

  Point() {
    x = 0;
    y = 0;
  }

  Point(float _x, float _y) {
    x = _x;
    y = _y;
  };
};

struct Size
{
  int width;
  int height;

  Size() {
    width = 0;
    height = 0;
  }

  Size(int width_, int height_) {
    width  = width_;
    height = height_;
  }
};

enum Side {
  Left,
  Right,
  Top,
  Bottom,
  None,
};
