#include <cassert>
#include <iostream>

#include "main.cpp"

// 驗證 LeetCode 第 3 題範例，確認 LongestSubstringFinder::exec 之正確性
int main() {
    using leetcode::LongestSubstringFinder;

    const LongestSubstringFinder solver;

    // Example 1: s = "abcabcbb" -> 3 ("abc")
    assert(solver.exec("abcabcbb") == 3);

    // Example 2: s = "bbbbb" -> 1 ("b")
    assert(solver.exec("bbbbb") == 1);

    // Example 3: s = "pwwkew" -> 3 ("wke")
    assert(solver.exec("pwwkew") == 3);

    std::cout << "All tests passed." << std::endl;
    return 0;
}
