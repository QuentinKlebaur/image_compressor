#include "AClustering.hpp"

namespace ic {
    class KMeansClustering : public AClustering {
        public:

            KMeansClustering(std::string const &input, std::string const &output, unsigned int k);

        private:
            void clusturingAlgorithme();
            void computeClusters();
            void resetClusters();
            void computeCentroids();
            bool computeEnd();

            Color _lastMeanColor;
            const unsigned int _k;
    };
}