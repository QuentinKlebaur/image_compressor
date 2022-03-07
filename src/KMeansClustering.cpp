#include "KMeansClustering.hpp"

#include <exception>
#include <array>
#include <algorithm>
#include <chrono>

ic::KMeansClustering::KMeansClustering(std::string const &input, std::string const &output, unsigned int k) :
    AClustering(input, output), _k(k)
{
    if (_k <= 0)
        _k = 1;
}

void ic::KMeansClustering::computeClusters() {
    for (auto i = _pixels.begin(); i != _pixels.end(); ++i) {
        int index = 0;
        float min = _distFunction(_clusters[0]->getCentroid(), (*i)->color);
        float tmp;

        for (int j = 1; j < _k; ++j) {
            tmp = _distFunction(_clusters[j]->getCentroid(), (*i)->color);
            if (tmp < min) {
                min = tmp;
                index = j;
            }
        }
        _clusters[index]->addPixel(std::move(*i));
        //auto min = std::min_element(distances.begin(), distances.end());
        //_clusters[std::distance(distances.begin(), min)]->addPixel(std::move(*i));
    }
    _pixels.clear();
}

void ic::KMeansClustering::resetClusters() {
    for (auto i = _clusters.begin(); i != _clusters.end(); ++i)
        (*i)->emptyPixels(_pixels);
}

void ic::KMeansClustering::computeCentroids() {
    for (auto i = _clusters.begin(); i != _clusters.end(); ++i) {
        (*i)->computeCentroid();
    }
}


bool ic::KMeansClustering::computeEnd() {
    for (auto i = _clusters.cbegin(); i != _clusters.cend(); ++i)
        if (!(*i)->hasNotMoved())
            return false;
    return true;
}

void ic::KMeansClustering::clusturingAlgorithme()
{
    int i = 0;

    for (int i = 0; i < _k; ++i)
        _clusters.push_back(std::make_unique<Cluster>());
    do {
        std::cout << "------------- " << ++i << " Loop -------------" << std::endl;
        resetClusters();
        computeClusters();
        computeCentroids();
    } while (!computeEnd());
}
