#include <algorithm>
#include <iostream>
#include <future>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  int nPlayer = 2;
  std::shared_ptr<Food> food;
  std::shared_ptr<Game> game;
  std::vector<std::shared_ptr<Snake>> snakes;
  std::vector<std::shared_ptr<Controller>> controllers;

  // food
  food = std::make_shared<Food>();

  // snake
  for(int i =0;i<nPlayer;i++)
  {
    snakes.push_back(std::make_shared<Snake>(kGridWidth, kGridHeight, i));
    //snakes.at(i)->Simulate;
  }

  // controller
  for(int i =0;i<nPlayer;i++)
  {
    controllers.push_back(std::make_shared<Controller>());
    controllers.at(i)->setSnake(snakes.at(i));
    //controllers.at(i)->Simulate;
  }

  //game
  game = std::make_shared<Game>(kGridWidth, kGridHeight, nPlayer);
  game->setSnake(snakes);
  game->setFood(food);
  game->Simulate();

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
  renderer.Simulate();


  std::cout << "Game has terminated successfully!\n";
  //std::cout << "Score: " << game.GetScore() << "\n";
  //std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}