#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

//void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
void Controller::ChangeDirection(Snake::Direction input, Snake::Direction opposite) const {
  if (_snake->direction != opposite || _snake->size == 1) 
    _snake->direction = input;
  return;
}

//void Controller::HandleInput(std::shared_ptr<Snake> snake) 
void Controller::HandleInput(void) 
{
  while (1)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        // todo : treat running
        //running = false;
      }
      else if (e.type == SDL_KEYDOWN)
      {
        std::cout << "input key is : " << e.key.keysym.sym << std::endl;
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
          ChangeDirection(Snake::Direction::kUp, Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(Snake::Direction::kDown, Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(Snake::Direction::kLeft, Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(Snake::Direction::kRight, Snake::Direction::kLeft);
          break;
        }
      }
    }
  }
}

void Controller::Simulate(void) 
{
  threads.emplace_back(std::thread(&Controller::HandleInput, this));
}