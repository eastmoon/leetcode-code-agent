using System;
using LeetCode.AddTwoNumbers;

namespace LeetCode.AddTwoNumbers.Tests
{
    public sealed class Program
    {
        public static void Main(string[] args)
        {
            var solution = new Solution();

            // Example 1: l1 = [2,4,3], l2 = [5,6,4] -> Output: [7,0,8] (342 + 465 = 807)
            RunExample(solution, new[] { 2, 4, 3 }, new[] { 5, 6, 4 }, new[] { 7, 0, 8 }, "Example 1");

            // Example 2: l1 = [0], l2 = [0] -> Output: [0]
            RunExample(solution, new[] { 0 }, new[] { 0 }, new[] { 0 }, "Example 2");

            // Example 3: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9] -> Output: [8,9,9,9,0,0,0,1]
            RunExample(solution, new[] { 9, 9, 9, 9, 9, 9, 9 }, new[] { 9, 9, 9, 9 }, new[] { 8, 9, 9, 9, 0, 0, 0, 1 }, "Example 3");
        }

        // 執行單一範例：建立輸入鏈結串列、呼叫 Exec、比對預期輸出並印出結果
        private static void RunExample(Solution solution, int[] firstDigits, int[] secondDigits, int[] expectedDigits, string caseName)
        {
            ListNode l1 = BuildLinkedList(firstDigits);
            ListNode l2 = BuildLinkedList(secondDigits);

            ListNode? result = solution.Exec(l1, l2);
            int[] actualDigits = ToArray(result);

            bool isPassed = actualDigits.Length == expectedDigits.Length && actualDigits.AsSpan().SequenceEqual(expectedDigits);

            Console.WriteLine($"{caseName}: {(isPassed ? "PASS" : "FAIL")} - Expected: [{string.Join(",", expectedDigits)}] Actual: [{string.Join(",", actualDigits)}]");
        }

        // 依反序數字陣列建立鏈結串列（陣列首位為個位數）
        private static ListNode BuildLinkedList(int[] digits)
        {
            ListNode dummyHead = new ListNode();
            ListNode currentNode = dummyHead;

            foreach (int digit in digits)
            {
                currentNode.Next = new ListNode(digit);
                currentNode = currentNode.Next;
            }

            return dummyHead.Next!;
        }

        // 將鏈結串列轉換回反序數字陣列，供測試結果比對
        private static int[] ToArray(ListNode? head)
        {
            var digits = new System.Collections.Generic.List<int>();
            ListNode? currentNode = head;

            while (currentNode != null)
            {
                digits.Add(currentNode.Val);
                currentNode = currentNode.Next;
            }

            return digits.ToArray();
        }
    }
}
