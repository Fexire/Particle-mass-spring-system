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
        G3Xvector force_norm = force;
        g3x_Normalize(&force_norm);
        g3x_Color4fv({(float)(force.x+1)/2,(float)(force.y+1)/2,(float)(force.z+1)/2});
        G3Xvector mid_position = p1.getPosition() + ((p2.getPosition() - p1.getPosition()) /2) ;
        glBegin(GL_LINES);
        g3x_Vertex3dv(mid_position);
        g3x_Vertex3dv(mid_position + force_norm);
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
        force=f;
    }

    void integrateGravity()
    {
        p1.updateForce(G3Xvector{0, 0, -10});
    }

    void integrateWind()
    {
        p1.updateForce(G3Xvector{0, 25., 25.});
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
    G3Xvector force = {0,0,0};
    G3Xcolor color;
    bool on;
};