#include "main.cpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

namespace {

// 浮點數比較須容許誤差，避免因浮點運算精度差異導致誤判。
bool is_approximately_equal(double lhs, double rhs, double tolerance = 1e-5) {
    return std::abs(lhs - rhs) < tolerance;
}

}  // namespace

int main() {
    const MedianOfTwoSortedArrays solution;

    // Example 1:
    // Input: nums1 = [1,3], nums2 = [2]
    // Output: 2.00000
    // Explanation: merged array = [1,2,3] and median is 2.
    {
        const std::vector<int> nums1 = {1, 3};
        const std::vector<int> nums2 = {2};
        const double result = solution.exec(nums1, nums2);
        assert(is_approximately_equal(result, 2.0));
        std::cout << "Example 1 passed: " << result << std::endl;
    }

    // Example 2:
    // Input: nums1 = [1,2], nums2 = [3,4]
    // Output: 2.50000
    // Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
    {
        const std::vector<int> nums1 = {1, 2};
        const std::vector<int> nums2 = {3, 4};
        const double result = solution.exec(nums1, nums2);
        assert(is_approximately_equal(result, 2.5));
        std::cout << "Example 2 passed: " << result << std::endl;
    }

    std::cout << "All test cases passed." << std::endl;
    return 0;
}
