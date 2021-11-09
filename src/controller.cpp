#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(int player, Snake::Direction input, Snake::Direction opposite) const {
  if (_snakes.at(player)->direction != opposite || _snakes.at(player)->_size == 1) 
    _snakes.at(player)->direction = input;
  return;
}

//void Controller::HandleInput(std::shared_ptr<Snake> snake) 
void Controller::HandleInput(void) 
{
  while(g_Running)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        g_Running = 0;
      }
      else if (e.type == SDL_KEYDOWN)
      {
        std::cout << "input key is : " << e.key.keysym.sym << std::endl;
        switch (e.key.keysym.sym)
        {

        case SDLK_ESCAPE:
          g_Running = 0;
          break;
        case SDLK_w:
          ChangeDirection(0, Snake::Direction::kUp, Snake::Direction::kDown);
          break;
        case SDLK_s:
          ChangeDirection(0, Snake::Direction::kDown, Snake::Direction::kUp);
          break;
        case SDLK_a:
          ChangeDirection(0, Snake::Direction::kLeft, Snake::Direction::kRight);
          break;
        case SDLK_d:
          ChangeDirection(0, Snake::Direction::kRight, Snake::Direction::kLeft);
          break;
        case SDLK_UP:
          ChangeDirection(1, Snake::Direction::kUp, Snake::Direction::kDown);
          break;
        case SDLK_DOWN:
          ChangeDirection(1, Snake::Direction::kDown, Snake::Direction::kUp);
          break;
        case SDLK_LEFT:
          ChangeDirection(1, Snake::Direction::kLeft, Snake::Direction::kRight);
          break;
        case SDLK_RIGHT:
          ChangeDirection(1, Snake::Direction::kRight, Snake::Direction::kLeft);
        }
      }
    }
  }
}

void Controller::Simulate(void) 
{
  thread = std::thread(&Controller::HandleInput, this);
}