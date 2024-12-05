#include <vector>
#include <cmath>
#include <execution>
#include <random>
#include <iostream>

// Function to simulate asset prices in parallel
void parallelSimulateAssetPrices(std::vector<double>& assetPrices, 
                                 double S0, double r, double sigma, 
                                 double T, size_t N) {
    // Generate random numbers
    std::vector<double> randomNumbers(N, 0.0);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);

    // Fill randomNumbers with normally distributed random values
    for (size_t i = 0; i < N; ++i) {
        randomNumbers[i] = dist(gen);
    }

    // Use parallel transform to compute asset prices
    std::transform(std::execution::par, randomNumbers.begin(), randomNumbers.end(),
                   assetPrices.begin(),
                   [=](double z) {
                       return S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * z);
                   });
}

int main() {
    // Parameters
    double S0 = 100.0;   // Initial asset price
    double r = 0.05;     // Risk-free rate
    double sigma = 0.2;  // Volatility
    double T = 1.0;      // Time to maturity (in years)
    size_t N = 100000;   // Number of simulations

    // Vector to store simulated asset prices
    std::vector<double> assetPrices(N);

    // Simulate asset prices
    parallelSimulateAssetPrices(assetPrices, S0, r, sigma, T, N);

    // Output a few simulated prices
    for (size_t i = 0; i < 10; ++i) {
        std::cout << "Asset Price " << i + 1 << ": " << assetPrices[i] << std::endl;
    }

    return 0;
}
