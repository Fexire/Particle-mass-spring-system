#pragma once

#include <g2x.h>
#include "Operators.hpp"

class Particle
{
public:
    Particle(G2Xvector position_, double mass_, G2Xcolor color_) : position(position_), mass(mass_), color(color_)
    {
    }

    ~Particle() = default;

    void draw()
    {
        g2x_FillCircle(position.x,position.y , radius, color);
    }

    void eulerExp(double h)
    {
        position = position + velocity * h; // Xn+1 = Xn + h * Vn
        velocity = velocity + force * h/mass ;    // Vn+1 = Vn + h * Fn
        force = g2x_Vector_XY(0,0);
    }

    void leapFrog(double h)
    {
        velocity = velocity + force * h/mass ; // Vn+1 = Vn + h * Fn
        position = position + velocity * h;  // Xn+1 = Xn + h * Vn+1
        force = g2x_Vector_XY(0,0);
    }

    void fixed(double h)
    {
        velocity = g2x_Vector_XY(0,0);
        force = g2x_Vector_XY(0,0);
    }

    G2Xvector& getPosition()
    {
        return position;
    }

    G2Xvector& getVelocity()
    {
        return velocity;
    }

    void updateForce(G2Xvector extForce)
    {
        force = force + extForce;
    }
    
    G2Xvector position = g2x_Vector_XY(0,0);
private :
    G2Xvector velocity = g2x_Vector_XY(0,0);
    G2Xvector force = g2x_Vector_XY(0,0);
    double mass = 1;
    G2Xcolor color;
    double radius = 0.3;
};