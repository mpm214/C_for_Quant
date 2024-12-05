#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

// Function to sort indices based on the correlation values in descending order
std::vector<size_t> sortByCorrelation(const std::vector<double>& correlations) {
    // Create a vector of indices from 0 to correlations.size() - 1
    std::vector<size_t> indices(correlations.size());
    std::iota(indices.begin(), indices.end(), 0); // Fill indices with 0, 1, 2, ...

    // Sort indices based on the corresponding correlation values
    std::sort(indices.begin(), indices.end(), [&](size_t i, size_t j) {
        return correlations[i] > correlations[j]; // Descending order
    });

    return indices;
}

int main() {
    // Example correlation data
    std::vector<double> correlations = {0.8, -0.5, 0.3, 0.9, -0.1};

    // Sort by correlation and get the indices
    std::vector<size_t> sortedIndices = sortByCorrelation(correlations);

    // Output the sorted indices
    std::cout << "Sorted Indices:" << std::endl;
    for (size_t index : sortedIndices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    // Output the correlations in sorted order
    std::cout << "Sorted Correlations:" << std::endl;
    for (size_t index : sortedIndices) {
        std::cout << correlations[index] << " ";
    }
    std::cout << std::endl;

    return 0;
}
