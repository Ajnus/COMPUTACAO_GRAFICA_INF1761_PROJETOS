#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include "transform.h"

class Engine
{
protected:
  Engine() {}

public:
  virtual ~Engine() {}
  virtual void Update(float dt) = 0; // atualizar o mundo
};

using EnginePtr = std::shared_ptr<Engine>;


class RotateEarthAxis : public Engine
{
  TransformPtr mTrf;

protected:
  RotateEarthAxis(TransformPtr trf);

public:
  static std::shared_ptr<RotateEarthAxis> Make(TransformPtr trf);
  virtual void Update(float dt) override;
};
using RotateEarthAxisPtr = std::shared_ptr<RotateEarthAxis>;


class MoonOrbit : public Engine
{
  TransformPtr mTrf;

protected:
  MoonOrbit(TransformPtr trf);

public:
  static std::shared_ptr<MoonOrbit> Make(TransformPtr trf);
  virtual void Update(float dt) override;
};
using MoonOrbitPtr = std::shared_ptr<MoonOrbit>;


class EarthOrbit : public Engine
{
  TransformPtr mTrf;

protected:
  EarthOrbit(TransformPtr trf);

public:
  static std::shared_ptr<EarthOrbit> Make(TransformPtr trf);
  virtual void Update(float dt) override;
};
using EarthOrbitPtr = std::shared_ptr<EarthOrbit>;


class VenusOrbit : public Engine
{
  TransformPtr mTrf;

protected:
  VenusOrbit(TransformPtr trf);

public:
  static std::shared_ptr<VenusOrbit> Make(TransformPtr trf);
  virtual void Update(float dt) override;
};
using VenusOrbitPtr = std::shared_ptr<VenusOrbit>;

#endif
