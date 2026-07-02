"""Two Sum 問題求解模組。"""

from __future__ import annotations


class TwoSumSolver:
    """求解兩數之和問題：給定整數清單與目標值，回傳兩數相加等於目標值之索引。"""

    def exec(self, nums: list[int], target: int) -> list[int]:
        """
        尋找兩數之索引，使其相加等於目標值。

        Args:
            nums: 整數清單，長度須介於 2 到 10^4 之間，僅保證恰有一組解。
            target: 目標總和。

        Returns:
            兩個索引組成的清單，順序不限。

        Raises:
            TypeError: nums 非 list 型別時拋出。
            ValueError: nums 長度不足 2 個元素時拋出。
        """
        self._validate_nums(nums)

        # 建立 空對映 數值對應索引表
        value_to_index: dict[int, int] = {}

        # 迴圈 走訪 數字清單，取得 目前索引 與 目前數值
        for current_index, current_value in enumerate(nums):
            # 設 所需數值 為 目標值 減去 目前數值
            complement = target - current_value

            # 若 所需數值 存在於 數值對應索引表 中 則
            if complement in value_to_index:
                # 回傳 由 數值對應索引表中所需數值對應之索引 與 目前索引 組成的清單
                return [value_to_index[complement], current_index]

            # 否則 將 目前數值 與 目前索引 的對應關係 加入 數值對應索引表
            value_to_index[current_value] = current_index

        # 回傳 空清單
        return []

    @staticmethod
    def _validate_nums(nums: list[int]) -> None:
        """驗證邊界輸入：nums 型別須為 list，長度須至少為 2。"""
        if not isinstance(nums, list):
            raise TypeError("nums 須為 list 型別。")
        if len(nums) < 2:
            raise ValueError("nums 長度須至少為 2。")
