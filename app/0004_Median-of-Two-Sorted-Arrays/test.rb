# frozen_string_literal: true

require 'minitest/autorun'
require_relative 'main'

# 依據「Median of Two Sorted Arrays」問題之範例情境驗證 MedianOfTwoSortedArrays#exec 邏輯正確性
class MedianOfTwoSortedArraysTest < Minitest::Test
  def setup
    @solution = MedianOfTwoSortedArrays.new
  end

  # Example 1: nums1 = [1,3], nums2 = [2] -> merged array = [1,2,3]，中位數為 2.00000
  def test_example_1
    assert_in_delta 2.00000, @solution.exec([1, 3], [2]), 1e-5
  end

  # Example 2: nums1 = [1,2], nums2 = [3,4] -> merged array = [1,2,3,4]，中位數為 (2 + 3) / 2 = 2.50000
  def test_example_2
    assert_in_delta 2.50000, @solution.exec([1, 2], [3, 4]), 1e-5
  end
end
