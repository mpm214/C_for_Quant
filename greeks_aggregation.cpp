#include <vector>
#include <cmath>
#include <iostream>

// Structure to hold Greeks values
struct Greeks {
    double delta;
    double gamma;
    double vega;
};

// Class to manage a collection of Greeks and perform operations on them
class GreeksVector {
public:
    // Vector to store Greeks
    std::vector<Greeks> values;

    // Add a new Greeks entry
    void add(double delta, double gamma, double vega) {
        values.push_back({delta, gamma, vega});
    }

    // Calculate Greeks for a given option
    void calculateAndAdd(double spotPrice, double strikePrice, double volatility,
                         double riskFreeRate, double timeToMaturity, char optionType) {
        // Calculate d1 and d2
        double d1 = (std::log(spotPrice / strikePrice) +
                    (riskFreeRate + 0.5 * volatility * volatility) * timeToMaturity) /
                    (volatility * std::sqrt(timeToMaturity));
        double d2 = d1 - volatility * std::sqrt(timeToMaturity);

        // Standard normal probability density function (PDF)
        auto normalPDF = [](double x) {
            return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
        };

        // Standard normal cumulative distribution function (CDF)
        auto normalCDF = [](double x) {
            return 0.5 * std::erfc(-x * std::sqrt(0.5));
        };

        // Calculate Delta
        double delta = (optionType == 'c')
                       ? normalCDF(d1) // Call option
                       : normalCDF(d1) - 1; // Put option

        // Calculate Gamma
        double gamma = normalPDF(d1) / (spotPrice * volatility * std::sqrt(timeToMaturity));

        // Calculate Vega
        double vega = spotPrice * normalPDF(d1) * std::sqrt(timeToMaturity);

        // Add the calculated Greeks to the vector
        add(delta, gamma, vega);
    }

    // Aggregate all Greeks in the vector
    Greeks aggregate() const {
        double totalDelta = 0.0, totalGamma = 0.0, totalVega = 0.0;

        // Sum up all Greeks components
        for (const auto& g : values) {
            totalDelta += g.delta;
            totalGamma += g.gamma;
            totalVega += g.vega;
        }

        // Return the aggregated Greeks
        return {totalDelta, totalGamma, totalVega};
    }
};

int main() {
    // Create a GreeksVector
    GreeksVector greeksVector;

    // Parameters for options
    double spotPrice = 100.0;        // Current stock price
    double strikePrice = 105.0;      // Option strike price
    double volatility = 0.2;         // Annual volatility (20%)
    double riskFreeRate = 0.05;      // Risk-free rate (5%)
    double timeToMaturity = 1.0;     // Time to maturity (1 year)

    // Add Greeks for a call option
    greeksVector.calculateAndAdd(spotPrice, strikePrice, volatility, riskFreeRate, timeToMaturity, 'c');

    // Add Greeks for a put option
    greeksVector.calculateAndAdd(spotPrice, strikePrice, volatility, riskFreeRate, timeToMaturity, 'p');

    // Aggregate the Greeks
    Greeks aggregatedGreeks = greeksVector.aggregate();

    // Print the aggregated Greeks
    std::cout << "Aggregated Greeks:" << std::endl;
    std::cout << "Delta: " << aggregatedGreeks.delta << std::endl;
    std::cout << "Gamma: " << aggregatedGreeks.gamma << std::endl;
    std::cout << "Vega: " << aggregatedGreeks.vega << std::endl;

    return 0;
}
