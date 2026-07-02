using System;
using System.Collections.Generic;

namespace LeetCode.Problems;

/// <summary>
/// Two Sum：給定整數陣列與目標值，回傳兩數相加等於目標值之索引。
/// </summary>
public sealed class Solution
{
    /// <summary>
    /// 尋找兩數之索引，使其相加等於目標值。
    /// </summary>
    /// <param name="nums">整數陣列，長度須介於 2 到 10^4 之間，僅保證恰有一組解。</param>
    /// <param name="target">目標總和。</param>
    /// <returns>兩個索引組成的陣列，順序不限。</returns>
    /// <exception cref="ArgumentNullException">nums 為 null 時拋出。</exception>
    /// <exception cref="ArgumentException">nums 長度不足 2 個元素時拋出。</exception>
    public int[] Exec(int[] nums, int target)
    {
        ArgumentNullException.ThrowIfNull(nums);
        if (nums.Length < 2)
        {
            throw new ArgumentException("nums 長度須至少為 2。", nameof(nums));
        }

        // 建立 空對映 數值對應索引表
        var valueToIndex = new Dictionary<int, int>();

        // 迴圈 走訪 數字清單，取得 目前索引 與 目前數值
        for (var currentIndex = 0; currentIndex < nums.Length; currentIndex++)
        {
            var currentValue = nums[currentIndex];

            // 設 所需數值 為 目標值 減去 目前數值
            var complement = target - currentValue;

            // 若 所需數值 存在於 數值對應索引表 中 則
            if (valueToIndex.TryGetValue(complement, out var complementIndex))
            {
                // 回傳 由 數值對應索引表中所需數值對應之索引 與 目前索引 組成的清單
                return new[] { complementIndex, currentIndex };
            }

            // 否則 將 目前數值 與 目前索引 的對應關係 加入 數值對應索引表
            valueToIndex[currentValue] = currentIndex;
        }

        // 回傳 空清單
        return Array.Empty<int>();
    }
}
