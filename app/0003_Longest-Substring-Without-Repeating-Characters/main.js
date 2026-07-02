/**
 * Longest Substring Without Repeating Characters：給定字串，回傳最長不重複字元子字串之長度。
 */
export class LongestSubstringSolver {
  /**
   * 尋找不重複字元之最長子字串長度。
   * @param {string} s - 輸入字串，長度介於 0 到 5*10^4，由英文字母、數字、符號與空白組成。
   * @returns {number} 最長不重複字元子字串之長度；輸入為空字串時回傳 0。
   */
  exec(s) {
    if (typeof s !== 'string') {
      throw new Error('s 須為字串。');
    }

    // 若 輸入字串 為空 則 回傳 0
    if (s.length === 0) {
      return 0;
    }

    // 建立 空對映 字元對應最近索引表
    const charToLastIndex = new Map();
    // 設 最長長度 為 0
    let longestLength = 0;
    // 設 視窗起始索引 為 0
    let windowStartIndex = 0;

    // 迴圈 走訪 輸入字串，取得 目前索引 與 目前字元
    for (let currentIndex = 0; currentIndex < s.length; currentIndex += 1) {
      const currentChar = s[currentIndex];

      // 若 目前字元 存在於 字元對應最近索引表 中 且 字元對應最近索引表中目前字元對應之索引 大於等於 視窗起始索引 則
      if (charToLastIndex.has(currentChar) && charToLastIndex.get(currentChar) >= windowStartIndex) {
        // 設 視窗起始索引 為 字元對應最近索引表中目前字元對應之索引 加 1
        windowStartIndex = charToLastIndex.get(currentChar) + 1;
      }

      // 將 目前字元 與 目前索引 的對應關係 加入 字元對應最近索引表
      charToLastIndex.set(currentChar, currentIndex);

      // 設 目前視窗長度 為 目前索引 減去 視窗起始索引 加 1
      const currentWindowLength = currentIndex - windowStartIndex + 1;

      // 若 目前視窗長度 大於 最長長度 則 設 最長長度 為 目前視窗長度
      if (currentWindowLength > longestLength) {
        longestLength = currentWindowLength;
      }
    }

    // 回傳 最長長度
    return longestLength;
  }
}
