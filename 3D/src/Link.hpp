#pragma once

#include "Particle.hpp"
#include <iostream>
class Link
{
public:
    Link(ParticleInterface &p1_, ParticleInterface &p2_,G3Xcolor color_) : p1(p1_), p2(p2_),color(color_)
    {
    }

    void draw()
    {
        g3x_Color4fv({(float)force.x,(float)force.y,(float)force.z});
        /*
        float power = g3x_Norm(force);
        g3x_Color4fv({power/200.f,1,0});
        */
        //g3x_Color4fv({(1 - distance) * 1.9f ,0,0});
        glBegin(GL_LINES);
        g3x_Vertex3dv(p1.getPosition());
        g3x_Vertex3dv(p2.getPosition());
        glEnd();
    }

    void integrateRessortBrake(double l0, double k, double z)
    {
        G3Xvector f = p2.getPosition() - p1.getPosition();
        double d = g3x_Dist(p1.getPosition(), p2.getPosition());
        double a = k * (1 - l0 / d);
        f = f * a;
        f = f + ((p2.getVelocity() - p1.getVelocity()) * z);
        p1.updateForce(f);
        p2.updateForce(f * -1);
        distance = l0/d;
        force=f;
    }

    void integrateGravity()
    {
        p1.updateForce(G3Xvector{0, 0, -10});
    }

    void integrateWind()
    {
        p1.updateForce(G3Xvector{0, std::rand() / double(RAND_MAX) * 50., std::rand() / double(RAND_MAX) * 50.});
    }

    double getl0()
    {
        return g3x_Dist(p1.getPosition(),p2.getPosition());
    }

    bool isOn()
    {
        return on;
    }

    void turnOff()
    {
        on = false;
    }

private:
    ParticleInterface &p1;
    ParticleInterface &p2;
    G3Xvector force;
    float distance;
    G3Xcolor color;
    bool on;
};