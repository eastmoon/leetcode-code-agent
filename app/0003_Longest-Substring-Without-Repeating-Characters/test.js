import assert from 'node:assert/strict';

import { LongestSubstringSolver } from './main.js';

// 需求範例 1：s = "abcabcbb" -> 3
function testExampleOne() {
  const solver = new LongestSubstringSolver();
  const result = solver.exec('abcabcbb');
  assert.equal(result, 3);
}

// 需求範例 2：s = "bbbbb" -> 1
function testExampleTwo() {
  const solver = new LongestSubstringSolver();
  const result = solver.exec('bbbbb');
  assert.equal(result, 1);
}

// 需求範例 3：s = "pwwkew" -> 3
function testExampleThree() {
  const solver = new LongestSubstringSolver();
  const result = solver.exec('pwwkew');
  assert.equal(result, 3);
}

testExampleOne();
testExampleTwo();
testExampleThree();
