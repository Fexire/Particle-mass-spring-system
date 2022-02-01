#pragma once

#include "LinkInterface.hpp"
#include "Link.hpp"

class Spring : public LinkInterface
{

public:
    Spring(Link link_, double k_, double z_) : link(link_), k(k_), z(z_)
    {
        l0 = link.getl0();
    }

    void integrate() override
    {
        link.integrateRessortBrake(l0,k,z);
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
    double k;
    double z;
    double l0;
};