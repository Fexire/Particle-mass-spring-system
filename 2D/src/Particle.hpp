#pragma once

#include <g2x.h>

class Particle
{
public:
    Particle(double position_, double mass_, G2Xcolor color_) : position(position_), mass(mass_), color(color_)
    {
    }

    ~Particle() = default;

    void draw()
    {
        g2x_FillCircle(0, position, radius, color);
    }

    void eulerExp(double h)
    {
        position += velocity * h; // Xn+1 = Xn + h * Vn
        velocity += force * h ;    // Vn+1 = Vn + h * Fn
        force = 0;
    }

    void leapFrog(double h)
    {
        velocity += force * h ; // Vn+1 = Vn + h * Fn
        position += velocity * h;  // Xn+1 = Xn + h * Vn+1
        force = 0;
    }

    void fixed(double h)
    {
        velocity = 0;
        force = 0;
    }

    double& getPosition()
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
    

    double position = 0;
private :
    double velocity = 0;
    double force = 0;
    double mass = 1;
    G2Xcolor color;
    double radius = 0.3;
};