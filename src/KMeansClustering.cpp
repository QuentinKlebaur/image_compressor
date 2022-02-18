#include "KMeansClustering.hpp"

#include <exception>
#include <array>
#include <algorithm>

ic::KMeansClustering::KMeansClustering(std::string const &input, std::string const &output, unsigned int k) :
    AClustering(input, output), _k(k)
{

}

void ic::KMeansClustering::computeClusters() {
    while (!_pixels.empty()) {
        auto pixel = _pixels.begin();
        size_t k = _k;
        std::vector<float> distances;

        for (int j = 0; j < _k; ++j)
            distances.push_back(_distFunction(_clusters[j]->getCentroid(), (*pixel)->color));
        auto min = std::min_element(distances.begin(), distances.end());
        _clusters[std::distance(distances.begin(), min)]->addPixel(std::move(_pixels.front()));
        _pixels.pop_front();
    }
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
    for (int i = 0; i < _k; ++i)
        _clusters.push_back(std::make_unique<Cluster>());
    int i = 0;
    do {
        std::cout << "-------------" << i << "-------------" << std::endl;
        resetClusters();
        computeClusters();
        computeCentroids();
        ++i;
    } while (!computeEnd());
}
