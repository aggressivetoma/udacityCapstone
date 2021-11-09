#include "snake.h"
#include <cmath>
#include <iostream>
#include "common.h"


template <typename T>
T MessageQueue<T>::receive()
{
    // The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function.

    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    //_cond.wait(uLock, [this] { return !_messages.empty(); }); // pass unique lock to condition variable
    _cond.wait_for(uLock, std::chrono::milliseconds(1),[this] { return !_messages.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T msg = std::move(_messages.back());

    std::cout  << "  num of queue : " << _messages.size() << std::endl;
    //_messages.pop_back();
    // it is needed to flush queue to prevent getting previous phase
    _messages.clear();

    return msg; // will not be copied due to return value optimization (RVO) in C++
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.

    // simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    std::cout << "   Message " << msg << " has been sent to the queue" << std::endl;
    _messages.push_back(std::move(msg));
    _cond.notify_one(); // notify client after pushing new Vehicle into vector
}


void Snake::Update()
{
  // update
  // We first capture the head's cell before updating.
  SDL_Point prev_cell{static_cast<int>(posx), static_cast<int>(posy)};

  UpdateHead();

  // Capture the head's cell after updating.
  SDL_Point current_cell{static_cast<int>(posx), static_cast<int>(posy)};

  // Update all of the body vector items if the snake head has moved to a new cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  std::unique_lock<std::mutex> lck(_mutex);
  switch (direction) {
    case Direction::kUp:
      posy -= speed;
      break;

    case Direction::kDown:
      posy += speed;
      break;

    case Direction::kLeft:
      posx -= speed;
      break;

    case Direction::kRight:
      posx += speed;
      break;
  }
  // Wrap the Snake around to the beginning if going off of the screen.
  posx = fmod(posx + grid_width, grid_width);
  posy = fmod(posy + grid_height, grid_height);

  lck.unlock();
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {

  std::unique_lock<std::mutex> lck(_mutex);
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    _size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
  lck.unlock();
}

void Snake::GrowBody(ObjectType food) 
{ 
  std::cout << "grow body" << std::endl;
  growing = true; 
  //MessageQueue<ObjectType> _foodMessage.send(food);
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(posx) && y == static_cast<int>(posy)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::setDirection(Direction input)
{
  std::unique_lock<std::mutex> lck(_mutex);
  direction = input;
  lck.unlock();
}

int Snake::GetScore() const 
{ 
  return _score; 
}
int Snake::GetSize() const 
{ 
  return _size; 
}
