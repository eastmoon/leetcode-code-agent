using System;
using LeetCode.LongestSubstringWithoutRepeatingCharacters;

namespace LeetCode.LongestSubstringWithoutRepeatingCharacters.Tests
{
    public sealed class Program
    {
        public static void Main(string[] args)
        {
            var solution = new Solution();

            // Example 1: s = "abcabcbb" -> Output: 3 ("abc")
            RunExample(solution, "abcabcbb", 3, "Example 1");

            // Example 2: s = "bbbbb" -> Output: 1 ("b")
            RunExample(solution, "bbbbb", 1, "Example 2");

            // Example 3: s = "pwwkew" -> Output: 3 ("wke")
            RunExample(solution, "pwwkew", 3, "Example 3");
        }

        // 執行單一範例：呼叫 Exec、比對預期輸出並印出結果
        private static void RunExample(Solution solution, string input, int expectedLength, string caseName)
        {
            int actualLength = solution.Exec(input);
            bool isPassed = actualLength == expectedLength;

            Console.WriteLine($"{caseName}: {(isPassed ? "PASS" : "FAIL")} - Expected: {expectedLength} Actual: {actualLength}");
        }
    }
}
