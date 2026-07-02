"""Longest Substring Without Repeating Characters 問題求解模組。"""

from __future__ import annotations


class LongestSubstringSolver:
    """求解最長不重複字元子字串問題：給定字串，回傳最長不含重複字元之子字串長度。"""

    def exec(self, s: str) -> int:
        """
        尋找不重複字元之最長子字串長度。

        Args:
            s: 輸入字串，長度介於 0 到 5*10^4，由英文字母、數字、符號與空白組成。

        Returns:
            最長不重複字元子字串之長度；輸入為空字串時回傳 0。

        Raises:
            TypeError: s 非 str 型別時拋出。
        """
        self._validate_input(s)

        # 若 輸入字串 為空 則 回傳 0
        if len(s) == 0:
            return 0

        # 建立 空對映 字元對應最近索引表
        char_to_last_index: dict[str, int] = {}
        # 設 最長長度 為 0
        longest_length = 0
        # 設 視窗起始索引 為 0
        window_start_index = 0

        # 迴圈 走訪 輸入字串，取得 目前索引 與 目前字元
        for current_index, current_char in enumerate(s):
            # 若 目前字元 存在於 字元對應最近索引表 中 且 字元對應最近索引表中目前字元對應之索引 大於等於 視窗起始索引 則
            if (
                current_char in char_to_last_index
                and char_to_last_index[current_char] >= window_start_index
            ):
                # 設 視窗起始索引 為 字元對應最近索引表中目前字元對應之索引 加 1
                window_start_index = char_to_last_index[current_char] + 1

            # 將 目前字元 與 目前索引 的對應關係 加入 字元對應最近索引表
            char_to_last_index[current_char] = current_index

            # 設 目前視窗長度 為 目前索引 減去 視窗起始索引 加 1
            current_window_length = current_index - window_start_index + 1

            # 若 目前視窗長度 大於 最長長度 則 設 最長長度 為 目前視窗長度
            if current_window_length > longest_length:
                longest_length = current_window_length

        # 回傳 最長長度
        return longest_length

    @staticmethod
    def _validate_input(s: str) -> None:
        """驗證邊界輸入：s 型別須為 str。"""
        if not isinstance(s, str):
            raise TypeError("s 須為 str 型別。")
