#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "game.h"
#include <memory>
#include <thread>

class Controller {
 public:
  ~Controller(){ thread.join(); };
  void HandleInput(void);
  void Simulate(void);
  void setSnakes(std::vector<std::shared_ptr<Snake>> snakes){_snakes = snakes;}
  void setGame(std::shared_ptr<Game> game){_game = game;}

 private:
  void ChangeDirection(int player, Snake::Direction input, Snake::Direction opposite) const;    
  std::shared_ptr<Game> _game;
  std::vector<std::shared_ptr<Snake>> _snakes;
  std::thread thread;

};

#endif