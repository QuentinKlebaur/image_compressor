#pragma once

#include "Color.hpp"
#include "Cluster.hpp"
#include "Pixel.hpp"
#include "ImageLoader.hpp"

#include <functional>
#include <vector>
#include <list>
#include <memory>

namespace ic {
    class AClustering {
        public:

            AClustering(std::string const &input, std::string const &output);
            void setDistanceFunction(std::function<float(Color const &cl, Color const &cr)> const &function);
            void run();

        protected:

            virtual void clusturingAlgorithme() = 0;

            std::string const _inputPath;
            std::string const _outputPath;
            std::function<float(Color const &cl, Color const &cr)> _distFunction = nullptr;
            std::list<std::unique_ptr<Pixel>> _pixels;
            std::vector<std::unique_ptr<Cluster>> _clusters;
            ImageLoader _image;

        private:

    };
}