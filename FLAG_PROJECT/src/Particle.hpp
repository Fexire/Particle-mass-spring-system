#pragma once

#include <g3x.h>
#include "Operators.hpp"

class Particle
{
public:
    Particle(G3Xvector position_, double mass_, G3Xcolor color_) : position(position_), mass(mass_), color(color_)
    {
    }

    ~Particle() = default;

    void draw()
    {
        g3x_Color4fv(color);
        glBegin(GL_POINTS);
        g3x_Vertex3dv(position);
        glEnd();
    }

    void eulerExp(double h)
    {
        position = position + velocity * h;     // Xn+1 = Xn + h * Vn
        velocity = velocity + force * h / mass; // Vn+1 = Vn + h * Fn
        force = G3Xvector{0, 0, 0};
    }

    void leapFrog(double h)
    {
        velocity = velocity + force * h / mass; // Vn+1 = Vn + h * Fn
        position = position + velocity * h;     // Xn+1 = Xn + h * Vn+1
        force = G3Xvector{0, 0, 0};
    }

    void fixed(double h)
    {
        velocity = G3Xvector{0, 0, 0};
        force = G3Xvector{0, 0, 0};
    }

    G3Xvector &getPosition()
    {
        return position;
    }

    G3Xvector &getVelocity()
    {
        return velocity;
    }

    void updateForce(G3Xvector extForce)
    {
        force = force + extForce;
    }

    G3Xvector position{0, 0, 0};

private:
    G3Xvector velocity{0, 0, 0};
    G3Xvector force{0, 0, 0};
    double mass = 1;
    G3Xcolor color;
    double radius = 0.3;
};