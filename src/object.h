#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <thread>
#include <mutex>
#include "SDL.h"

enum ObjectType
{
  objFood,
  objSnake,
};

class Object
{
  public:
    // constructor / desctructor
    Object(ObjectType type) : _type(type){};
    ~Object(){};
    ObjectType getType() { return _type; };
    void getPosition(int &x, int &y)
    {
      x = _pos.x;
      y = _pos.y;
    };

    // typical behaviour methods
    virtual void simulate(){};


  protected:
    ObjectType _type;
    SDL_Point _pos;
    std::vector<std::thread> threads; // holds all threads that have been launched within this object
    std::mutex _mtx;
};

class Food : public Object
{
  public:
    // constructor / desctructor
    Food():Object(ObjectType::objFood){};
};

#endif