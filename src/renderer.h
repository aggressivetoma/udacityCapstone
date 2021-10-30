#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <mutex>
#include <thread>
#include "object.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  //void Render(Snake const snake, SDL_Point const &food);
  void Render(void);
  void UpdateWindowTitle(int score, int fps);
  //void setSnake(std::vector<std::shared_ptr<Snake>> snakes){_snakes = snakes;}
  //void setFood(std::shared_ptr<Food> food){_food = food;}
  void setGameObjects(std::vector<std::shared_ptr<Object>> &gameObjects){_gameObjects = gameObjects;}
  void Simulate(void);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  //std::shared_ptr<Snake> _snake;
  //std::vector<std::shared_ptr<Snake>> _snakes;
  //std::shared_ptr<Food> _food;
  std::vector<std::shared_ptr<Object>> _gameObjects;

  std::thread thread;
};

#endif