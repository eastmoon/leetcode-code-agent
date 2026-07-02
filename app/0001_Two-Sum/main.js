/**
 * Two Sum：給定整數陣列與目標值，回傳兩數相加等於目標值之索引。
 */
export class TwoSumSolver {
  /**
   * 尋找兩數之索引，使其相加等於目標值。
   * @param {number[]} nums - 整數陣列，長度須介於 2 到 10^4 之間，僅保證恰有一組解。
   * @param {number} target - 目標總和。
   * @returns {number[]} 兩個索引組成的陣列，順序不限。
   */
  exec(nums, target) {
    if (!Array.isArray(nums)) {
      throw new Error('nums 須為陣列。');
    }
    if (nums.length < 2) {
      throw new Error('nums 長度須至少為 2。');
    }

    // 建立 空對映 數值對應索引表
    const valueToIndex = new Map();

    // 迴圈 走訪 數字清單，取得 目前索引 與 目前數值
    for (let currentIndex = 0; currentIndex < nums.length; currentIndex += 1) {
      const currentValue = nums[currentIndex];

      // 設 所需數值 為 目標值 減去 目前數值
      const complement = target - currentValue;

      // 若 所需數值 存在於 數值對應索引表 中 則
      if (valueToIndex.has(complement)) {
        // 回傳 由 數值對應索引表中所需數值對應之索引 與 目前索引 組成的清單
        return [valueToIndex.get(complement), currentIndex];
      }

      // 否則 將 目前數值 與 目前索引 的對應關係 加入 數值對應索引表
      valueToIndex.set(currentValue, currentIndex);
    }

    // 回傳 空清單
    return [];
  }
}
