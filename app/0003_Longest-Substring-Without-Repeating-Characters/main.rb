# Longest Substring Without Repeating Characters
#
# 摘要：
# 給定一個字串 s，找出其中不含重複字元的最長子字串長度。
#
# 約束：
# - 0 <= s.length <= 5 * 10^4
# - s 由英文字母、數字、符號與空白組成。
#
# 註釋：
# - 回傳的是子字串的長度（整數），而非子字串本身。
# - 子字串（substring）須為連續字元序列，不可為子序列（subsequence）。
# - 當輸入字串為空時，回傳 0。
class LongestSubstringWithoutRepeatingCharacters
  # 執行虛擬碼邏輯：以滑動視窗（Sliding Window）搭配雜湊表記錄
  # 「字元 -> 最近索引」，動態調整視窗起始位置以避免重複字元。
  def exec(input_string)
    # 若 輸入字串 為空 則 回傳 0
    return 0 if input_string.empty?

    # 建立 空對映 字元對應最近索引表
    char_to_last_index = {}
    # 設 最長長度 為 0
    longest_length = 0
    # 設 視窗起始索引 為 0
    window_start_index = 0

    # 迴圈 走訪 輸入字串，取得 目前索引 與 目前字元
    input_string.each_char.with_index do |current_char, current_index|
      # 若 目前字元 存在於 字元對應最近索引表 中 且 對應之索引 大於等於 視窗起始索引 則
      if char_to_last_index.key?(current_char) && char_to_last_index[current_char] >= window_start_index
        # 設 視窗起始索引 為 字元對應最近索引表中目前字元對應之索引 加 1
        window_start_index = char_to_last_index[current_char] + 1
      end

      # 將 目前字元 與 目前索引 的對應關係 加入 字元對應最近索引表
      char_to_last_index[current_char] = current_index

      # 設 目前視窗長度 為 目前索引 減去 視窗起始索引 加 1
      current_window_length = current_index - window_start_index + 1
      # 若 目前視窗長度 大於 最長長度 則 設 最長長度 為 目前視窗長度
      longest_length = current_window_length if current_window_length > longest_length
    end

    # 回傳 最長長度
    longest_length
  end
end
