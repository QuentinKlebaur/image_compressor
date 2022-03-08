#include "AClustering.hpp"

namespace ic {
    class KMeansClustering : public AClustering {
        public:

            KMeansClustering(std::string const &input, std::string const &output, unsigned int k);

        private:
            void clusturingAlgorithme() override;
            void computeClusters();
            void resetClusters();
            void computeCentroids();
            bool computeEnd();

            unsigned int _k;
    };
}