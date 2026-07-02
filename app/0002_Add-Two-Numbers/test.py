"""Add Two Numbers 測試模組。"""

from __future__ import annotations

from types import SimpleNamespace
from typing import Optional

from main import AddTwoNumbersSolver


def _build_list(values: list[int]) -> Optional[SimpleNamespace]:
    """建立鏈結串列（測試輔助函式）。"""
    dummy_head = SimpleNamespace(val=0, next=None)
    current_node = dummy_head
    for value in values:
        current_node.next = SimpleNamespace(val=value, next=None)
        current_node = current_node.next
    return dummy_head.next


def _list_to_values(head: Optional[SimpleNamespace]) -> list[int]:
    """將鏈結串列轉換為數字清單（測試輔助函式）。"""
    values: list[int] = []
    current_node = head
    while current_node is not None:
        values.append(current_node.val)
        current_node = current_node.next
    return values


def test_example_one() -> None:
    """驗證 Example 1：l1 = [2,4,3], l2 = [5,6,4] -> [7,0,8]。"""
    solver = AddTwoNumbersSolver()
    result = solver.exec(_build_list([2, 4, 3]), _build_list([5, 6, 4]))
    assert _list_to_values(result) == [7, 0, 8], f"Example 1 失敗: {_list_to_values(result)}"


def test_example_two() -> None:
    """驗證 Example 2：l1 = [0], l2 = [0] -> [0]。"""
    solver = AddTwoNumbersSolver()
    result = solver.exec(_build_list([0]), _build_list([0]))
    assert _list_to_values(result) == [0], f"Example 2 失敗: {_list_to_values(result)}"


def test_example_three() -> None:
    """驗證 Example 3：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9] -> [8,9,9,9,0,0,0,1]。"""
    solver = AddTwoNumbersSolver()
    result = solver.exec(_build_list([9, 9, 9, 9, 9, 9, 9]), _build_list([9, 9, 9, 9]))
    assert _list_to_values(result) == [
        8,
        9,
        9,
        9,
        0,
        0,
        0,
        1,
    ], f"Example 3 失敗: {_list_to_values(result)}"


if __name__ == "__main__":
    test_example_one()
    test_example_two()
    test_example_three()
