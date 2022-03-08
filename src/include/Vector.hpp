#pragma once

#include <iostream>

namespace ic {
    struct Vector {
        Vector(unsigned int X=0, unsigned int Y=0) {
            x = X;
            y = Y;
        }

        unsigned int x = 0;
        unsigned int y = 0;
        ~Vector() = default;
    };
}
std::ostream& operator<<(std::ostream& os, const ic::Vector& color);