"""摘要：給定兩個已排序陣列 nums1 與 nums2，回傳合併後陣列的中位數，
整體時間複雜度須達到 O(log (m+n))。
"""

from __future__ import annotations


class MedianOfTwoSortedArrays:
    """尋找兩個已排序陣列之中位數。"""

    def exec(self, nums1: list[int], nums2: list[int]) -> float:
        """對應虛擬碼「尋找兩個排序陣列的中位數」函式，為本類別對外的唯一入口。

        Args:
            nums1: 已排序整數清單，對應約束 0 <= m <= 1000。
            nums2: 已排序整數清單，對應約束 0 <= n <= 1000。

        Returns:
            合併後陣列之中位數。

        Raises:
            ValueError: 當 nums1 與 nums2 之總長度小於 1 時拋出。
        """
        self._validate_boundary_input(nums1, nums2)

        # 虛擬碼：設定 短陣列 為 陣列一；設定 長陣列 為 陣列二
        short_array, long_array = nums1, nums2

        # 虛擬碼：若 取得長度(短陣列) 大於 取得長度(長陣列) 則 交換(短陣列, 長陣列)
        if len(short_array) > len(long_array):
            short_array, long_array = long_array, short_array

        return self._find_median_by_partition(short_array, long_array)

    @staticmethod
    def _validate_boundary_input(nums1: list[int], nums2: list[int]) -> None:
        """邊界輸入驗證：nums1 與 nums2 之總長度須至少為 1（對應約束 1 <= m + n <= 2000）。"""
        total_length = len(nums1) + len(nums2)
        if total_length < 1:
            raise ValueError("nums1 與 nums2 之總長度須至少為 1。")

    @staticmethod
    def _find_median_by_partition(short_array: list[int], long_array: list[int]) -> float:
        """虛擬碼主體：以二分搜尋於較短陣列上尋找正確分割位置，對應
        「迴圈 當 搜尋下界 小於等於 搜尋上界 時」至「結束迴圈」之邏輯。

        前提：short_array 與 long_array 須為已排序陣列（依摘要之描述）；驗證排序狀態
        需 O(m+n)，將違反題目要求之 O(log (m+n)) 複雜度，故不於執行期檢查排序狀態。
        """
        short_length = len(short_array)
        long_length = len(long_array)
        total_length = short_length + long_length
        # 虛擬碼：設定 左半部目標數量 為 向下取整((總長度 加上 1) 除以 2)
        left_half_target_count = (total_length + 1) // 2

        search_lower_bound = 0
        search_upper_bound = short_length

        while search_lower_bound <= search_upper_bound:
            short_partition = (search_lower_bound + search_upper_bound) // 2
            long_partition = left_half_target_count - short_partition

            # 虛擬碼：短陣列左側最大值 / 短陣列右側最小值，分割位置為 0 或等於陣列長度時
            # 以正負無限大代表不存在之邊界元素。
            short_left_max = (
                float("-inf") if short_partition == 0 else short_array[short_partition - 1]
            )
            short_right_min = (
                float("inf") if short_partition == short_length else short_array[short_partition]
            )

            long_left_max = (
                float("-inf") if long_partition == 0 else long_array[long_partition - 1]
            )
            long_right_min = (
                float("inf") if long_partition == long_length else long_array[long_partition]
            )

            # 虛擬碼：若 短陣列左側最大值 小於等於 長陣列右側最小值
            #          且 長陣列左側最大值 小於等於 短陣列右側最小值 則
            if short_left_max <= long_right_min and long_left_max <= short_right_min:
                left_half_max = max(short_left_max, long_left_max)

                if total_length % 2 == 0:
                    right_half_min = min(short_right_min, long_right_min)
                    return (left_half_max + right_half_min) / 2

                return float(left_half_max)

            # 虛擬碼：否則 若 短陣列左側最大值 大於 長陣列右側最小值 則 搜尋上界 為 短陣列分割位置 減 1
            if short_left_max > long_right_min:
                search_upper_bound = short_partition - 1
            else:
                # 虛擬碼：否則 搜尋下界 為 短陣列分割位置 加 1
                search_lower_bound = short_partition + 1

        # 前提不成立（輸入陣列未排序）時之防禦性錯誤回報；若前提成立，迴圈必於上方回傳結果。
        raise ValueError("nums1 與 nums2 須為已排序陣列。")
