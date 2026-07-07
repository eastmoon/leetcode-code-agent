using System;
using LeetCode.Problem0004;

namespace LeetCode.Problem0004.Tests
{
    internal static class Program
    {
        private static void Main()
        {
            var solution = new MedianOfTwoSortedArraysSolution();

            // Example 1:
            // Input: nums1 = [1,3], nums2 = [2]
            // Output: 2.00000
            // Explanation: merged array = [1,2,3] and median is 2.
            {
                var nums1 = new[] { 1, 3 };
                var nums2 = new[] { 2 };
                var result = solution.Exec(nums1, nums2);
                AssertApproximatelyEqual(result, 2.0, "Example 1");
            }

            // Example 2:
            // Input: nums1 = [1,2], nums2 = [3,4]
            // Output: 2.50000
            // Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
            {
                var nums1 = new[] { 1, 2 };
                var nums2 = new[] { 3, 4 };
                var result = solution.Exec(nums1, nums2);
                AssertApproximatelyEqual(result, 2.5, "Example 2");
            }

            Console.WriteLine("All test cases passed.");
        }

        // 浮點數比較須容許誤差，避免因浮點運算精度差異導致誤判。
        private static void AssertApproximatelyEqual(double actual, double expected, string testName, double tolerance = 1e-5)
        {
            if (Math.Abs(actual - expected) >= tolerance)
            {
                throw new InvalidOperationException($"{testName} failed: expected {expected}, actual {actual}");
            }

            Console.WriteLine($"{testName} passed: {actual}");
        }
    }
}
