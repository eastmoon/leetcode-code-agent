# Add Two Numbers
#
# 摘要：
# 給定兩個非空的鏈結串列，分別代表兩個非負整數。
# 數字以反序方式儲存，且每個節點只包含一位數字。
# 將兩數相加，並以鏈結串列回傳其總和。
# 除了數字 0 本身，兩數皆不含前導零。
#
# 約束：
# - 每個鏈結串列的節點數量介於 [1, 100] 之間。
# - 0 <= Node.val <= 9
# - 保證鏈結串列所表示之數字不含前導零。
#
# 註釋：
# - 數字以反序儲存於鏈結串列中（個位數在串列頭部）。
# - 回傳結果同樣須以反序鏈結串列表示。
# - 兩個鏈結串列的長度可以不相等，需處理進位（carry）至結果串列末端的情況。

# 鏈結串列節點，僅作為資料容器，不承載運算邏輯。
class ListNode
  attr_accessor :val, :next_node

  def initialize(val = 0, next_node = nil)
    @val = val
    @next_node = next_node
  end
end

class AddTwoNumbers
  # 執行虛擬碼邏輯：逐位相加兩鏈結串列之數值並處理進位，
  # 以虛擬表頭節點串接結果，回傳結果串列之實際表頭。
  def exec(first_list_head, second_list_head)
    # 建立 虛擬表頭節點
    dummy_head = ListNode.new
    # 設 目前結果節點 為 虛擬表頭節點
    current_result_node = dummy_head
    # 設 進位值 為 0
    carry = 0
    # 設 目前第一節點 為 第一鏈結串列表頭
    current_first_node = first_list_head
    # 設 目前第二節點 為 第二鏈結串列表頭
    current_second_node = second_list_head

    # 迴圈 當 目前第一節點 存在 或 目前第二節點 存在 或 進位值 不為 0
    while current_first_node || current_second_node || carry != 0
      # 若 目前第一節點 存在 則 設 第一數值 為 目前第一節點的數值 否則 設 第一數值 為 0
      first_value = current_first_node ? current_first_node.val : 0
      # 若 目前第二節點 存在 則 設 第二數值 為 目前第二節點的數值 否則 設 第二數值 為 0
      second_value = current_second_node ? current_second_node.val : 0

      # 設 位數總和 為 第一數值 加上 第二數值 加上 進位值
      digit_sum = first_value + second_value + carry
      # 設 進位值 為 位數總和 整除 10
      carry = digit_sum / 10
      # 設 目前位數 為 位數總和 除以 10 取餘數
      current_digit = digit_sum % 10

      # 建立 新節點，數值為 目前位數；將 新節點 接續於 目前結果節點 之後
      current_result_node.next_node = ListNode.new(current_digit)
      # 設 目前結果節點 為 新節點
      current_result_node = current_result_node.next_node

      # 若 目前第一節點 存在 則 設 目前第一節點 為 目前第一節點的下一節點
      current_first_node = current_first_node.next_node if current_first_node
      # 若 目前第二節點 存在 則 設 目前第二節點 為 目前第二節點的下一節點
      current_second_node = current_second_node.next_node if current_second_node
    end

    # 回傳 虛擬表頭節點的下一節點
    dummy_head.next_node
  end
end
