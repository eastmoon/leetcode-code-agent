using System;
using System.Collections.Generic;

namespace LeetCode.Problem0004
{
    /// <summary>
    /// 摘要：給定兩個已排序陣列 nums1 與 nums2，回傳合併後陣列的中位數，
    /// 整體時間複雜度須達到 O(log (m+n))。
    /// </summary>
    public sealed class MedianOfTwoSortedArraysSolution
    {
        /// <summary>
        /// Exec 對應虛擬碼「尋找兩個排序陣列的中位數」函式，為本類別對外的唯一入口。
        /// </summary>
        /// <param name="nums1">已排序整數陣列，對應約束 0 &lt;= m &lt;= 1000。</param>
        /// <param name="nums2">已排序整數陣列，對應約束 0 &lt;= n &lt;= 1000。</param>
        /// <returns>合併後陣列之中位數。</returns>
        /// <exception cref="ArgumentNullException">nums1 或 nums2 為 null 時拋出。</exception>
        /// <exception cref="ArgumentException">nums1 與 nums2 之總長度小於 1 時拋出。</exception>
        public double Exec(IReadOnlyList<int> nums1, IReadOnlyList<int> nums2)
        {
            ValidateBoundaryInput(nums1, nums2);

            // 虛擬碼：設定 短陣列 為 陣列一；設定 長陣列 為 陣列二
            var shortArray = nums1;
            var longArray = nums2;

            // 虛擬碼：若 取得長度(短陣列) 大於 取得長度(長陣列) 則 交換(短陣列, 長陣列)
            if (shortArray.Count > longArray.Count)
            {
                (shortArray, longArray) = (longArray, shortArray);
            }

            return FindMedianByPartition(shortArray, longArray);
        }

        // 邊界輸入驗證：nums1 與 nums2 不得為 null，且總長度須至少為 1
        // （對應約束 1 &lt;= m + n &lt;= 2000）。
        private static void ValidateBoundaryInput(IReadOnlyList<int> nums1, IReadOnlyList<int> nums2)
        {
            ArgumentNullException.ThrowIfNull(nums1);
            ArgumentNullException.ThrowIfNull(nums2);

            var totalLength = nums1.Count + nums2.Count;
            if (totalLength < 1)
            {
                throw new ArgumentException("nums1 與 nums2 之總長度須至少為 1。");
            }
        }

        // 虛擬碼主體：以二分搜尋於較短陣列上尋找正確分割位置，對應
        // 「迴圈 當 搜尋下界 小於等於 搜尋上界 時」至「結束迴圈」之邏輯。
        // 前提：nums1 與 nums2 須為已排序陣列（依摘要之描述）；驗證排序狀態需 O(m+n)，
        //       將違反題目要求之 O(log (m+n)) 複雜度，故不於執行期檢查排序狀態。
        private static double FindMedianByPartition(IReadOnlyList<int> shortArray, IReadOnlyList<int> longArray)
        {
            var shortLength = shortArray.Count;
            var longLength = longArray.Count;
            var totalLength = shortLength + longLength;
            // 虛擬碼：設定 左半部目標數量 為 向下取整((總長度 加上 1) 除以 2)
            var leftHalfTargetCount = (totalLength + 1) / 2;

            var searchLowerBound = 0;
            var searchUpperBound = shortLength;

            while (searchLowerBound <= searchUpperBound)
            {
                var shortPartition = (searchLowerBound + searchUpperBound) / 2;
                var longPartition = leftHalfTargetCount - shortPartition;

                // 虛擬碼：短陣列左側最大值 / 短陣列右側最小值，分割位置為 0 或等於陣列長度時
                // 以 int.MinValue / int.MaxValue 代表不存在之邊界元素。
                var shortLeftMax = shortPartition == 0
                    ? int.MinValue
                    : shortArray[shortPartition - 1];
                var shortRightMin = shortPartition == shortLength
                    ? int.MaxValue
                    : shortArray[shortPartition];

                var longLeftMax = longPartition == 0
                    ? int.MinValue
                    : longArray[longPartition - 1];
                var longRightMin = longPartition == longLength
                    ? int.MaxValue
                    : longArray[longPartition];

                // 虛擬碼：若 短陣列左側最大值 小於等於 長陣列右側最小值
                //          且 長陣列左側最大值 小於等於 短陣列右側最小值 則
                if (shortLeftMax <= longRightMin && longLeftMax <= shortRightMin)
                {
                    var leftHalfMax = Math.Max(shortLeftMax, longLeftMax);

                    if (totalLength % 2 == 0)
                    {
                        var rightHalfMin = Math.Min(shortRightMin, longRightMin);
                        return (leftHalfMax + (double)rightHalfMin) / 2.0;
                    }

                    return leftHalfMax;
                }

                // 虛擬碼：否則 若 短陣列左側最大值 大於 長陣列右側最小值 則 搜尋上界 為 短陣列分割位置 減 1
                if (shortLeftMax > longRightMin)
                {
                    searchUpperBound = shortPartition - 1;
                }
                else
                {
                    // 虛擬碼：否則 搜尋下界 為 短陣列分割位置 加 1
                    searchLowerBound = shortPartition + 1;
                }
            }

            // 前提不成立（輸入陣列未排序）時之防禦性錯誤回報；若前提成立，迴圈必於上方回傳結果。
            throw new ArgumentException("nums1 與 nums2 須為已排序陣列。");
        }
    }
}
