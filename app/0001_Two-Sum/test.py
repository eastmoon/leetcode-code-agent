"""Two Sum 測試模組。"""

from __future__ import annotations

from main import TwoSumSolver


def test_example_one() -> None:
    """驗證 Example 1：nums = [2,7,11,15], target = 9 -> [0,1]。"""
    solver = TwoSumSolver()
    result = solver.exec([2, 7, 11, 15], 9)
    assert result == [0, 1], f"Example 1 失敗: {result}"


def test_example_two() -> None:
    """驗證 Example 2：nums = [3,2,4], target = 6 -> [1,2]。"""
    solver = TwoSumSolver()
    result = solver.exec([3, 2, 4], 6)
    assert result == [1, 2], f"Example 2 失敗: {result}"


def test_example_three() -> None:
    """驗證 Example 3：nums = [3,3], target = 6 -> [0,1]。"""
    solver = TwoSumSolver()
    result = solver.exec([3, 3], 6)
    assert result == [0, 1], f"Example 3 失敗: {result}"


if __name__ == "__main__":
    test_example_one()
    test_example_two()
    test_example_three()
