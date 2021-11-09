#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include <iostream>
#include <deque>
#include <condition_variable>
#include "SDL.h"
#include "common.h"

template <typename T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _messages;
};

class Snake : public Object  
{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int player)
      : grid_width(grid_width), grid_height(grid_height), Object(ObjectType::objSnake)
  {
    _player = player;
    if (player == 0)
    {
      posx = (grid_width / 4);
      posy = (grid_height / 2);
    }
    else if (player == 1)
    {
      posx = ((grid_width / 4) * 3);
      posy = (grid_height / 2);
    }
    std::cout << "snake constructor. x:" << posx << " y:" << posy << std::endl;
  }

  void Update();
  void GrowBody(ObjectType food); 
  bool SnakeCell(int x, int y);
  void setDirection(Direction input);
  int getPlayer() { return _player; };
  void IncreaseScore(){ _score++; };
  int GetScore() const;
  int GetSize() const;

  Direction direction = Direction::kUp;

  float speed{0.1f};
  bool alive{true};
  std::vector<SDL_Point> body;
  int _score{0};
  int _size{0};

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  int _player;
  MessageQueue<ObjectType> _foodMessage;
};

#endif