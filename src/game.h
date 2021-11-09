#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "renderer.h"
#include "snake.h"

class Game
{
  public:
    Game(std::size_t grid_width, std::size_t grid_height, int player);
    ~Game();
    void Simulate();
    void setSnakes(std::vector<std::shared_ptr<Snake>> snakes) { _snakes = snakes; }
    void setFood(std::shared_ptr<Food> food) { _food = food; }

  private:
    void PlaceFood();
    void Update();

    std::vector<std::shared_ptr<Snake>> _snakes;
    std::shared_ptr<Food> _food;
    //std::shared_ptr<Controller> _controller;
    int _nPlayer;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    std::thread thread; // holds all threads that have been launched within this object
};

#endif