#pragma once

#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <vector>

// 摘要：給定兩個已排序陣列 nums1 與 nums2，回傳合併後陣列的中位數，
// 整體時間複雜度須達到 O(log (m+n))。
class MedianOfTwoSortedArrays {
public:
    // exec 對應虛擬碼「尋找兩個排序陣列的中位數」函式，為本類別對外的唯一入口。
    // 約束：nums1.length == m, nums2.length == n, 0 <= m <= 1000, 0 <= n <= 1000,
    //       1 <= m + n <= 2000, -10^6 <= nums1[i], nums2[i] <= 10^6
    // 前提：nums1 與 nums2 須為已排序陣列（依摘要之描述）；驗證排序狀態需 O(m+n)，
    //       將違反題目要求之 O(log (m+n)) 複雜度，故不於執行期檢查排序狀態。
    [[nodiscard]] double exec(const std::vector<int>& nums1, const std::vector<int>& nums2) const {
        validate_boundary_input(nums1, nums2);

        // 虛擬碼：設定 短陣列 為 陣列一；設定 長陣列 為 陣列二
        const std::vector<int>* short_array = &nums1;
        const std::vector<int>* long_array = &nums2;

        // 虛擬碼：若 取得長度(短陣列) 大於 取得長度(長陣列) 則 交換(短陣列, 長陣列)
        if (short_array->size() > long_array->size()) {
            std::swap(short_array, long_array);
        }
        assert(short_array->size() <= long_array->size());

        return find_median_by_partition(*short_array, *long_array);
    }

private:
    // 邊界輸入驗證：nums1 與 nums2 之總長度須至少為 1（對應約束 1 <= m + n <= 2000）。
    static void validate_boundary_input(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        const std::size_t total_length = nums1.size() + nums2.size();
        if (total_length < 1) {
            throw std::invalid_argument("nums1 與 nums2 之總長度須至少為 1");
        }
    }

    // 虛擬碼主體：以二分搜尋於較短陣列上尋找正確分割位置，對應
    // 「迴圈 當 搜尋下界 小於等於 搜尋上界 時」至「結束迴圈」之邏輯。
    static double find_median_by_partition(const std::vector<int>& short_array,
                                            const std::vector<int>& long_array) {
        const int short_length = static_cast<int>(short_array.size());
        const int long_length = static_cast<int>(long_array.size());
        const int total_length = short_length + long_length;
        // 虛擬碼：設定 左半部目標數量 為 向下取整((總長度 加上 1) 除以 2)
        const int left_half_target_count = (total_length + 1) / 2;

        int search_lower_bound = 0;
        int search_upper_bound = short_length;

        while (search_lower_bound <= search_upper_bound) {
            const int short_partition = (search_lower_bound + search_upper_bound) / 2;
            const int long_partition = left_half_target_count - short_partition;

            // 虛擬碼：短陣列左側最大值 / 短陣列右側最小值 之邊界值計算，
            // 分割位置為 0 或等於陣列長度時以負／正無限大代表不存在之邊界元素。
            const int short_left_max = (short_partition == 0)
                ? std::numeric_limits<int>::min()
                : short_array[short_partition - 1];
            const int short_right_min = (short_partition == short_length)
                ? std::numeric_limits<int>::max()
                : short_array[short_partition];

            const int long_left_max = (long_partition == 0)
                ? std::numeric_limits<int>::min()
                : long_array[long_partition - 1];
            const int long_right_min = (long_partition == long_length)
                ? std::numeric_limits<int>::max()
                : long_array[long_partition];

            // 虛擬碼：若 短陣列左側最大值 小於等於 長陣列右側最小值
            //          且 長陣列左側最大值 小於等於 短陣列右側最小值 則
            if (short_left_max <= long_right_min && long_left_max <= short_right_min) {
                const int left_half_max = std::max(short_left_max, long_left_max);

                if (total_length % 2 == 0) {
                    const int right_half_min = std::min(short_right_min, long_right_min);
                    return (static_cast<double>(left_half_max) + static_cast<double>(right_half_min)) / 2.0;
                }
                return static_cast<double>(left_half_max);
            }

            // 虛擬碼：否則 若 短陣列左側最大值 大於 長陣列右側最小值 則 搜尋上界 為 短陣列分割位置 減 1
            if (short_left_max > long_right_min) {
                search_upper_bound = short_partition - 1;
            } else {
                // 虛擬碼：否則 搜尋下界 為 短陣列分割位置 加 1
                search_lower_bound = short_partition + 1;
            }
        }

        // 前提不成立（輸入陣列未排序）時之防禦性錯誤回報；若前提成立，迴圈必於上方回傳結果。
        throw std::invalid_argument("nums1 與 nums2 須為已排序陣列");
    }
};
