#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <mutex>
#include <thread>
#include "common.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(void);
  void UpdateWindowTitle(int score, int fps);
  void setGameObjects(std::vector<std::shared_ptr<Object>> &gameObjects){_gameObjects = gameObjects;}
  void Draw(void);
  void Simulate(void);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  std::vector<std::shared_ptr<Object>> _gameObjects;

  std::thread thread;
};

#endif