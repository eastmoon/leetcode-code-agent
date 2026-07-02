#include <cassert>
#include <vector>

#include "main.cpp"

namespace {

// 驗證 Example 1：nums = [2,7,11,15], target = 9 -> [0,1]
void testExampleOne() {
    const Solution solution;
    const std::vector<int> nums = {2, 7, 11, 15};
    const std::vector<int> result = solution.exec(nums, 9);
    assert(result == std::vector<int>({0, 1}));
}

// 驗證 Example 2：nums = [3,2,4], target = 6 -> [1,2]
void testExampleTwo() {
    const Solution solution;
    const std::vector<int> nums = {3, 2, 4};
    const std::vector<int> result = solution.exec(nums, 6);
    assert(result == std::vector<int>({1, 2}));
}

// 驗證 Example 3：nums = [3,3], target = 6 -> [0,1]
void testExampleThree() {
    const Solution solution;
    const std::vector<int> nums = {3, 3};
    const std::vector<int> result = solution.exec(nums, 6);
    assert(result == std::vector<int>({0, 1}));
}

}  // namespace

int main() {
    testExampleOne();
    testExampleTwo();
    testExampleThree();
    return 0;
}
