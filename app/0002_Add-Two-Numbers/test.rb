require_relative "main"

# Add Two Numbers 測試碼
# 依據設計需求中的範例進行驗證。

# 將整數陣列轉換為鏈結串列，回傳表頭節點。
def build_linked_list(values)
  dummy_head = ListNode.new
  current_node = dummy_head
  values.each do |value|
    current_node.next_node = ListNode.new(value)
    current_node = current_node.next_node
  end
  dummy_head.next_node
end

# 將鏈結串列轉換為整數陣列，便於與預期結果比對。
def linked_list_to_array(head)
  result = []
  current_node = head
  while current_node
    result << current_node.val
    current_node = current_node.next_node
  end
  result
end

if __FILE__ == $PROGRAM_NAME
  add_two_numbers = AddTwoNumbers.new

  # Example 1:
  # Input: l1 = [2,4,3], l2 = [5,6,4]
  # Output: [7,0,8]
  # Explanation: 342 + 465 = 807.
  result_1 = linked_list_to_array(add_two_numbers.exec(build_linked_list([2, 4, 3]), build_linked_list([5, 6, 4])))
  raise "Example 1 failed: #{result_1}" unless result_1 == [7, 0, 8]
  puts "Example 1 passed: #{result_1}"

  # Example 2:
  # Input: l1 = [0], l2 = [0]
  # Output: [0]
  result_2 = linked_list_to_array(add_two_numbers.exec(build_linked_list([0]), build_linked_list([0])))
  raise "Example 2 failed: #{result_2}" unless result_2 == [0]
  puts "Example 2 passed: #{result_2}"

  # Example 3:
  # Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
  # Output: [8,9,9,9,0,0,0,1]
  result_3 = linked_list_to_array(
    add_two_numbers.exec(build_linked_list([9, 9, 9, 9, 9, 9, 9]), build_linked_list([9, 9, 9, 9]))
  )
  raise "Example 3 failed: #{result_3}" unless result_3 == [8, 9, 9, 9, 0, 0, 0, 1]
  puts "Example 3 passed: #{result_3}"
end
