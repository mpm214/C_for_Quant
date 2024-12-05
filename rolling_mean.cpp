#include <vector>
#include <deque>
#include <numeric>
#include <iostream>

// Function to compute rolling mean using a sliding window
std::vector<double> rollingMean(const std::vector<double>& data, size_t windowSize) {
    std::deque<double> window;        // Sliding window to hold the current window elements
    std::vector<double> result;       // Result vector to store rolling means
    double sum = 0.0;                 // Sum of elements in the current window

    for (size_t i = 0; i < data.size(); ++i) {
        // Add the next element to the window
        window.push_back(data[i]);
        sum += data[i];

        // If the window size exceeds the specified size, remove the oldest element
        if (window.size() > windowSize) {
            sum -= window.front();
            window.pop_front();
        }

        // Calculate and store the rolling mean when the window is full
        if (window.size() == windowSize) {
            result.push_back(sum / windowSize);
        }
    }

    return result;
}

int main() {
    // Example data
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    size_t windowSize = 3;

    // Compute the rolling mean
    std::vector<double> result = rollingMean(data, windowSize);

    // Print the result
    std::cout << "Rolling Mean:" << std::endl;
    for (double value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
