#include "ImageLoader.hpp"

#include <QString>

#include <exception>
#include <iostream>

ic::ImageLoader::ImageLoader()
{
}

void ic::ImageLoader::getImagePixels(std::list<std::unique_ptr<ic::Pixel>> &list)
{
    for (int x = 0; x != _image.width(); ++x)
        for (int y = 0; y != _image.height(); ++y) {
            QColor const &color = _image.pixelColor(x, y);

            list.push_back(std::make_unique<ic::Pixel>(x, y, (unsigned char)color.red(), (unsigned char)color.green(), (unsigned char)color.blue()));
        }
}

void ic::ImageLoader::updateImagePixels(std::vector<std::unique_ptr<Cluster>> const &list)
{
    for (auto i = list.cbegin(); i != list.cend(); ++i)
        for (auto j = (*i)->getPixels().cbegin(); j != (*i)->getPixels().cend(); ++j)
            _image.setPixelColor((*j)->pos.x, (*j)->pos.y, QColor((int)(*i)->getCentroid().r, (int)(*i)->getCentroid().g, (int)(*i)->getCentroid().b));
}

bool ic::ImageLoader::writeImage(std::string const &path)
{
    return _image.save(path.c_str());
}

void ic::ImageLoader::setImage(std::string const &path)
{
    _image.load(path.c_str());
    if (_image.isNull())
        throw std::exception(std::string("Image not found (" + path + ")").c_str());
}
