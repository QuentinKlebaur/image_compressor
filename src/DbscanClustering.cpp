#include "DbscanClustering.hpp"

#include <list>

ic::DbscanClustering::DbscanClustering(std::string const &input, std::string const &output, float epsilon) :
   AClustering(input, output), _epsilon(epsilon)
{

}


void ic::DbscanClustering::addNearPixels(std::unique_ptr<Pixel> const &pixel, std::list<std::unique_ptr<Pixel>> &list, std::unique_ptr<Cluster> &cluster, std::vector<Color> &colorContained)
{
    auto i = _pixels.begin();

    while(i != _pixels.end()) {
        if (_distFunction(pixel->color, (*i)->color) < _epsilon) {
            if (std::find(colorContained.begin(), colorContained.end(), (*i)->color) == colorContained.end())
                cluster->addPixel(std::move(*i));
            else
                list.push_back(std::move(*i));
            _pixels.erase(i++);
        } else
            ++i;
    }
}

void ic::DbscanClustering::computeCluster()
{
    std::list<std::unique_ptr<Pixel>> list;
    std::unique_ptr<Cluster> cluster = std::make_unique<Cluster>();
    std::vector<Color> colorContained;

    list.push_back(std::move(_pixels.front()));
    _pixels.pop_front();

    while (!list.empty()) {
        std::unique_ptr<Pixel> currentPixel = std::move(list.front());

        list.pop_front();
        colorContained.push_back(currentPixel->color);
        addNearPixels(currentPixel, list, cluster, colorContained);
        cluster->addPixel(std::move(currentPixel));
    }
    std::cout << "Cluster size: " << cluster->getPixels().size() << std::endl;
    cluster->computeCentroid();
    _clusters.push_back(std::move(cluster));
}

void ic::DbscanClustering::clusturingAlgorithme()
{
    int i = 0;

    while (!_pixels.empty()) {
        std::cout << "------------- " << ++i << " Clusters -------------" << std::endl;
        computeCluster();
        std::cout << "Pixels remaining: " << _pixels.size() << std::endl;
    }
    std::cout << "Number of clusters: " << _clusters.size() << std::endl;
}