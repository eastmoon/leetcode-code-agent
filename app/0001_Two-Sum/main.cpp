#include <unordered_map>
#include <vector>

// Two Sum：給定整數陣列與目標值，回傳兩數相加等於目標值之索引。
class Solution final {
public:
    // 需求：回傳兩數之索引，使其相加等於 target；同一元素不得使用兩次；回傳順序不限。
    [[nodiscard]] std::vector<int> exec(const std::vector<int>& nums, int target) const {
        // 虛擬碼：建立 空對映 數值對應索引表
        std::unordered_map<int, int> valueToIndex;
        valueToIndex.reserve(nums.size());

        // 虛擬碼：迴圈 走訪 數字清單，取得 目前索引 與 目前數值
        for (int currentIndex = 0; currentIndex < static_cast<int>(nums.size()); ++currentIndex) {
            const int currentValue = nums[currentIndex];
            // 虛擬碼：設 所需數值 為 目標值 減去 目前數值
            const int complementValue = target - currentValue;

            // 虛擬碼：若 所需數值 存在於 數值對應索引表 中 則
            const auto foundComplement = valueToIndex.find(complementValue);
            if (foundComplement != valueToIndex.end()) {
                // 虛擬碼：回傳 由 數值對應索引表中所需數值對應之索引 與 目前索引 組成的清單
                return {foundComplement->second, currentIndex};
            }

            // 虛擬碼：否則 將 目前數值 與 目前索引 的對應關係 加入 數值對應索引表
            valueToIndex.emplace(currentValue, currentIndex);
        }

        // 虛擬碼：回傳 空清單（約束保證恰有一組解，此路徑僅為型別完整性而存在）
        return {};
    }
};
