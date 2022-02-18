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
    }
}

void ic::KMeansClustering::resetClusters() {
    for (auto i = _clusters.begin(); i != _clusters.end(); ++i)
        (*i)->emptyPixels(_pixels);
}

void ic::KMeansClustering::computeCentroids() {
    for (auto i = _clusters.begin(); i != _clusters.end(); ++i)
        (*i)->computeCentroid();
}


bool ic::KMeansClustering::computeEnd() {
    for (auto i = _clusters.cbegin(); i != _clusters.cend(); ++i)
        if ((*i)->hasMoved())
            return false;
    return true;
}

void ic::KMeansClustering::clusturingAlgorithme()
{
    std::cout << "Algo starts running" << std::endl;
    for (int i = 0; i < _k; ++i)
        _clusters.push_back(std::make_unique<Cluster>());
    std::cout << "Clusters created" << std::endl;
    do {
        std::cout << "Before" << std::endl;
        computeClusters();
        std::cout << "Clusters Computed" << std::endl;
        computeCentroids();
        std::cout << "Centroids Computed" << std::endl;
        resetClusters();
        std::cout << "Clusters Reseted" << std::endl;
    } while (!computeEnd());
}
