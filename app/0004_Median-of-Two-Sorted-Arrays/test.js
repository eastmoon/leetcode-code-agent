import { MedianOfTwoSortedArrays } from './main.js';

/**
 * 浮點數比較須容許誤差，避免因浮點運算精度差異導致誤判。
 *
 * @param {number} actual
 * @param {number} expected
 * @param {string} testName
 * @param {number} [tolerance]
 */
function assertApproximatelyEqual(actual, expected, testName, tolerance = 1e-5) {
  if (Math.abs(actual - expected) >= tolerance) {
    throw new Error(`${testName} failed: expected ${expected}, actual ${actual}`);
  }
  console.log(`${testName} passed: ${actual}`);
}

const solution = new MedianOfTwoSortedArrays();

// Example 1:
// Input: nums1 = [1,3], nums2 = [2]
// Output: 2.00000
// Explanation: merged array = [1,2,3] and median is 2.
const result1 = solution.exec([1, 3], [2]);
assertApproximatelyEqual(result1, 2.0, 'Example 1');

// Example 2:
// Input: nums1 = [1,2], nums2 = [3,4]
// Output: 2.50000
// Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
const result2 = solution.exec([1, 2], [3, 4]);
assertApproximatelyEqual(result2, 2.5, 'Example 2');

console.log('All test cases passed.');
