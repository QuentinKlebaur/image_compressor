#pragma once

#include <iostream>

namespace ic {
    struct Vector {
        Vector(unsigned int X=0, unsigned int Y=0) {
            x = X;
            y = Y;
        }

        unsigned char x = 0;
        unsigned char y = 0;
        ~Vector() = default;
    };
}
std::ostream& operator<<(std::ostream& os, const ic::Vector& color);