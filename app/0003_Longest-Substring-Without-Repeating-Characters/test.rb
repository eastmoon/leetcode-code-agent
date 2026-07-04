require_relative "main"

# Longest Substring Without Repeating Characters 測試碼
# 依據設計需求中的範例進行驗證。
if __FILE__ == $PROGRAM_NAME
  longest_substring = LongestSubstringWithoutRepeatingCharacters.new

  # Example 1:
  # Input: s = "abcabcbb"
  # Output: 3
  # Explanation: The answer is "abc", with the length of 3.
  result_1 = longest_substring.exec("abcabcbb")
  raise "Example 1 failed: #{result_1}" unless result_1 == 3
  puts "Example 1 passed: #{result_1}"

  # Example 2:
  # Input: s = "bbbbb"
  # Output: 1
  # Explanation: The answer is "b", with the length of 1.
  result_2 = longest_substring.exec("bbbbb")
  raise "Example 2 failed: #{result_2}" unless result_2 == 1
  puts "Example 2 passed: #{result_2}"

  # Example 3:
  # Input: s = "pwwkew"
  # Output: 3
  # Explanation: The answer is "wke", with the length of 3.
  # Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
  result_3 = longest_substring.exec("pwwkew")
  raise "Example 3 failed: #{result_3}" unless result_3 == 3
  puts "Example 3 passed: #{result_3}"
end
