"""測試碼：驗證 MedianOfTwoSortedArrays.exec 於題目範例之正確性。"""

from __future__ import annotations

import math

from main import MedianOfTwoSortedArrays


def _assert_approximately_equal(
    actual: float, expected: float, test_name: str, tolerance: float = 1e-5
) -> None:
    """浮點數比較須容許誤差，避免因浮點運算精度差異導致誤判。"""
    if not math.isclose(actual, expected, abs_tol=tolerance):
        raise AssertionError(f"{test_name} failed: expected {expected}, actual {actual}")
    print(f"{test_name} passed: {actual}")


if __name__ == "__main__":
    solution = MedianOfTwoSortedArrays()

    # Example 1:
    # Input: nums1 = [1,3], nums2 = [2]
    # Output: 2.00000
    # Explanation: merged array = [1,2,3] and median is 2.
    result_1 = solution.exec([1, 3], [2])
    _assert_approximately_equal(result_1, 2.0, "Example 1")

    # Example 2:
    # Input: nums1 = [1,2], nums2 = [3,4]
    # Output: 2.50000
    # Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
    result_2 = solution.exec([1, 2], [3, 4])
    _assert_approximately_equal(result_2, 2.5, "Example 2")

    print("All test cases passed.")
