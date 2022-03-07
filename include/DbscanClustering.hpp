#include "AClustering.hpp"

namespace ic {
    class DbscanClustering : public AClustering {
        public:

            DbscanClustering(std::string const &input, std::string const &output, float epsilon);

        private:
            void clusturingAlgorithme() override;
            void addNearPixels(std::unique_ptr<Pixel> const &pixel, std::list<std::unique_ptr<Pixel>> &list, std::unique_ptr<Cluster> &cluster, std::vector<Color> &colorContained);
            void computeCluster();

            const float _epsilon;
    };
}