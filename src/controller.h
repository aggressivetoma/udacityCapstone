#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>
#include <thread>

class Controller {
 public:
  //void HandleInput(bool &running, Snake &snake) const;
  //void HandleInput( Snake &snake) const;
  //void HandleInput(std::shared_ptr<Snake> snake);
  void HandleInput(void);
  void Simulate(void);
  void setSnake(std::shared_ptr<Snake> snake){_snake = snake;}

 private:
  //void ChangeDirection(Snake &snake, Snake::Direction input,
  void ChangeDirection(Snake::Direction input, Snake::Direction opposite) const;    
  std::vector<std::thread> threads;
  std::shared_ptr<Snake> _snake;

};

#endif