require_relative "main"

# Two Sum 測試碼
# 依據設計需求中的範例進行驗證。
if __FILE__ == $PROGRAM_NAME
  two_sum = TwoSum.new

  # Example 1:
  # Input: nums = [2,7,11,15], target = 9
  # Output: [0,1]
  # Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
  result_1 = two_sum.exec([2, 7, 11, 15], 9)
  raise "Example 1 failed: #{result_1}" unless result_1 == [0, 1]
  puts "Example 1 passed: #{result_1}"

  # Example 2:
  # Input: nums = [3,2,4], target = 6
  # Output: [1,2]
  result_2 = two_sum.exec([3, 2, 4], 6)
  raise "Example 2 failed: #{result_2}" unless result_2 == [1, 2]
  puts "Example 2 passed: #{result_2}"

  # Example 3:
  # Input: nums = [3,3], target = 6
  # Output: [0,1]
  result_3 = two_sum.exec([3, 3], 6)
  raise "Example 3 failed: #{result_3}" unless result_3 == [0, 1]
  puts "Example 3 passed: #{result_3}"
end
