#pragma once

#include "ParticleInterface.hpp"
#include "Particle.hpp"
#include <g2x.h>

class FixedParticle : public ParticleInterface
{
public:
    FixedParticle(Particle particle_) : particle(particle_)
    {
    }

    ~FixedParticle() = default;

    void integrate(double h) override
    {
        particle.fixed(h);
    }

    void draw() override
    {
        particle.draw();
    }

    G2Xvector &getPosition() override
    {
        return particle.getPosition();
    }

    void updateForce(G2Xvector extForce) override
    {
        particle.updateForce(extForce);
    }

    G2Xvector &getVelocity() override
    {
        return particle.getVelocity();
    }

private:
    Particle particle;
};
