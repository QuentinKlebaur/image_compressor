#include "Cluster.hpp"

#include <iostream>
#include <cstdlib>

ic::Cluster::Cluster() {

}

void ic::Cluster::addPixel(std::unique_ptr<Pixel> &&pixel)
{
    _pixels.push_back(std::move(pixel));
}

void ic::Cluster::computeClusterColor()
{
    _clusterColor.r = (unsigned char) std::rand();
    _clusterColor.g = (unsigned char) std::rand();
    _clusterColor.b = (unsigned char) std::rand();
}

void ic::Cluster::setDistanceFunction(std::function<float(Color const &cl, Color const &cr)> const &function)
{
    _distFunction = function;
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


ic::Color const&ic::Cluster::getColor() const
{
    return _clusterColor;
}