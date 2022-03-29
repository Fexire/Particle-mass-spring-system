#pragma once

#include "ParticleInterface.hpp"
#include "Particle.hpp"
#include <g3x.h>

class MovingParticle : public ParticleInterface
{
public:
    MovingParticle(Particle particle_) : particle(particle_)
    {
    }

    ~MovingParticle() = default;

    void integrate(double h) override
    {
        particle.leapFrog(h);
    }

    void draw() override
    {
        particle.draw();
    }

    G3Xvector &getPosition() override
    {
        return particle.getPosition();
    }

    void updateForce(G3Xvector extForce) override
    {
        particle.updateForce(extForce);
    }

    G3Xvector &getVelocity() override
    {
        return particle.getVelocity();
    }

private:
    Particle particle;
};
