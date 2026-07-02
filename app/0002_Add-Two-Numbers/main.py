"""Add Two Numbers 問題求解模組。"""

from __future__ import annotations

from types import SimpleNamespace
from typing import Optional


class AddTwoNumbersSolver:
    """求解兩鏈結串列相加問題：給定兩個以反序儲存非負整數之鏈結串列，回傳其和之反序鏈結串列。"""

    def exec(
        self, l1: Optional[SimpleNamespace], l2: Optional[SimpleNamespace]
    ) -> Optional[SimpleNamespace]:
        """
        相加兩鏈結串列所表示之數字。

        Args:
            l1: 第一鏈結串列表頭，節點須具備 val、next 屬性，個位數在表頭，節點數介於 1 到 100。
            l2: 第二鏈結串列表頭，節點須具備 val、next 屬性，個位數在表頭，節點數介於 1 到 100。

        Returns:
            相加結果之反序鏈結串列表頭。

        Raises:
            ValueError: l1 或 l2 為 None 時拋出。
        """
        self._validate_lists(l1, l2)

        # 建立 虛擬表頭節點
        dummy_head = self._create_node(0)
        # 設 目前結果節點 為 虛擬表頭節點
        current_result_node = dummy_head
        # 設 進位值 為 0
        carry = 0
        # 設 目前第一節點 為 第一鏈結串列表頭
        current_first_node = l1
        # 設 目前第二節點 為 第二鏈結串列表頭
        current_second_node = l2

        # 迴圈 當 目前第一節點 存在 或 目前第二節點 存在 或 進位值 不為 0
        while current_first_node is not None or current_second_node is not None or carry != 0:
            # 若 目前第一節點 存在 則 設 第一數值 為其數值 否則 設 第一數值 為 0
            first_value = current_first_node.val if current_first_node is not None else 0
            # 若 目前第二節點 存在 則 設 第二數值 為其數值 否則 設 第二數值 為 0
            second_value = current_second_node.val if current_second_node is not None else 0

            # 設 位數總和 為 第一數值 加上 第二數值 加上 進位值
            digit_sum = first_value + second_value + carry
            # 設 進位值 為 位數總和 整除 10
            carry = digit_sum // 10
            # 設 目前位數 為 位數總和 除以 10 取餘數
            current_digit = digit_sum % 10

            # 建立 新節點，數值為 目前位數；將 新節點 接續於 目前結果節點 之後
            current_result_node.next = self._create_node(current_digit)
            # 設 目前結果節點 為 新節點
            current_result_node = current_result_node.next

            # 若 目前第一節點 存在 則 設 目前第一節點 為 目前第一節點的下一節點
            if current_first_node is not None:
                current_first_node = current_first_node.next
            # 若 目前第二節點 存在 則 設 目前第二節點 為 目前第二節點的下一節點
            if current_second_node is not None:
                current_second_node = current_second_node.next

        # 回傳 虛擬表頭節點的下一節點
        return dummy_head.next

    @staticmethod
    def _validate_lists(
        l1: Optional[SimpleNamespace], l2: Optional[SimpleNamespace]
    ) -> None:
        """驗證邊界輸入：l1 與 l2 依約束保證至少包含一個節點，不得為 None。"""
        if l1 is None or l2 is None:
            raise ValueError("l1 與 l2 均須為非空鏈結串列。")

    @staticmethod
    def _create_node(val: int) -> SimpleNamespace:
        """建立鏈結串列節點，節點數值範圍為 0 到 9。"""
        return SimpleNamespace(val=val, next=None)
