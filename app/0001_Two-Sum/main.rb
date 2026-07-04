# Two Sum
#
# 摘要：
# 給定一個整數陣列 nums 與一個整數 target，
# 回傳兩個數字相加等於 target 的索引。
# 假設每組輸入恰好存在一個解，且不可重複使用同一個元素。
# 回傳順序不限。
#
# 約束：
# - 2 <= nums.length <= 10^4
# - -10^9 <= nums[i] <= 10^9
# - -10^9 <= target <= 10^9
# - 僅存在一個有效解。
#
# 註釋：
# - 回傳的是索引（indices），而非數值本身。
# - 同一個元素不得使用兩次（i != j）。
# - 答案的順序不限（[0,1] 與 [1,0] 均可接受）。
class TwoSum
  # 執行虛擬碼邏輯：以雜湊表（Hash）記錄「數值 -> 索引」對應關係，
  # 走訪一次陣列即可找出兩數之索引。
  def exec(nums, target)
    # 建立 空對映 數值對應索引表
    value_to_index = {}

    # 迴圈 走訪 數字清單，取得 目前索引 與 目前數值
    nums.each_with_index do |current_value, current_index|
      # 設 所需數值 為 目標值 減去 目前數值
      complement = target - current_value

      # 若 所需數值 存在於 數值對應索引表 中 則
      if value_to_index.key?(complement)
        # 回傳 由 數值對應索引表中所需數值對應之索引 與 目前索引 組成的清單
        return [value_to_index[complement], current_index]
      end

      # 否則 將 目前數值 與 目前索引 的對應關係 加入 數值對應索引表
      value_to_index[current_value] = current_index
    end

    # 回傳 空清單
    []
  end
end
