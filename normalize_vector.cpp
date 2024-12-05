// Normalize a vector in - place
#include <vector>
#include <numeric>
#include <cmath>

void normalizeVector(std::vector<double>& vec) {
    double norm = std::sqrt(std::accumulate(vec.begin(), vec.end(), 0.0,
        [](double sum, double val) { return sum + val * val; }));
    for (double& val : vec) val /= norm;
}