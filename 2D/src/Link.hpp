#pragma once

#include "Particle.hpp"
#include <g2x.h>
class Link
{
public:
    Link(ParticleInterface &p1_, ParticleInterface &p2_) : p1(p1_), p2(p2_)
    {
        l0 = p2.getPosition().y- p1.getPosition().y;
        p1.updateForce(fre);
    }

    void draw()
    {
        g2x_Line(p1.getPosition().x, p1.getPosition().y, p2.getPosition().x, p2.getPosition().y, G2Xcolor{0, 0, 0, 0}, 1);
    }

    void integrateRessortBrake()
    {
        double d = p2.getPosition().y- p1.getPosition().y;
        double f = k * (d - l0);
        f += z * (p2.getVelocity() -  p1.getVelocity());
        p1.updateForce(f);
        p2.updateForce(-f);
    }

    bool isOn()
    {
        return on;
    }

    void turnOff()
    {
        on = false;
    }

    void update(double k, double z)
    {
        this->k = k;
        this->z = z;
    }

private:
    ParticleInterface &p1;
    ParticleInterface &p2;
    double l0;
    double k;
    double z;
    double s;
    double fre = -10 * 100;
    bool on;
};