#pragma once

#include <iostream>

namespace ic {
    struct Color {
        Color(unsigned char R=0, unsigned char G=0, unsigned char B=0) {
            r = R;
            g = G;
            b = B;
        }

        bool operator==(Color const &rhs) const {
            return r == rhs.r && g == rhs.g && b == rhs.b;
        }

        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        ~Color() = default;
    };
}
std::ostream& operator<<(std::ostream& os, const ic::Color& color);