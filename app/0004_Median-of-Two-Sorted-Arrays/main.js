/**
 * 摘要：給定兩個已排序陣列 nums1 與 nums2，回傳合併後陣列的中位數，
 * 整體時間複雜度須達到 O(log (m+n))。
 */
class MedianOfTwoSortedArrays {
  /**
   * exec 對應虛擬碼「尋找兩個排序陣列的中位數」函式，為本類別對外的唯一入口。
   *
   * @param {number[]} nums1 已排序整數陣列，對應約束 0 <= m <= 1000。
   * @param {number[]} nums2 已排序整數陣列，對應約束 0 <= n <= 1000。
   * @returns {number} 合併後陣列之中位數。
   * @throws {Error} 當 nums1 與 nums2 之總長度小於 1 時拋出。
   */
  exec(nums1, nums2) {
    this.#validateBoundaryInput(nums1, nums2);

    // 虛擬碼：設定 短陣列 為 陣列一；設定 長陣列 為 陣列二
    let shortArray = nums1;
    let longArray = nums2;

    // 虛擬碼：若 取得長度(短陣列) 大於 取得長度(長陣列) 則 交換(短陣列, 長陣列)
    if (shortArray.length > longArray.length) {
      [shortArray, longArray] = [longArray, shortArray];
    }

    return this.#findMedianByPartition(shortArray, longArray);
  }

  /**
   * 邊界輸入驗證：nums1 與 nums2 之總長度須至少為 1（對應約束 1 <= m + n <= 2000）。
   *
   * @param {number[]} nums1
   * @param {number[]} nums2
   */
  #validateBoundaryInput(nums1, nums2) {
    const totalLength = nums1.length + nums2.length;
    if (totalLength < 1) {
      throw new Error('nums1 與 nums2 之總長度須至少為 1。');
    }
  }

  /**
   * 虛擬碼主體：以二分搜尋於較短陣列上尋找正確分割位置，對應
   * 「迴圈 當 搜尋下界 小於等於 搜尋上界 時」至「結束迴圈」之邏輯。
   *
   * 前提：shortArray 與 longArray 須為已排序陣列（依摘要之描述）；驗證排序狀態
   * 需 O(m+n)，將違反題目要求之 O(log (m+n)) 複雜度，故不於執行期檢查排序狀態。
   *
   * @param {number[]} shortArray
   * @param {number[]} longArray
   * @returns {number}
   */
  #findMedianByPartition(shortArray, longArray) {
    const shortLength = shortArray.length;
    const longLength = longArray.length;
    const totalLength = shortLength + longLength;
    // 虛擬碼：設定 左半部目標數量 為 向下取整((總長度 加上 1) 除以 2)
    const leftHalfTargetCount = Math.floor((totalLength + 1) / 2);

    let searchLowerBound = 0;
    let searchUpperBound = shortLength;

    while (searchLowerBound <= searchUpperBound) {
      const shortPartition = Math.floor((searchLowerBound + searchUpperBound) / 2);
      const longPartition = leftHalfTargetCount - shortPartition;

      // 虛擬碼：短陣列左側最大值 / 短陣列右側最小值，分割位置為 0 或等於陣列長度時
      // 以正負無限大代表不存在之邊界元素。
      const shortLeftMax = shortPartition === 0
        ? Number.NEGATIVE_INFINITY
        : shortArray[shortPartition - 1];
      const shortRightMin = shortPartition === shortLength
        ? Number.POSITIVE_INFINITY
        : shortArray[shortPartition];

      const longLeftMax = longPartition === 0
        ? Number.NEGATIVE_INFINITY
        : longArray[longPartition - 1];
      const longRightMin = longPartition === longLength
        ? Number.POSITIVE_INFINITY
        : longArray[longPartition];

      // 虛擬碼：若 短陣列左側最大值 小於等於 長陣列右側最小值
      //          且 長陣列左側最大值 小於等於 短陣列右側最小值 則
      if (shortLeftMax <= longRightMin && longLeftMax <= shortRightMin) {
        const leftHalfMax = Math.max(shortLeftMax, longLeftMax);

        if (totalLength % 2 === 0) {
          const rightHalfMin = Math.min(shortRightMin, longRightMin);
          return (leftHalfMax + rightHalfMin) / 2;
        }

        return leftHalfMax;
      }

      // 虛擬碼：否則 若 短陣列左側最大值 大於 長陣列右側最小值 則 搜尋上界 為 短陣列分割位置 減 1
      if (shortLeftMax > longRightMin) {
        searchUpperBound = shortPartition - 1;
      } else {
        // 虛擬碼：否則 搜尋下界 為 短陣列分割位置 加 1
        searchLowerBound = shortPartition + 1;
      }
    }

    // 前提不成立（輸入陣列未排序）時之防禦性錯誤回報；若前提成立，迴圈必於上方回傳結果。
    throw new Error('nums1 與 nums2 須為已排序陣列。');
  }
}

export { MedianOfTwoSortedArrays };
