#pragma once

#include "Pixel.hpp"
#include "Cluster.hpp"

#include <QImage>

#include <list>
#include <memory>

namespace ic {
    class ImageLoader
    {
        public:

            ImageLoader();

            void getImagePixels(std::list<std::unique_ptr<ic::Pixel>> &list);
            void updateImagePixels(std::vector<std::unique_ptr<Cluster>> const &list);
            bool writeImage(std::string const &path);
            void setImage(std::string const &path);

        private:

            QImage _image;
    };
}