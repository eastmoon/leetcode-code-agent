using System;
using System.Linq;

namespace LeetCode.Problems;

/// <summary>
/// Two Sum 測試程式，驗證 Solution.Exec 是否符合程式設計需求之範例。
/// </summary>
public static class Program
{
    public static void Main()
    {
        // 需求範例 1：nums = [2,7,11,15], target = 9 -> [0,1]
        RunExample(new[] { 2, 7, 11, 15 }, 9, new[] { 0, 1 });

        // 需求範例 2：nums = [3,2,4], target = 6 -> [1,2]
        RunExample(new[] { 3, 2, 4 }, 6, new[] { 1, 2 });

        // 需求範例 3：nums = [3,3], target = 6 -> [0,1]
        RunExample(new[] { 3, 3 }, 6, new[] { 0, 1 });
    }

    private static void RunExample(int[] nums, int target, int[] expected)
    {
        var solution = new Solution();
        var actual = solution.Exec(nums, target);

        if (!actual.SequenceEqual(expected))
        {
            throw new InvalidOperationException(
                $"預期 [{string.Join(", ", expected)}]，實際 [{string.Join(", ", actual)}]。");
        }
    }
}
