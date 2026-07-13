# C++ Guideline

C++ 為靜態型別、支援多重程式設計典範（程序式、物件導向、泛型、範本後設程式設計）之編譯式程式語言，特徵包含手動記憶體管理與 RAII 資源管理機制、運算子多載、範本 ( Template ) 泛型機制、多重繼承與虛擬函式多型機制、標準範本函式庫 ( STL )。

## Code Rules

### I. 意圖提升 (Intent Elevation / What over How)

摘要禁止使用 `for`、`while`、`if`、`switch`、`return` 等 C++ 關鍵字作為摘要動詞，除非該操作本身即為使用者可觀察之行為。建構函式 ( Constructor )、解構函式 ( Destructor )、運算子多載 ( Operator Overloading ) 之摘要，以其對外呈現之物件生命週期管理意圖或運算語意為主軸，禁止逐行複述初始化列表 ( Initializer List ) 或成員逐一指派之順序。範本函式 ( Template Function ) 與範本類別 ( Template Class ) 之摘要，以其泛型化之業務目的為主軸，禁止複述 `template<typename T>` 語法本身。

例：摘要為「驗證輸入範圍」，而非「若 `x < 0` 則回傳 `false`，否則檢查 `x > max` 並回傳對應布林值」。

### II. 去噪與抽象化 (De-noising and Abstraction)

摘要排除 `#include` 前置處理指令、`using namespace` 宣告、`noexcept`／`constexpr`／`inline` 等修飾詞、`static_cast`／`dynamic_cast` 等型別轉換語法之逐句描述。摘要排除建構子／解構子之樣板初始化與 `try/catch` 例外處理之樣板重拋 ( rethrow ) 邏輯，除非該例外處理本身即決定業務結果。STL 容器 ( `std::vector`、`std::map`、`std::unique_ptr` 等 ) 之操作收斂為其抽象角色（「暫存清單」、「所有權管理指標」），除非容器之特定選型為理解行為之必要條件。巢狀範本特化 ( Template Specialization ) 或巢狀 Lambda 表達式，摘要為其最外層抽象目的，內層細節僅於必要時展開。

### III. 語意分塊 (Semantic Chunking)

切分邊界依循函式、類別 ( Class )、結構 ( Struct )、命名空間 ( Namespace ) 或編譯單元 ( Translation Unit ) 之自然邊界，禁止以固定行數切分單一 `.cpp`／`.h` 檔案。標示為 `private` 或位於未命名命名空間 ( Anonymous Namespace ) 之輔助函式，其摘要併入呼叫者之摘要範圍，不個別產出摘要。跨標頭檔 (`.h`) 與原始檔 (`.cpp`) 共同組成之單一類別或函式，須合併宣告與定義後產出單一摘要，不因檔案分離而重複或割裂摘要內容。類別繼承鏈 ( 基底類別、衍生類別、虛擬函式覆寫 ) 共同完成單一功能者，辨識其呼叫鏈後標註各分塊於流程中之角色。

### IV. 領域詞彙映射 (Domain Vocabulary Mapping)

摘要禁止直接沿用 C++ 識別字（如 `m_`、`_impl` 前綴、匈牙利命名法前綴等實作慣例命名）作為摘要用詞，除非該識別字已是領域詞彙。領域詞彙之映射依據命名空間名稱、類別註解、Doxygen 註解區塊 (`/** ... */`)、單元測試案例命名，禁止臆測未出現於程式碼上下文之業務語意。運算子多載之語意（如 `operator+` 用於向量相加）與領域詞彙產生歧義時，標註為待釐清事項。摘要中對同一領域概念，於同一文件內固定使用單一詞彙，不因程式碼中出現多個同義識別字（如 `size`、`length`、`count`）而交替使用不同摘要詞彙。

## Interpreting Constraints

指標與參照 ( Pointer / Reference ) 之所有權語意須於摘要中明確標註（「持有所有權」、「借用」），不得省略。

```cpp
std::unique_ptr<Connection> createConnection();
```
摘要：「建立連線並轉移其所有權予呼叫者」，禁止摘要為「回傳連線」。

前置處理巨集 (`#define`) 與條件編譯 (`#ifdef`) 區塊，摘要須標註其為編譯期分支而非執行期邏輯，不得與 `if` 執行期條件式合併摘要。

```cpp
#ifdef _WIN32
    void platformInit();
#else
    void platformInitUnix();
#endif
```
摘要：「依編譯目標平台選用對應之初始化實作（Windows 或 Unix）」。

運算子多載函式摘要須標註其對應之語言內建運算符號，不得以函式名稱直接作為摘要用詞。

```cpp
bool operator==(const Point& lhs, const Point& rhs);
```
摘要：「比較兩點座標是否相等」，禁止摘要為「執行 operator== 函式」。

範本後設程式設計 ( Template Metaprogramming，如 `std::enable_if`、`constexpr if` ) 之編譯期邏輯，摘要須標註其為編譯期型別篩選或分支，禁止與執行期邏輯合併同一敘述句。

多執行緒同步原語 (`std::mutex`、`std::atomic`、`std::lock_guard`) 出現於程式碼中時，摘要須標註其並行安全意圖（「確保執行緒安全存取」），不得省略。

## Governance

本細則依循程式摘要憲章 (`.codekit/memory/constitution/code-summarization.md`) 之四項核心原則衍生，任一條目與憲章原則牴觸時，以憲章為準。修訂程序：條目之新增、刪除或重新定義，須標示異動對應之核心原則編號與差異內容。版本控制依循語意化版本規則：主要版本對應本細則治理規則或條目之不相容變更；次要版本對應新增條目或章節、或既有條目之大幅擴充；補丁版本對應文字澄清、錯字修正、非語意性修訂。合規性審查：C++ 程式碼摘要產出前，須逐項核對本細則之 Code Rules 與 Interpreting Constraints，未通過核對之摘要不得視為最終產出。

**Version**: 1.0.0 | **Ratified**: 2026-07-13 | **Last Amended**: 2026-07-13
