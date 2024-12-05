// Normalize a vector in - place
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>

void normalizeVector(std::vector<double>& vec) {
    double norm = std::sqrt(std::accumulate(vec.begin(), vec.end(), 0.0,
        [](double sum, double val) { return sum + val * val; }));
    for (double& val : vec) val /= norm;
}

int main() {
    // Example vector
    std::vector<double> vec = {3.0, 4.0, 5.0};

    // Normalize the vector
    normalizeVector(vec);

    return 0;
}
