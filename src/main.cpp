#include "Color.hpp"
#include "KMeansClustering.hpp"
#include "DbscanClustering.hpp"
#include "AClustering.hpp"
#include "Distance.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <vector>
#include <chrono>
#include <map>
#include <filesystem>

std::map<std::string, std::function<std::unique_ptr<ic::AClustering>(std::string, std::string, float)>> algorithmChooser{
    {"kmeans", [](std::string input, std::string output, float value){return std::make_unique<ic::KMeansClustering>(input, output, (int)value);}},
    {"dbscan", [](std::string input, std::string output, float value){return std::make_unique<ic::DbscanClustering>(input, output, value);}}
};

std::map<std::string, std::function<float(ic::Color const &, ic::Color const &)>> distanceChooser{
    {"euclidean", &ic::euclideanDistance},
    {"manhattan", &ic::manhattanDistance}
};

bool helper(int ac, char **av)
{
    if (ac != 6) {
        std::cout << std::endl << "You must launch this program as described below" << std::endl << std::endl;
        std::cout << "\tImageCompressor.exe input output algorithm distance value" << std::endl << std::endl;
        std::cout << "\t-input\t\tis the path of the input image" << std::endl;
        std::cout << "\t-output\t\tis the path of the output folder" << std::endl;
        std::cout << "\t-algorithm\tis the name of the choosen algorithm" << std::endl;
        std::cout << "\t-distance\tis the name of the choosen distance formula" << std::endl;
        std::cout << "\t-value\t\tis the value used to launch the algorithm. It can be 'k' for kmeans or the epsilon for dbscan" << std::endl;
        return true;
    }
    return false;
}

std::string fileNameIndexer(std::string const &baseName, std::string const &extension, int index)
{
    if (index == 0)
        return baseName + extension;
    return baseName + " (" + std::to_string(index) + ')' + extension;
}

std::string computeOutputFileName(std::string const &input, std::string const &outputFolder, std::string const &algo, std::string const &distance, float value)
{
    char folderDelim = '\\';
    if (outputFolder.find(folderDelim) == std::string::npos)
        folderDelim = '/';
    char fileDelim = '\\';
    if (input.find(fileDelim) == std::string::npos)
        fileDelim = '/';
    std::string fileName = input;
    if (fileName.find(fileDelim) != std::string::npos)
        fileName = fileName.substr(fileName.find_last_of(fileDelim) + 1);
    std::string baseOutput = outputFolder;
    std::string extension = "." + fileName.substr(fileName.find_last_of('.') + 1);
    std::string fileBaseName = fileName.substr(0, fileName.find_last_of('.'));
    std::string valueStr = std::to_string((int)value);
    int decimal = (int)((value - (int)value) * 1000);

    if (decimal != 0)
        valueStr += '.' +  std::to_string(decimal);
    if (outputFolder[outputFolder.size() - 1] != folderDelim)
        baseOutput += folderDelim;

    std::string output = baseOutput + fileBaseName + '_' + algo + '_' + distance + '_' + valueStr;
    int index = 0;

    while (std::filesystem::exists(fileNameIndexer(output, extension, index)))
        ++index;
    return fileNameIndexer(output, extension, index);
}

int myMain(int ac, char **av)
{
    if (helper(ac, av))
        return 0;
    auto start = std::chrono::steady_clock::now();
    std::vector<std::unique_ptr<ic::AClustering>> v;
    std::string input{av[1]};
    std::string outputFolder{av[2]};
    std::string algoName{av[3]};
    std::string distanceName{av[4]};
    std::string outputFile;
    float value;

    if (!std::filesystem::is_directory(outputFolder)) {
        std::cout << "You should enter a valid output folder" << std::endl;
        return 84;
    }
    try {
        value = std::atof(av[5]);
        if (value <= 0)
            throw std::exception();
    } catch (std::exception) {
        std::cout << "You should enter a valid number" << std::endl;
        return 84;
    }
    outputFile = computeOutputFileName(input, outputFolder, algoName, distanceName, value);
    if (algorithmChooser.find(algoName) == algorithmChooser.end()) {
        std::cout << "You should enter a valid algorithm:" << std::endl;
        for (auto i = algorithmChooser.begin(); i != algorithmChooser.end(); ++i)
            std::cout << "\t-" << i->first << std::endl;
        return 84;
    }
    if (distanceChooser.find(distanceName) == distanceChooser.end()) {
        std::cout << "You should enter a valid distance type:" << std::endl;
        for (auto i = distanceChooser.begin(); i != distanceChooser.end(); ++i)
            std::cout << "\t-" << i->first << std::endl;
        return 84;
    }
    try {
        v.push_back(algorithmChooser[algoName](input, outputFile, value));
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->setDistanceFunction(distanceChooser[distanceName]);
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->run();
    auto end = std::chrono::steady_clock::now();

    std::cout << "Duration: " << ((std::chrono::duration<double>)(end - start)).count() << std::endl;
}

int main(int ac, char **av)
{
    int ret = myMain(ac, av);

    system("pause");
    return ret;
}