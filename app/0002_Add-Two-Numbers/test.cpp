#include <cassert>
#include <memory>
#include <vector>

#include "main.cpp"

namespace {

// 建立鏈結串列（測試輔助函式）
std::unique_ptr<ListNode> buildList(const std::vector<int>& values) {
    auto dummyHead = std::make_unique<ListNode>(0);
    ListNode* currentNode = dummyHead.get();
    for (const int value : values) {
        currentNode->next = std::make_unique<ListNode>(value);
        currentNode = currentNode->next.get();
    }
    return std::move(dummyHead->next);
}

// 將鏈結串列轉換為數字清單（測試輔助函式）
std::vector<int> listToValues(const ListNode* head) {
    std::vector<int> values;
    const ListNode* currentNode = head;
    while (currentNode != nullptr) {
        values.push_back(currentNode->val);
        currentNode = currentNode->next.get();
    }
    return values;
}

// 驗證 Example 1：l1 = [2,4,3], l2 = [5,6,4] -> [7,0,8]
void testExampleOne() {
    const Solution solution;
    const auto l1 = buildList({2, 4, 3});
    const auto l2 = buildList({5, 6, 4});
    const auto result = solution.exec(l1.get(), l2.get());
    assert(listToValues(result.get()) == std::vector<int>({7, 0, 8}));
}

// 驗證 Example 2：l1 = [0], l2 = [0] -> [0]
void testExampleTwo() {
    const Solution solution;
    const auto l1 = buildList({0});
    const auto l2 = buildList({0});
    const auto result = solution.exec(l1.get(), l2.get());
    assert(listToValues(result.get()) == std::vector<int>({0}));
}

// 驗證 Example 3：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9] -> [8,9,9,9,0,0,0,1]
void testExampleThree() {
    const Solution solution;
    const auto l1 = buildList({9, 9, 9, 9, 9, 9, 9});
    const auto l2 = buildList({9, 9, 9, 9});
    const auto result = solution.exec(l1.get(), l2.get());
    assert(listToValues(result.get()) == std::vector<int>({8, 9, 9, 9, 0, 0, 0, 1}));
}

}  // namespace

int main() {
    testExampleOne();
    testExampleTwo();
    testExampleThree();
    return 0;
}
