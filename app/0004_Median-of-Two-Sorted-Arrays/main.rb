# frozen_string_literal: true

# 摘要：給定兩個已排序陣列 nums1（長度 m）與 nums2（長度 n），
# 回傳兩陣列合併後的中位數，且整體時間複雜度須達到 O(log (m+n))。
#
# 約束：0 <= m, n <= 1000；1 <= m + n <= 2000；-10^6 <= nums1[i], nums2[i] <= 10^6。
#
# 註釋：中位數為排序後陣列之中間值，若合併後長度為偶數則取中間兩數之平均值；
# 為達 O(log (m+n)) 複雜度，須以二分搜尋於較短陣列上尋找分割位置，
# 而非直接合併兩陣列後排序。
class MedianOfTwoSortedArrays
  # 尋找兩個排序陣列的中位數
  def exec(nums1, nums2)
    # 對應虛擬碼：設定 短陣列 為 陣列一，設定 長陣列 為 陣列二
    short_array = nums1
    long_array = nums2

    # 對應虛擬碼：若 取得長度(短陣列) 大於 取得長度(長陣列) 則 交換(短陣列, 長陣列)
    short_array, long_array = long_array, short_array if short_array.length > long_array.length

    partition_median(short_array, long_array)
  end

  private

  # 於較短陣列上以二分搜尋尋找左右分割位置，使左右兩側元素數量與大小關係符合中位數定義
  def partition_median(short_array, long_array)
    # 對應虛擬碼：設定 短陣列長度、長陣列長度、總長度、左半部目標數量
    short_length = short_array.length
    long_length = long_array.length
    total_length = short_length + long_length
    left_half_count = (total_length + 1) / 2

    # 對應虛擬碼：設定 搜尋下界 為 0，設定 搜尋上界 為 短陣列長度
    search_lower_bound = 0
    search_upper_bound = short_length

    # 對應虛擬碼：迴圈 當 搜尋下界 小於等於 搜尋上界 時
    while search_lower_bound <= search_upper_bound
      short_partition = (search_lower_bound + search_upper_bound) / 2
      long_partition = left_half_count - short_partition

      short_left_max, short_right_min = partition_edges(short_array, short_partition, short_length)
      long_left_max, long_right_min = partition_edges(long_array, long_partition, long_length)

      # 對應虛擬碼：若 短陣列左側最大值 小於等於 長陣列右側最小值 且 長陣列左側最大值 小於等於 短陣列右側最小值 則
      if short_left_max <= long_right_min && long_left_max <= short_right_min
        left_half_max = [short_left_max, long_left_max].max

        # 對應虛擬碼：若 總長度 為偶數 則 回傳 (左半部最大值 加上 右半部最小值) 除以 2，否則 回傳 左半部最大值
        return left_half_max unless total_length.even?

        right_half_min = [short_right_min, long_right_min].min
        return (left_half_max + right_half_min) / 2.0
      elsif short_left_max > long_right_min
        # 對應虛擬碼：否則 若 短陣列左側最大值 大於 長陣列右側最小值 則 設定 搜尋上界 為 短陣列分割位置 減 1
        search_upper_bound = short_partition - 1
      else
        # 對應虛擬碼：否則 設定 搜尋下界 為 短陣列分割位置 加 1
        search_lower_bound = short_partition + 1
      end
    end
  end

  # 取得指定分割位置左側最大值與右側最小值；邊界外側以正負無限大代表不影響比較結果
  def partition_edges(array, partition, length)
    left_max = partition.zero? ? -Float::INFINITY : array[partition - 1]
    right_min = partition == length ? Float::INFINITY : array[partition]
    [left_max, right_min]
  end
end
