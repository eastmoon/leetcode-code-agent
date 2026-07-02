#pragma once

#include <cassert>
#include <string>
#include <unordered_map>

namespace leetcode {

/// 依據 LeetCode 第 3 題設計，計算輸入字串中不含重複字元之最長子字串長度。
class LongestSubstringFinder final {
public:
    /// exec 為虛擬碼邏輯之執行進入點，回傳不含重複字元之最長子字串長度。
    [[nodiscard]] int exec(const std::string& inputString) const;
};

int LongestSubstringFinder::exec(const std::string& inputString) const {
    // 約束：輸入字串長度須介於 0 至 5 * 10^4 之間
    assert(inputString.size() <= 50000 && "輸入字串長度超出約束範圍");

    // 虛擬碼：若輸入字串為空，回傳 0
    if (inputString.empty()) {
        return 0;
    }

    // 虛擬碼：建立空對映，記錄字元對應最近出現之索引
    std::unordered_map<char, int> characterToLastIndex;
    int longestLength = 0;
    int windowStartIndex = 0;

    // 虛擬碼：走訪輸入字串，取得目前索引與目前字元
    for (int currentIndex = 0; currentIndex < static_cast<int>(inputString.size()); ++currentIndex) {
        const char currentCharacter = inputString[currentIndex];

        // 虛擬碼：若目前字元已存在於表中，且其索引落於目前視窗範圍內，則收縮視窗起始索引
        const auto foundIterator = characterToLastIndex.find(currentCharacter);
        if (foundIterator != characterToLastIndex.end() && foundIterator->second >= windowStartIndex) {
            windowStartIndex = foundIterator->second + 1;
        }

        // 虛擬碼：將目前字元與目前索引的對應關係加入字元對應最近索引表
        characterToLastIndex[currentCharacter] = currentIndex;

        // 虛擬碼：計算目前視窗長度，並更新最長長度
        const int currentWindowLength = currentIndex - windowStartIndex + 1;
        if (currentWindowLength > longestLength) {
            longestLength = currentWindowLength;
        }
    }

    // 虛擬碼：回傳最長長度
    return longestLength;
}

}  // namespace leetcode
