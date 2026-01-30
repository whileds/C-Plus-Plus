/**
 * @file
 * @brief Negative-aware digit-based sorting algorithm.
 * @details
 * This algorithm separates negative and non-negative numbers.
 * Negative numbers are sorted using Shell Sort, while non-negative
 * numbers are grouped by digit count and sorted. Finally, both
 * parts are merged to produce a fully sorted array.
 */

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

namespace sorting {

/**
 * @brief Counts number of digits in a number.
 */
int count_digits(int x) {
    if (x == 0) {
        return 1;
    }
    x = std::abs(x);
    int count = 0;
    while (x > 0) {
        x /= 10;
        count++;
    }
    return count;
}

/**
 * @brief Shell sort implementation for integers.
 */
void shell_sort(std::vector<int> &arr) {
    int n = static_cast<int>(arr.size());
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

/**
 * @brief Sorts array using negative-aware digit sort.
 */
std::vector<int> negative_aware_digit_sort(const std::vector<int> &arr) {
    std::vector<int> negatives;
    std::vector<int> positives;

    for (int x : arr) {
        if (x < 0) {
            negatives.push_back(x);
        } else {
            positives.push_back(x);
        }
    }

    if (!negatives.empty()) {
        shell_sort(negatives);
    }

    std::vector<int> result;
    for (int x : negatives) {
        result.push_back(x);
    }

    for (int digits = 1; digits <= 10; digits++) {
        std::vector<int> bucket;
        for (int x : positives) {
            if (count_digits(x) == digits) {
                bucket.push_back(x);
            }
        }
        if (!bucket.empty()) {
            shell_sort(bucket);
            for (int x : bucket) {
                result.push_back(x);
            }
        }
    }

    return result;
}

}  // namespace sorting

/**
 * @brief Self-test implementations.
 */
static void tests() {
    std::vector<int> arr = {34, -5, 12, -99, 0, 7, 100, -1};
    std::vector<int> sorted =
        sorting::negative_aware_digit_sort(arr);

    assert(std::is_sorted(sorted.begin(), sorted.end()));
    std::cout << "All tests passed\n";
}

/**
 * @brief Main function.
 */
int main() {
    tests();
    return 0;
}
