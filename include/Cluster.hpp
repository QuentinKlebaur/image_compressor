#pragma once

#include "Color.hpp"
#include "Pixel.hpp"

#include <list>
#include <memory>

namespace ic {
    class Cluster {
        public:

            Cluster();

            void addPixel(std::unique_ptr<Pixel> &&pixel);
            void computeCentroid();
            void emptyPixels(std::list<std::unique_ptr<Pixel>> &list);
            void display() const;
            bool hasMoved() const;
            Color const &getCentroid() const;

        private:

            std::list<std::unique_ptr<Pixel>> _pixels;
            Color _centroid;
            Color _lastCentroid;
    };
}