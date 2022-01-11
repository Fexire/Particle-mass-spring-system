#pragma once

#include <g3x.h>

class ParticleInterface
{
public:
    virtual void integrate(double h) = 0;

    virtual void draw() = 0;

    virtual G3Xvector &getPosition() = 0;

    virtual void updateForce(G3Xvector extForce) = 0;

    virtual G3Xvector &getVelocity() = 0;
};