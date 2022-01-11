#pragma once

#include "LinkInterface.hpp"
#include "Link.hpp"

class Spring : public LinkInterface
{

public:
    Spring(Link link_) : link(link_)
    {
    }

    void integrate(double k,double z)  override
    {
        link.update(k,z);
        link.integrateRessortBrake();
    }

    void draw() override
    {
        link.draw();
    }

    bool isOn() override
    {
        return link.isOn();
    }

    void turnOff()
    {
        link.turnOff();
    }

private:
    Link link;
};