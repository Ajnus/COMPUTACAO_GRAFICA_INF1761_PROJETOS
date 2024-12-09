#include "engine.h"
#include "transform.h"

RotateEarthAxis::RotateEarthAxis(TransformPtr trf) : mTrf(trf) {}

RotateEarthAxisPtr RotateEarthAxis::Make(TransformPtr trf)
{
    return RotateEarthAxisPtr(new RotateEarthAxis(trf));
}

void RotateEarthAxis::Update(float dt)
{
    mTrf->Rotate(0.00000005f, 0, 0, 1);
}

MoonOrbit::MoonOrbit(TransformPtr trf) : mTrf(trf) {}

MoonOrbitPtr MoonOrbit::Make(TransformPtr trf)
{
    return MoonOrbitPtr(new MoonOrbit(trf));
}

void MoonOrbit::Update(float dt)
{
    mTrf->Translate(-1.25f, 0, 0);
    mTrf->Rotate(60.0f * dt, 0, 0, 1);
    mTrf->Translate(1.25f, 0, 0);
}

EarthOrbit::EarthOrbit(TransformPtr trf) : mTrf(trf) {}

EarthOrbitPtr EarthOrbit::Make(TransformPtr trf)
{
    return EarthOrbitPtr(new EarthOrbit(trf));
}

void EarthOrbit::Update(float dt)
{
    mTrf->Translate(-4.5, 0, 0);
    mTrf->Rotate(45.0f * dt, 0, 0, 1);
    mTrf->Translate(4.5, 0, 0);
}

VenusOrbit::VenusOrbit(TransformPtr trf) : mTrf(trf) {}

VenusOrbitPtr VenusOrbit::Make(TransformPtr trf)
{
    return VenusOrbitPtr(new VenusOrbit(trf));
}

void VenusOrbit::Update(float dt)
{
    mTrf->Translate(-2, 0, 0);
    mTrf->Rotate(70.0f * dt, 0, 0, 1);
    mTrf->Translate(2, 0, 0);
}
