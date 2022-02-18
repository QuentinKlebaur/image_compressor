#include "KMeansClustering.hpp"
#include "AClustering.hpp"
#include "Distance.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <vector>

int main(int ac, char **av) {

    std::vector<std::unique_ptr<ic::AClustering>> v;


    std::cout << "Hello" << std::endl;
    v.push_back(std::make_unique<ic::KMeansClustering>("tmp.png", "computed.png", 32));
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->setDistanceFunction(&ic::euclideanDistance);
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->run();

    system("pause");
    return 0;
}