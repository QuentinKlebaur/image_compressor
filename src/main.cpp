#include "KMeansClustering.hpp"
#include "AClustering.hpp"
#include "Distance.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <vector>
#include <chrono>

int main(int ac, char **av) {
    auto start = std::chrono::steady_clock::now();
    std::vector<std::unique_ptr<ic::AClustering>> v;


    std::cout << "Hello" << std::endl;
    v.push_back(std::make_unique<ic::KMeansClustering>("tmp.png", "computed.png", 32));
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->setDistanceFunction(&ic::euclideanDistance);
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->run();
    auto end = std::chrono::steady_clock::now();

    std::cout << "elapsed time: " << ((std::chrono::duration<double>)(end - start)).count() << std::endl;

    system("pause");
    return 0;
}