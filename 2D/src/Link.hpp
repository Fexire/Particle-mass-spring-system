#pragma once

#include "Particle.hpp"
#include <g2x.h>
class Link
{
public:
    Link(ParticleInterface &p1_, ParticleInterface &p2_) : p1(p1_), p2(p2_)
    {
        l0 = p2.getPosition()- p1.getPosition();
        p1.updateForce(fre);
    }

    void draw()
    {
        g2x_Line(0, p1.getPosition(), 0, p2.getPosition(), G2Xcolor{0, 0, 0, 0}, 1);
    }

    void integrateRessortBrake()
    {
        double d = p2.getPosition()- p1.getPosition();
        double f = k * (d - l0);
        f += z * (p1.getVelocity() -  p2.getVelocity());
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
    double fre = -10;
    bool on;
};