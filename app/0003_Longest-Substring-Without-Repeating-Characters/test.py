"""Longest Substring Without Repeating Characters 測試模組。"""

from __future__ import annotations

from main import LongestSubstringSolver


def test_example_one() -> None:
    """驗證 Example 1：s = "abcabcbb" -> 3。"""
    solver = LongestSubstringSolver()
    result = solver.exec("abcabcbb")
    assert result == 3, f"Example 1 失敗: {result}"


def test_example_two() -> None:
    """驗證 Example 2：s = "bbbbb" -> 1。"""
    solver = LongestSubstringSolver()
    result = solver.exec("bbbbb")
    assert result == 1, f"Example 2 失敗: {result}"


def test_example_three() -> None:
    """驗證 Example 3：s = "pwwkew" -> 3。"""
    solver = LongestSubstringSolver()
    result = solver.exec("pwwkew")
    assert result == 3, f"Example 3 失敗: {result}"


if __name__ == "__main__":
    test_example_one()
    test_example_two()
    test_example_three()
