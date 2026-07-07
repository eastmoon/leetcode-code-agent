# Median of Two Sorted Arrays

## 摘要

Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return the median of the two sorted arrays.

The overall run time complexity should be `O(log (m+n))`.

## 範例

**Example 1:**
```
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
```

**Example 2:**
```
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
```

## 約束

- `nums1.length == m`
- `nums2.length == n`
- `0 <= m <= 1000`
- `0 <= n <= 1000`
- `1 <= m + n <= 2000`
- `-10^6 <= nums1[i], nums2[i] <= 10^6`

## 註釋

- 中位數（Median）定義為排序後陣列的中間值；若合併後陣列長度為偶數，則為中間兩數的平均值。
- 時間複雜度須達到 `O(log (m+n))`，意味著需採用二分搜尋（Binary Search）等對數時間解法，而非直接合併兩陣列後排序之 `O(m+n)` 解法。
