/**
 * Add Two Numbers：給定兩個以反序儲存非負整數之鏈結串列，回傳其和之反序鏈結串列。
 */
export class AddTwoNumbersSolver {
  /**
   * 相加兩鏈結串列所表示之數字。
   * @param {{ val: number, next: object|null }} l1 - 第一鏈結串列表頭，數字以反序儲存，個位數在表頭，節點數介於 1 到 100。
   * @param {{ val: number, next: object|null }} l2 - 第二鏈結串列表頭，數字以反序儲存，個位數在表頭，節點數介於 1 到 100。
   * @returns {{ val: number, next: object|null }|null} 相加結果之反序鏈結串列表頭。
   */
  exec(l1, l2) {
    if (l1 === undefined || l2 === undefined) {
      throw new Error('l1 與 l2 為必要參數，不可為 undefined。');
    }

    // 建立 虛擬表頭節點
    const dummyHead = createNode(0, null);
    // 設 目前結果節點 為 虛擬表頭節點
    let currentResultNode = dummyHead;
    // 設 進位值 為 0
    let carry = 0;
    // 設 目前第一節點 為 第一鏈結串列表頭
    let currentFirstNode = l1;
    // 設 目前第二節點 為 第二鏈結串列表頭
    let currentSecondNode = l2;

    // 迴圈 當 目前第一節點 存在 或 目前第二節點 存在 或 進位值 不為 0
    while (currentFirstNode !== null || currentSecondNode !== null || carry !== 0) {
      // 若 目前第一節點 存在 則 設 第一數值 為 目前第一節點的數值；否則 設 第一數值 為 0
      const firstValue = currentFirstNode !== null ? currentFirstNode.val : 0;
      // 若 目前第二節點 存在 則 設 第二數值 為 目前第二節點的數值；否則 設 第二數值 為 0
      const secondValue = currentSecondNode !== null ? currentSecondNode.val : 0;

      // 設 位數總和 為 第一數值 加上 第二數值 加上 進位值
      const digitSum = firstValue + secondValue + carry;
      // 設 進位值 為 位數總和 整除 10
      carry = Math.floor(digitSum / 10);
      // 設 目前位數 為 位數總和 除以 10 取餘數
      const currentDigit = digitSum % 10;

      // 建立 新節點，數值為 目前位數；將 新節點 接續於 目前結果節點 之後
      currentResultNode.next = createNode(currentDigit, null);
      // 設 目前結果節點 為 新節點
      currentResultNode = currentResultNode.next;

      // 若 目前第一節點 存在 則 設 目前第一節點 為 目前第一節點的下一節點
      if (currentFirstNode !== null) {
        currentFirstNode = currentFirstNode.next;
      }
      // 若 目前第二節點 存在 則 設 目前第二節點 為 目前第二節點的下一節點
      if (currentSecondNode !== null) {
        currentSecondNode = currentSecondNode.next;
      }
    }

    // 回傳 虛擬表頭節點的下一節點
    return dummyHead.next;
  }
}

/**
 * 建立鏈結串列節點。
 * @param {number} val - 節點數值，範圍為 0 到 9。
 * @param {object|null} next - 下一節點參照。
 * @returns {{ val: number, next: object|null }} 節點物件。
 */
function createNode(val, next) {
  return { val, next };
}
