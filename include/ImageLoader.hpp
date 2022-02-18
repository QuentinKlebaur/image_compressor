#pragma once

#include "Pixel.hpp"

#include <QImage>

#include <list>
#include <memory>

namespace ic {
    class ImageLoader
    {
        public:

            ImageLoader();

            void getImagePixels(std::list<std::unique_ptr<ic::Pixel>> &list);
            void updateImagePixels(std::list<std::unique_ptr<ic::Pixel>> const &list);
            bool writeImage(std::string const &path);
            void setImage(std::string const &path);

        private:

            QImage _image;
    };
}