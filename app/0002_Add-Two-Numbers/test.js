import assert from 'node:assert/strict';

import { AddTwoNumbersSolver } from './main.js';

// 建立鏈結串列（測試輔助函式）
function buildList(values) {
  let head = null;
  let tail = null;
  for (const value of values) {
    const node = { val: value, next: null };
    if (head === null) {
      head = node;
    } else {
      tail.next = node;
    }
    tail = node;
  }
  return head;
}

// 將鏈結串列轉換為陣列（測試輔助函式）
function listToArray(head) {
  const values = [];
  let currentNode = head;
  while (currentNode !== null) {
    values.push(currentNode.val);
    currentNode = currentNode.next;
  }
  return values;
}

// 需求範例 1：l1 = [2,4,3], l2 = [5,6,4] -> [7,0,8]
function testExampleOne() {
  const solver = new AddTwoNumbersSolver();
  const result = solver.exec(buildList([2, 4, 3]), buildList([5, 6, 4]));
  assert.deepEqual(listToArray(result), [7, 0, 8]);
}

// 需求範例 2：l1 = [0], l2 = [0] -> [0]
function testExampleTwo() {
  const solver = new AddTwoNumbersSolver();
  const result = solver.exec(buildList([0]), buildList([0]));
  assert.deepEqual(listToArray(result), [0]);
}

// 需求範例 3：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9] -> [8,9,9,9,0,0,0,1]
function testExampleThree() {
  const solver = new AddTwoNumbersSolver();
  const result = solver.exec(
    buildList([9, 9, 9, 9, 9, 9, 9]),
    buildList([9, 9, 9, 9]),
  );
  assert.deepEqual(listToArray(result), [8, 9, 9, 9, 0, 0, 0, 1]);
}

testExampleOne();
testExampleTwo();
testExampleThree();
