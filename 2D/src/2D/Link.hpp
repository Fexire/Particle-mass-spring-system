#pragma once

#include "Particle.hpp"
class Link
{
public:
    Link(ParticleInterface &p1_, ParticleInterface &p2_) : p1(p1_), p2(p2_)
    {
        l0 = g2x_Dist(p1.getPosition(),p2.getPosition());
    }

    void draw()
    {
        g2x_Line(p1.getPosition().x, p1.getPosition().y, p2.getPosition().x, p2.getPosition().y, G2Xcolor{0, 0, 0, 0}, 1);
    }

    void integrateRessortBrake()
    {
        G2Xvector f = g2x_Vector(p1.getPosition(),p2.getPosition());
        double d = g2x_Dist(p1.getPosition(),p2.getPosition());
        double a = k * (1 - l0/d) ;
        f = f * a;
        f = f + ((p2.getVelocity() - p1.getVelocity()) * z );
        p1.updateForce(f);
        p2.updateForce(f * -1);
    }

    void integrateGravity()
    {
        p1.updateForce(g2x_Vector_XY(0,-10));
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
    bool on;
};