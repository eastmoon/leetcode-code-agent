# Longest Substring Without Repeating Characters

## 摘要

Given a string `s`, find the length of the longest substring without repeating characters.

## 範例

**Example 1:**
```
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
```

**Example 2:**
```
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

**Example 3:**
```
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

## 約束

- `0 <= s.length <= 5 * 10^4`
- `s` consists of English letters, digits, symbols and spaces.

## 註釋

- 回傳的是子字串的長度（整數），而非子字串本身。
- 子字串（substring）須為連續字元序列，不可為子序列（subsequence）。
- 當輸入字串為空時，回傳 `0`。
