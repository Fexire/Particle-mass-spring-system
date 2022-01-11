#pragma once

#include <g2x.h>

G2Xvector operator+(const G2Xvector& v,const G2Xvector& u )
{
    return g2x_Vector_XY(v.x + u.x,v.y + u.y);
}

G2Xvector operator-(const G2Xvector& v,const G2Xvector& u )
{
    return g2x_Vector_XY(v.x - u.x,v.y - u.y);
}

G2Xvector operator*(const G2Xvector& v,const G2Xvector& u )
{
    return g2x_Vector_XY(v.x * u.x,v.y * u.y);
}

G2Xvector operator/(const G2Xvector& v,const G2Xvector& u )
{
    return g2x_Vector_XY(v.x / u.x,v.y / u.y);
}

G2Xvector operator*(const G2Xvector& v,const double& u )
{
    return g2x_Vector_XY(v.x * u,v.y * u);
}

G2Xvector operator/(const G2Xvector& v,const double& u )
{
    return g2x_Vector_XY(v.x / u,v.y / u);
}