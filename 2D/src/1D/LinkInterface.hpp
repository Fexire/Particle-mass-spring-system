#pragma once

class LinkInterface
{
public:
    virtual void integrate(double k,double z) = 0;

    virtual void draw() = 0;

    virtual bool isOn() = 0;

    virtual void turnOff() = 0;
};