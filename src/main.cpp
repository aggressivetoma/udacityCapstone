#include <algorithm>
#include <iostream>
#include <future>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int g_Running = 1;

int main() 
{
  int run;
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  int nPlayer = 2;
  std::shared_ptr<Food> food;
  std::shared_ptr<Game> game;
  std::vector<std::shared_ptr<Snake>> snakes;

  // food
  std::cout << "create food!\n";
  food = std::make_shared<Food>(kGridWidth, kGridHeight);

  // snake
  for(int i =0;i<nPlayer;i++)
  {
    std::cout << "create snake!\n";
    auto snake = std::make_shared<Snake>(kGridWidth, kGridHeight, i);
    snakes.push_back(snake);
  }

  //game
  std::cout << "create game!\n";
  game = std::make_shared<Game>(kGridWidth, kGridHeight, nPlayer);
  game->setSnakes(snakes);
  game->setFood(food);
  game->Simulate();

  // controller
  std::cout << "create controller!\n";
  auto controller = std::make_shared<Controller>();
  controller->setSnakes(snakes);
  controller->setGame(game);
  controller->Simulate();

  // add all objects into common vector
  std::vector<std::shared_ptr<Object>> gameObjects;
  gameObjects.push_back(std::dynamic_pointer_cast<Object>(food));
  std::for_each(snakes.begin(), snakes.end(), [&gameObjects](std::shared_ptr<Snake> &snakes) {
      std::shared_ptr<Object> object = std::dynamic_pointer_cast<Object>(snakes);
      gameObjects.push_back(object);
  });

  // draw 
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  renderer.setGameObjects(gameObjects);
  renderer.Draw();

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Player1 Score: " << snakes.at(0)->GetScore() << "\n";
  std::cout << "Player1 Size: " << snakes.at(0)->GetSize() << "\n";
  std::cout << "Player2 Score: " << snakes.at(1)->GetScore() << "\n";
  std::cout << "Player2 Size: " << snakes.at(1)->GetSize() << "\n";
  return 0;
}