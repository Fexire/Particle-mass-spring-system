#pragma once

#include <g2x.h>

class ParticleInterface
{
public:
    virtual void integrate(double h) = 0;

    virtual void draw() = 0;

    virtual G2Xvector &getPosition() = 0;

    virtual void updateForce(G2Xvector extForce) = 0;

    virtual G2Xvector &getVelocity() = 0;
};