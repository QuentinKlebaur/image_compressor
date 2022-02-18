#include "Color.hpp"
#include "Pixel.hpp"
#include "Cluster.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>

int main(int ac, char **av) {
    ic::Color c{(unsigned char)10, (unsigned char)255, (unsigned char)256};
    std::string input;

//    std::cout << "Hello world" << std::endl;
//    std::cout << c << std::endl;
    std::srand(std::time(nullptr));


    std::list<std::unique_ptr<ic::Pixel>> list;
    ic::Cluster cluster;

    list.push_back(std::make_unique<ic::Pixel>(1, 1, 1, 1, 1));
    list.push_back(std::make_unique<ic::Pixel>(2, 2, 2, 2, 2));

    system("pause");

    return 0;
}