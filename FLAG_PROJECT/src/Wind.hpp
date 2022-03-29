#pragma once

#include "LinkInterface.hpp"
#include "Link.hpp"

class Wind : public LinkInterface
{

public:
    Wind(Link link_) : link(link_)
    {
    }

    void integrate()  override
    {
        link.integrateWind();
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