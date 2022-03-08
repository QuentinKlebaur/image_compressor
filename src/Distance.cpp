#include "Distance.hpp"

#include <cmath>

float ic::euclideanDistance(Color const &cl, Color const &cr)
{
    short x1 = (short)cl.r;
    short y1 = (short)cl.g;
    short z1 = (short)cl.b;
    short x2 = (short)cr.r;
    short y2 = (short)cr.g;
    short z2 = (short)cr.b;

    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2) + std::pow(z1 - z2, 2));
}

float ic::manhattanDistance(Color const &cl, Color const &cr)
{
    short x1 = (short)cl.r;
    short y1 = (short)cl.g;
    short z1 = (short)cl.b;
    short x2 = (short)cr.r;
    short y2 = (short)cr.g;
    short z2 = (short)cr.b;

    return std::abs(x1 - x2) + std::abs(y1 - y2) + std::abs(z1 - z2);
}
