#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game
{
  public:
    Game(std::size_t grid_width, std::size_t grid_height, int player);
    // void Run(Controller const &controller, Renderer &renderer,
    // void Run(Controller const &controller, std::size_t target_frame_duration);
    void Simulate();
    int GetScore() const;
    int GetSize() const;
    void setSnake(std::vector<std::shared_ptr<Snake>> &snakes) { _snakes = snakes; }
    void setFood(std::shared_ptr<Food> foods) { _foods = foods; }

  private:
    // std::shared_ptr<Snake> _snakes;
    std::vector<std::shared_ptr<Snake>> _snakes;
    std::shared_ptr<Food> _foods;
    int _nPlayer;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int score{0};

    void PlaceFood();
    void Update();

    std::thread thread; // holds all threads that have been launched within this object
};

#endif