#include <memory>
class Engine;
using EnginePtr = std::shared_ptr<Engine>; 

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
  protected:
  Engine () {}
  public:
  virtual ~Engine () {}
  virtual void Update (float dt) = 0;  // to update the world
};

#endif