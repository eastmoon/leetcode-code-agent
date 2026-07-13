# Python Guideline

Python 為動態型別、直譯式、支援多重典範（物件導向、函式式、程序式）之高階程式語言，特徵包含縮排定義區塊語法、鴨子型別 ( Duck Typing )、產生器與疊代器 ( Generator／Iterator )、裝飾器 ( Decorator )、脈絡管理器 ( Context Manager，`with` 語句 )、型別提示 ( Type Hint )。

## Code Rules

### I. 意圖提升 (Intent Elevation / What over How)

摘要禁止使用 `for`、`while`、`if`、`elif`、`return` 等 Python 關鍵字作為摘要動詞，除非該操作本身即為使用者可觀察之行為。裝飾器 ( Decorator ) 之摘要以其橫切關注點（如快取、授權、日誌）之意圖為主軸，禁止逐行描述包裹函式 ( wrapper ) 之呼叫順序。產生器 ( Generator，`yield` ) 之摘要以其延遲產生序列之業務目的為主軸，禁止複述 `yield` 語法本身。脈絡管理器 ( `with` 語句 ) 之摘要以其資源生命週期管理意圖為主軸，禁止逐行描述 `__enter__`／`__exit__` 呼叫順序。

例：摘要為「驗證輸入範圍」，而非「若 `x < 0` 則回傳 `False`，否則檢查 `x > max` 並回傳對應布林值」。

### II. 去噪與抽象化 (De-noising and Abstraction)

摘要排除 `import` 陳述、型別提示 ( Type Hint ) 語法之逐句描述、用於防禦性檢查（非業務邏輯）之 `assert` 語句描述。摘要排除樣板化之 `try/except` 純記錄或忽略錯誤邏輯，除非該處理本身即決定業務結果。串列、字典、集合綜合表達式 ( Comprehension ) 收斂為單一抽象操作，禁止展開為迴圈描述。巢狀裝飾器或巢狀函式，摘要為其最外層抽象目的，內層細節僅於必要時展開。

### III. 語意分塊 (Semantic Chunking)

切分邊界依循函式、類別 ( Class )、模組 ( `.py` 檔案 ) 之自然邊界，禁止以固定行數切分單一模組。以底線開頭（`_` 或 `__`）之慣例私有輔助函式／方法，其摘要併入呼叫者之摘要範圍，不個別產出摘要。同一功能拆分於套件 ( Package ) 內多個模組檔案之呼叫鏈，辨識其呼叫鏈後產出涵蓋整體流程之摘要，並標註各分塊於流程中之角色。多重繼承 ( Multiple Inheritance ) 與 Mixin 類別共同完成單一功能者，標註各分塊之角色。

### IV. 領域詞彙映射 (Domain Vocabulary Mapping)

摘要禁止直接沿用 Python 識別字（如底線前綴之慣例私有命名、單字母暫存變數）作為摘要用詞，除非該識別字已是領域詞彙。領域詞彙之映射依據 docstring、模組或套件命名、測試案例（pytest／unittest）命名，禁止臆測未出現於程式碼上下文之業務語意。鴨子型別 ( Duck Typing ) 使方法名稱與領域語意產生歧義時，標註為待釐清事項。摘要中對同一領域概念，於同一文件內固定使用單一詞彙，不因程式碼中出現多個同義識別字而交替使用不同摘要詞彙。

## Interpreting Constraints

產生器函式（`yield`）之延遲執行／惰性求值語意須標註，不得摘要為一般函式回傳一次性結果。

```python
def read_large_file(path):
    with open(path) as f:
        for line in f:
            yield line
```
摘要：「逐行延遲讀取大型檔案內容」。

裝飾器 ( Decorator ) 須標註其橫切關注點語意，不得與被裝飾函式本體邏輯混合摘要。

```python
@lru_cache
def fibonacci(n):
    ...
```
摘要：「計算費式數列並快取先前計算結果」。

脈絡管理器（`with` 語句）須標註資源獲取與釋放之語意，不得逕以區塊內程式碼摘要之。

```python
with open(path) as f:
    data = f.read()
```
摘要：「開啟檔案讀取內容後自動關閉檔案」。

型別提示 ( Type Hint ) 與實際執行期動態型別行為（鴨子型別）若產生落差（型別提示未被強制檢查），摘要不得逕以型別提示宣稱之型別作為唯一依據。

可變預設引數（Mutable Default Argument，如 `def f(x=[])`）之陷阱行為，若程式碼中出現此模式且影響業務結果，須於摘要標註其潛在共享狀態風險。

```python
def append_item(item, items=[]):
    items.append(item)
    return items
```
摘要標註：「將項目加入清單，且預設清單於多次呼叫間共享狀態」。

## Governance

本細則依循程式摘要憲章 (`.codekit/memory/constitution/code-summarization.md`) 之四項核心原則衍生，任一條目與憲章原則牴觸時，以憲章為準。修訂程序：條目之新增、刪除或重新定義，須標示異動對應之核心原則編號與差異內容。版本控制依循語意化版本規則：主要版本對應本細則治理規則或條目之不相容變更；次要版本對應新增條目或章節、或既有條目之大幅擴充；補丁版本對應文字澄清、錯字修正、非語意性修訂。合規性審查：Python 程式碼摘要產出前，須逐項核對本細則之 Code Rules 與 Interpreting Constraints，未通過核對之摘要不得視為最終產出。

**Version**: 1.0.0 | **Ratified**: 2026-07-13 | **Last Amended**: 2026-07-13
