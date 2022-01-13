#pragma once

#include "Particle.hpp"
class Link
{
public:
    Link(ParticleInterface &p1_, ParticleInterface &p2_) : p1(p1_), p2(p2_)
    {
        l0 = g3x_Dist(p1.getPosition(),p2.getPosition());
    }

    void draw()
    {
        g3x_Color4fv(G3Xcolor{(float)k,(float)z,1});
        glBegin(GL_LINES);
        g3x_Vertex3dv(p1.getPosition());
        g3x_Vertex3dv(p2.getPosition());
        glEnd();
    }

    void integrateRessortBrake()
    {
        G3Xvector f = p2.getPosition() - p1.getPosition();
        double d = g3x_Dist(p1.getPosition(),p2.getPosition());
        double a = k * (1 - l0/d) ;
        f = f * a;
        f = f + ((p2.getVelocity() - p1.getVelocity()) * z );
        p1.updateForce(f);
        p2.updateForce(f * -1);
    }

    void integrateGravity()
    {
        p1.updateForce(G3Xvector{0,-10,0});
    }

    void integrateWind()
    {
        p1.updateForce(G3Xvector{0,std::rand() / double(RAND_MAX) * 1.,std::rand() / double(RAND_MAX) * 10.});
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