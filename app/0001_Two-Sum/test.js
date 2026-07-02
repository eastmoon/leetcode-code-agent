import assert from 'node:assert/strict';

import { TwoSumSolver } from './main.js';

// 需求範例 1：nums = [2,7,11,15], target = 9 -> [0,1]
function testExampleOne() {
  const solver = new TwoSumSolver();
  const result = solver.exec([2, 7, 11, 15], 9);
  assert.deepEqual(result, [0, 1]);
}

// 需求範例 2：nums = [3,2,4], target = 6 -> [1,2]
function testExampleTwo() {
  const solver = new TwoSumSolver();
  const result = solver.exec([3, 2, 4], 6);
  assert.deepEqual(result, [1, 2]);
}

// 需求範例 3：nums = [3,3], target = 6 -> [0,1]
function testExampleThree() {
  const solver = new TwoSumSolver();
  const result = solver.exec([3, 3], 6);
  assert.deepEqual(result, [0, 1]);
}

testExampleOne();
testExampleTwo();
testExampleThree();
