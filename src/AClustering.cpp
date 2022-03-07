#include "AClustering.hpp"

ic::AClustering::AClustering(std::string const &input, std::string const &output) : _inputPath(input), _outputPath(output), _image()
{
    _image.setImage(_inputPath);
}

void ic::AClustering::setDistanceFunction(std::function<float(Color const &cl, Color const &cr)> const &function)
{
    _distFunction = function;
}

void ic::AClustering::run()
{
    _image.getImagePixels(_pixels);
    if (_distFunction == nullptr)
        throw std::exception("Distance compute function is not set");

    clusturingAlgorithme();
    _image.updateImagePixels(_clusters);
    _image.writeImage(_outputPath);
}