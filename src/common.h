#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <thread>
#include <mutex>
#include "SDL.h"

extern int g_Running;

enum ObjectType
{
  objFood,
  objSuperFood,
  objSnake,
};

class Object
{
  public:
    // constructor / desctructor
    Object(ObjectType type) : _type(type){};
    ~Object(){};
    ObjectType getType() { return _type; };
    void setPositoin(int x, int y) { posx = (float)x; posy = (float)y;}
    void getPosition(int &x, int &y) { x = (int)posx; y = (int)posy; };

    // typical behaviour methods
    virtual void simulate(){};
    std::mutex _mutex;

  protected:
    ObjectType _type;
    float posx;
    float posy;
};

class Food : public Object
{
  public:
    // constructor / desctructor
    Food(int grid_width, int grid_height):Object(ObjectType::objFood){ 
      posx = (grid_width / 2);
      posy = (grid_height / 2);
    };
};

#endif