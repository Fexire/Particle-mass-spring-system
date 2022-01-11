#pragma once

#include <g2x.h>

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
        position.y += velocity * h; // Xn+1 = Xn + h * Vn
        velocity += force * h/mass ;    // Vn+1 = Vn + h * Fn
        force = 0;
    }

    void leapFrog(double h)
    {
        velocity += force * h/mass ; // Vn+1 = Vn + h * Fn
        position.y += velocity * h;  // Xn+1 = Xn + h * Vn+1
        force = 0;
    }

    void fixed(double h)
    {
        velocity = 0;
        force = 0;
    }

    G2Xvector& getPosition()
    {
        return position;
    }

    double& getVelocity()
    {
        return velocity;
    }

    void updateForce(double extForce)
    {
        force += extForce;
    }
    
    G2Xvector position = g2x_Vector_XY(0,0);
private :
    double velocity = 0;
    double force = 0;
    double mass = 1;
    G2Xcolor color;
    double radius = 0.3;
};