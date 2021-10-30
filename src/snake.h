#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <thread>
#include <memory>
#include "SDL.h"
#include "object.h"

class Snake : public Object  
{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int player)
      : grid_width(grid_width), grid_height(grid_height), Object(ObjectType::objSnake)
  {
    if (player == 0)
    {
      head_x = (grid_width / 4);
      head_y = (grid_height / 2);
    }
    else if (player == 1)
    {
      head_x = ((grid_width / 4) * 3);
      head_y = (grid_height / 2);
    }
  }

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  void Simulate();
  void setDirection(Direction input);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x; // use _pos in object
  float head_y; // use _pos in object
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif