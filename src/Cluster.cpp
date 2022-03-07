#include "Cluster.hpp"

#include <iostream>
#include <cstdlib>

ic::Cluster::Cluster() {
    _centroid.r = (unsigned char) std::rand();
    _centroid.g = (unsigned char) std::rand();
    _centroid.b = (unsigned char) std::rand();
}

void ic::Cluster::addPixel(std::unique_ptr<Pixel> &&pixel)
{
    _pixels.push_front(std::move(pixel));
}

void ic::Cluster::computeCentroid()
{
    unsigned long x = 0;
    unsigned long y = 0;
    unsigned long z = 0;

    _lastCentroid = _centroid;
    for (auto i = _pixels.cbegin(); i != _pixels.cend(); ++i) {
        x += (*i)->color.r;
        y += (*i)->color.g;
        z += (*i)->color.b;
    }
    if (!_pixels.empty()) {
        _centroid.r = x / _pixels.size();
        _centroid.g = y / _pixels.size();
        _centroid.b = z / _pixels.size();
    }
}


void ic::Cluster::addPixels(std::list<std::unique_ptr<ic::Pixel>> &list)
{
    _pixels.splice(_pixels.end(), list);
}

void ic::Cluster::emptyPixels(std::list<std::unique_ptr<Pixel>> &list)
{
    list.splice(list.end(), _pixels);
}

void ic::Cluster::display() const
{
    std::cout << "[Cluster]" << std::endl;
    for (auto i = _pixels.begin(); i != _pixels.end(); ++i)
        std::cout << **i << std::endl;
}

ic::Color const &ic::Cluster::getCentroid() const
{
    return _centroid;
}

bool ic::Cluster::hasNotMoved() const
{
    return _lastCentroid == _centroid;
}


std::list<std::unique_ptr<ic::Pixel>> const &ic::Cluster::getPixels() const
{
    return _pixels;
}