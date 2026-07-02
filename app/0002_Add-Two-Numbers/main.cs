using System;

namespace LeetCode.AddTwoNumbers
{
    // 反序鏈結串列節點：個位數位於串列頭部，用以表示一個非負整數。
    public sealed class ListNode
    {
        public int Val { get; set; }
        public ListNode? Next { get; set; }

        public ListNode(int val = 0, ListNode? next = null)
        {
            Val = val;
            Next = next;
        }
    }

    // 求解兩個以反序鏈結串列表示之非負整數相加結果。
    public sealed class Solution
    {
        // 摘要：將兩個反序鏈結串列所表示之數字相加，回傳同樣以反序鏈結串列表示之總和。
        // 約束：兩鏈結串列節點個數介於 [1, 100]，節點數值介於 0 到 9，且不含前導零（0 本身除外）。
        public ListNode? Exec(ListNode l1, ListNode l2)
        {
            ArgumentNullException.ThrowIfNull(l1);
            ArgumentNullException.ThrowIfNull(l2);

            // 建立虛擬表頭節點，簡化結果串列的頭尾銜接邏輯
            ListNode dummyHead = new ListNode();
            ListNode currentResult = dummyHead;
            int carry = 0;
            ListNode? currentL1 = l1;
            ListNode? currentL2 = l2;

            // 迴圈：當任一鏈結串列仍有節點，或仍有進位值時，持續逐位相加
            while (currentL1 != null || currentL2 != null || carry != 0)
            {
                int firstValue = GetNodeValue(currentL1);
                int secondValue = GetNodeValue(currentL2);

                int digitSum = firstValue + secondValue + carry;
                carry = digitSum / 10;
                int currentDigit = digitSum % 10;

                currentResult.Next = new ListNode(currentDigit);
                currentResult = currentResult.Next;

                if (currentL1 != null)
                {
                    currentL1 = currentL1.Next;
                }

                if (currentL2 != null)
                {
                    currentL2 = currentL2.Next;
                }
            }

            return dummyHead.Next;
        }

        // 節點存在則回傳其數值，否則以 0 代表補位（處理兩串列長度不相等之情況）
        private static int GetNodeValue(ListNode? node)
        {
            return node != null ? node.Val : 0;
        }
    }
}
