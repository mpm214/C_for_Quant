// Covariance Matrix 
#include <vector>
#include <cstddef> // For size_t

// Function to compute the covariance matrix
std::vector<std::vector<double>> covarianceMatrix(const std::vector<std::vector<double>>& data) {
    size_t n = data.size();            // Number of data points
    size_t m = data[0].size();         // Number of variables (columns)
    
    // Initialize covariance matrix with zeros
    std::vector<std::vector<double>> cov(m, std::vector<double>(m, 0.0));
    
    // Calculate the covariance for each pair of variables
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            double cov_ij = 0.0;

            // Accumulate the product of data points for variables i and j
            for (size_t k = 0; k < n; ++k) {
                cov_ij += data[k][i] * data[k][j];
            }

            // Normalize by (n - 1) and fill in symmetric entries
            cov[i][j] = cov[j][i] = cov_ij / (n - 1);
        }
    }
    
    return cov;
}
