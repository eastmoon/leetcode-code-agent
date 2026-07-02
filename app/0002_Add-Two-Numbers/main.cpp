#include <memory>

// Add Two Numbers：給定兩個以反序儲存非負整數之鏈結串列，回傳其和之反序鏈結串列。

// 鏈結串列節點，數值範圍為 0 到 9；以 unique_ptr 管理下一節點之生命週期。
struct ListNode {
    int val;
    std::unique_ptr<ListNode> next;

    explicit ListNode(int value) : val(value), next(nullptr) {}
};

class Solution final {
public:
    // 需求：相加兩鏈結串列所表示之數字，回傳結果鏈結串列表頭；節點數介於 1 到 100，個位數在表頭。
    [[nodiscard]] std::unique_ptr<ListNode> exec(const ListNode* l1, const ListNode* l2) const {
        // 虛擬碼：建立 虛擬表頭節點
        auto dummyHead = std::make_unique<ListNode>(0);
        // 虛擬碼：設 目前結果節點 為 虛擬表頭節點
        ListNode* currentResultNode = dummyHead.get();
        // 虛擬碼：設 進位值 為 0
        int carry = 0;
        // 虛擬碼：設 目前第一節點 為 第一鏈結串列表頭
        const ListNode* currentFirstNode = l1;
        // 虛擬碼：設 目前第二節點 為 第二鏈結串列表頭
        const ListNode* currentSecondNode = l2;

        // 虛擬碼：迴圈 當 目前第一節點 存在 或 目前第二節點 存在 或 進位值 不為 0
        while (currentFirstNode != nullptr || currentSecondNode != nullptr || carry != 0) {
            // 虛擬碼：若 目前第一節點 存在 則 設 第一數值 為其數值 否則 設 第一數值 為 0
            const int firstValue = currentFirstNode != nullptr ? currentFirstNode->val : 0;
            // 虛擬碼：若 目前第二節點 存在 則 設 第二數值 為其數值 否則 設 第二數值 為 0
            const int secondValue = currentSecondNode != nullptr ? currentSecondNode->val : 0;

            // 虛擬碼：設 位數總和 為 第一數值 加上 第二數值 加上 進位值
            const int digitSum = firstValue + secondValue + carry;
            // 虛擬碼：設 進位值 為 位數總和 整除 10
            carry = digitSum / 10;
            // 虛擬碼：設 目前位數 為 位數總和 除以 10 取餘數
            const int currentDigit = digitSum % 10;

            // 虛擬碼：建立 新節點，數值為 目前位數；將 新節點 接續於 目前結果節點 之後
            currentResultNode->next = std::make_unique<ListNode>(currentDigit);
            // 虛擬碼：設 目前結果節點 為 新節點
            currentResultNode = currentResultNode->next.get();

            // 虛擬碼：若 目前第一節點 存在 則 設 目前第一節點 為其下一節點
            if (currentFirstNode != nullptr) {
                currentFirstNode = currentFirstNode->next.get();
            }
            // 虛擬碼：若 目前第二節點 存在 則 設 目前第二節點 為其下一節點
            if (currentSecondNode != nullptr) {
                currentSecondNode = currentSecondNode->next.get();
            }
        }

        // 虛擬碼：回傳 虛擬表頭節點的下一節點
        return std::move(dummyHead->next);
    }
};
