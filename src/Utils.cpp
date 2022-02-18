#include "Color.hpp"
#include "Vector.hpp"
#include "Pixel.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const ic::Color& color)
{
    os << "[Color](" << (int)color.r << ',' << (int)color.g << ',' << (int)color.b << ')';
    return os;
}


std::ostream& operator<<(std::ostream& os, const ic::Vector& vector)
{
    os << "[Vector](" << (int)vector.x << ',' << (int)vector.y << ')';
    return os;
}


std::ostream& operator<<(std::ostream& os, const ic::Pixel& pixel)
{
    os << "[Pixel](" << pixel.pos << ',' << pixel.color << ')';
    return os;
}