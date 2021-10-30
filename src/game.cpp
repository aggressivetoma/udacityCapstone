#include "game.h"
#include <iostream>
#include "SDL.h"
#include <future>


Game::Game(std::size_t grid_width, std::size_t grid_height, int player)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      _nPlayer(player) {
  PlaceFood();
}

//void Game::Run(Controller const &controller, Renderer &renderer,
#if 0
void Game::Run(Controller const &controller, std::size_t target_frame_duration) {
  bool running = true;

  //while (running) {
    //frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //controller.HandleInput(running, _snake);
    // it will be replace to thread
    Update();
    // replace it to thread
    //renderer.Render(snake, food);

    /*
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }
    */

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    /*
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    */
  //}
}
#endif

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    // todo
    /*
    if (!snake.SnakeCell(x, y)) {
      _food->x = x;
      _food->y = y;
      return;
    }
    */
  }
}

void Game::Update() {
  // print id of the current thread
  //std::unique_lock<std::mutex> lck(_mtx);
  //std::cout << "snake thread id = " << std::this_thread::get_id() << std::endl;
  //lck.unlock();

  // initalize variables
  bool hasEnteredIntersection = false;
  double cycleDuration = 10; // duration of a single simulation cycle in ms
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;

  while (1)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // compute time difference to stop watch
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
    if (timeSinceLastUpdate >= cycleDuration)
    {
      //todo
      /*
      if (!_snake->alive)
        return;
      */

      // todo
      /*
      _snake->Update();

      int new_x = static_cast<int>(_snake->head_x);
      int new_y = static_cast<int>(_snake->head_y);

      // Check if there's food over here
      int posx, posy;
      _food->getPosition(posx, posy);
      if (posx == new_x && posy == new_y)
      {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        _snake->GrowBody();
        _snake->speed += 0.02;
      }
      */

      // reset stop watch for next cycle
      lastUpdate = std::chrono::system_clock::now();

    }
  }
}

int Game::GetScore() const 
{ 
  //return score; 
  return 1;
}
int Game::GetSize() const 
{ 
  //return snake.size; 
  return 1;
}

void Game::Simulate()
{
  thread = std::thread(&Game::Update, this);
}