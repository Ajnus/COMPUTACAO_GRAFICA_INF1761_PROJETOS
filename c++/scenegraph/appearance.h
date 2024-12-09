#include <memory>
class Appearance;
using  AppearancePtr = std::shared_ptr<Appearance>;

#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "state.h"

class Appearance {
public:
  virtual ~Appearance () {}
  virtual void Load (StatePtr st) = 0;
  virtual void Unload (StatePtr ) { }
};

#endif