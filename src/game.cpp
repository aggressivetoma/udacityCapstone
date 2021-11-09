#include "game.h"
#include "common.h"
#include <iostream>
#include "SDL.h"
#include <future>


Game::Game(std::size_t grid_width, std::size_t grid_height, int player)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      _nPlayer(player) {
  std::cout << "game constructor" << std::endl;
}

Game::~Game()
{
  thread.join();
}

void Game::PlaceFood() {
  int x, y;
  int foodIsNotOccupied = 0;

  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item 
    // before placing food.
    for(int i=0;i<2;i++)
    {
      if (!_snakes.at(i)->SnakeCell(x, y))
        foodIsNotOccupied = 1;
    }
    /* if both of snake are not ....*/
    if(foodIsNotOccupied == 1)
    {
      _food->setPositoin(x, y);
      return;
    }
  }
}

void Game::Update() {

  // initalize variables
  bool hasEnteredIntersection = false;
  double cycleDuration = 10; // duration of a single simulation cycle in ms
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;

  while (g_Running)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // compute time difference to stop watch
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
    if (timeSinceLastUpdate >= cycleDuration)
    {
      for(int i =0;i<2;i++)
      {
        if (!_snakes[i]->alive)
          return;

        _snakes[i]->Update();

        int new_x, new_y;
        _snakes[i]->getPosition(new_x, new_y);

        // Check if there's food over here
        int food_x, food_y;
        _food->getPosition(food_x, food_y);
        if (food_x == new_x && food_y == new_y)
        {
          // Grow snake and increase speed.
          _snakes[i]->IncreaseScore();
          _snakes[i]->GrowBody(_food->getType());
          _snakes[i]->speed += 0.02;

          PlaceFood();
        }
      }

      // reset stop watch for next cycle
      lastUpdate = std::chrono::system_clock::now();
    }
  }
}


void Game::Simulate()
{
  thread = std::thread(&Game::Update, this);
}