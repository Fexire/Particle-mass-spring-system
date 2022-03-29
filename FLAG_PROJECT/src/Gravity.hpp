#pragma once

#include "LinkInterface.hpp"
#include "Link.hpp"

class Gravity : public LinkInterface
{

public:
    Gravity(Link link_) : link(link_)
    {
    }

    void integrate()  override
    {
        link.integrateGravity();
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