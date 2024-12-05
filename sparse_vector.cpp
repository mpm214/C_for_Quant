#include <map>
#include <cstddef> // For size_t
#include <iostream>

class SparseVector {
public:
    // Map to store non-zero values, with the index as the key
    std::map<size_t, double> values;

    // Set a value at a specific index
    void set(size_t index, double value) {
        if (value != 0.0) {
            values[index] = value;
        } else {
            values.erase(index); // Remove zero values to maintain sparsity
        }
    }

    // Get the value at a specific index, or 0.0 if not present
    double get(size_t index) const {
        auto it = values.find(index);
        return it != values.end() ? it->second : 0.0;
    }

    // Add another SparseVector to this one and return the result
    SparseVector add(const SparseVector& other) const {
        SparseVector result;

        // Add all elements from this SparseVector
        for (const auto& [index, value] : values) {
            result.set(index, value + other.get(index));
        }

        // Add elements from the other SparseVector that are not in this one
        for (const auto& [index, value] : other.values) {
            if (values.find(index) == values.end()) {
                result.set(index, value);
            }
        }

        return result;
    }
};

int main() {
    SparseVector vec1, vec2;

    // Set some values in vec1
    vec1.set(0, 1.5);
    vec1.set(3, 2.5);

    // Set some values in vec2
    vec2.set(3, 1.5);
    vec2.set(5, 3.0);

    // Add the vectors
    SparseVector result = vec1.add(vec2);

    // Output the result
    std::cout << "Result SparseVector:" << std::endl;
    for (const auto& [index, value] : result.values) {
        std::cout << "Index " << index << ": " << value << std::endl;
    }

    return 0;
}
