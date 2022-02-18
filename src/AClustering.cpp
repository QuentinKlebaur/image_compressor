#include "AClustering.hpp"

ic::AClustering::AClustering(std::string const &input, std::string const &output) : _inputPath(input), _outputPath(output), _image()
{
}

void ic::AClustering::setDistanceFunction(std::function<float(Color const &cl, Color const &cr)> const &function)
{
    _distFunction = function;
}

void ic::AClustering::run()
{
    std::cout << _inputPath << std::endl;
    _image.setImage(_inputPath);
    _image.getImagePixels(_pixels);
    if (_distFunction == nullptr)
        throw std::exception("Distance compute function is not set");

    clusturingAlgorithme();
    std::cout << "Algo end" << std::endl;
    _image.updateImagePixels(_pixels);
    std::cout << _outputPath << std::endl;
    _image.writeImage(_outputPath);
}