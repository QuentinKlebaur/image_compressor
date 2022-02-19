#include "KMeansClustering.hpp"

#include <exception>
#include <array>
#include <algorithm>
#include <chrono>

ic::KMeansClustering::KMeansClustering(std::string const &input, std::string const &output, unsigned int k) :
    AClustering(input, output), _k(k)
{

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
    for (int i = 0; i < _k; ++i)
        _clusters.push_back(std::make_unique<Cluster>());
    int i = 0;
    do {
        std::cout << "-------------" << i << "-------------" << std::endl;
        auto time1 = std::chrono::steady_clock::now();
        resetClusters();
        auto time2 = std::chrono::steady_clock::now();
        std::cout << "elapsed time: " << ((std::chrono::duration<double>)(time2 - time1)).count() << std::endl;
        computeClusters();
        auto time3 = std::chrono::steady_clock::now();
        std::cout << "elapsed time: " << ((std::chrono::duration<double>)(time3 - time2)).count() << std::endl;
        computeCentroids();
        auto time4 = std::chrono::steady_clock::now();
        std::cout << "elapsed time: " << ((std::chrono::duration<double>)(time4 - time3)).count() << std::endl;
        ++i;
    } while (!computeEnd());
}
