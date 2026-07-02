using System;
using System.Collections.Generic;

namespace LeetCode.LongestSubstringWithoutRepeatingCharacters
{
    // 求解字串中不含重複字元之最長子字串長度。
    public sealed class Solution
    {
        // 摘要：給定字串 s，回傳不含重複字元之最長子字串長度。
        // 約束：s 長度介於 [0, 5*10^4]，可包含英文字母、數字、符號與空白。
        // 註釋：回傳值為長度（整數）而非子字串本身；子字串須為連續字元序列。
        public int Exec(string s)
        {
            ArgumentNullException.ThrowIfNull(s);

            // 輸入字串為空時，回傳 0
            if (s.Length == 0)
            {
                return 0;
            }

            // 建立字元對應最近索引表，用以判斷滑動視窗內是否已出現該字元
            var lastSeenIndex = new Dictionary<char, int>();
            int longestLength = 0;
            int windowStart = 0;

            // 迴圈：走訪輸入字串，取得目前索引與目前字元
            for (int currentIndex = 0; currentIndex < s.Length; currentIndex++)
            {
                char currentChar = s[currentIndex];

                // 目前字元存在於對應表中，且其對應索引落於目前視窗內，須收縮視窗起始索引
                if (lastSeenIndex.TryGetValue(currentChar, out int previousIndex) && previousIndex >= windowStart)
                {
                    windowStart = previousIndex + 1;
                }

                lastSeenIndex[currentChar] = currentIndex;

                int currentWindowLength = currentIndex - windowStart + 1;
                if (currentWindowLength > longestLength)
                {
                    longestLength = currentWindowLength;
                }
            }

            return longestLength;
        }
    }
}
