# Longest Palindromic Substring

## 摘要

Given a string `s`, return the longest palindromic substring in `s`.

## 範例

**Example 1:**
```
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.
```

**Example 2:**
```
Input: s = "cbbd"
Output: "bb"
```

## 約束

- `1 <= s.length <= 1000`
- `s` consist of only digits and English letters.

## 註釋

- 回文（Palindrome）定義為正讀與反讀相同的字串，例如 `"aba"`、`"bb"`。
- 若有多個長度相同的最長回文子字串，回傳其中任一皆可（如範例一所示）。
