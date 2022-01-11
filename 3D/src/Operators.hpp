#pragma once

#include <g3x.h>

G3Xvector operator+(const G3Xvector &v, const G3Xvector &u)
{
    return G3Xvector{v.x + u.x, v.y + u.y, v.z + u.z};
}

G3Xvector operator-(const G3Xvector &v, const G3Xvector &u)
{
    return G3Xvector{v.x - u.x, v.y - u.y, v.z - u.z};
}

G3Xvector operator*(const G3Xvector &v, const G3Xvector &u)
{
    return G3Xvector{v.x * u.x, v.y * u.y, v.z * u.z};
}

G3Xvector operator/(const G3Xvector &v, const G3Xvector &u)
{
    return G3Xvector{v.x / u.x, v.y / u.y, v.z / u.z};
}

G3Xvector operator*(const G3Xvector &v, const double &u)
{
    return G3Xvector{v.x * u, v.y * u, v.z * u};
}

G3Xvector operator/(const G3Xvector &v, const double &u)
{
    return G3Xvector{v.x / u, v.y / u, v.z / u};
}