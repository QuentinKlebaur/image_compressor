#pragma once

#include "Color.hpp"
#include "Pixel.hpp"

#include <list>
#include <memory>
#include <functional>

namespace ic {
    class Cluster {
        public:

            Cluster();

            void addPixel(std::unique_ptr<Pixel> &&pixel);
            void computeClusterColor();
            void setDistanceFunction(std::function<float(Color const &cl, Color const &cr)> const &function);
            void emptyPixels(std::list<std::unique_ptr<Pixel>> &list);
            void display() const;
            Color const&getColor();

        private:

            std::list<std::unique_ptr<Pixel>> _pixels;
            Color _clusterColor;
            std::function<float(Color const &cl, Color const &cr)> _distFunction = nullptr;
    };
}