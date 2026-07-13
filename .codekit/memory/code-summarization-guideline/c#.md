# C# Guideline

C# 為微軟開發之靜態型別、物件導向為主、執行於 .NET／CLR ( Common Language Runtime ) 之受管理程式語言，特徵包含自動垃圾回收 ( Garbage Collection )、LINQ 查詢語法、`async`／`await` 非同步程式設計模型、屬性 ( Property )、委派 ( Delegate ) 與事件 ( Event ) 機制、特性標註 ( Attribute ) 機制。

## Code Rules

### I. 意圖提升 (Intent Elevation / What over How)

摘要禁止使用 `for`、`while`、`if`、`switch`、`return` 等 C# 關鍵字作為摘要動詞，除非該操作本身即為使用者可觀察之行為。屬性 ( Property ) 之 `get`／`set` 存取子摘要，以其封裝之欄位存取語意為主軸，禁止逐一描述存取子語法。`async`／`await` 方法之摘要須以其非同步業務目的為主軸，禁止複述 `Task`／`await` 語法本身。LINQ 查詢鏈 ( `Where`、`Select`、`OrderBy` 等 ) 之摘要以其集合轉換之業務意圖為主軸，禁止逐一列舉各查詢方法呼叫。

例：摘要為「驗證輸入範圍」，而非「若 `x < 0` 則回傳 `false`，否則檢查 `x > max` 並回傳對應布林值」。

### II. 去噪與抽象化 (De-noising and Abstraction)

摘要排除 `using` 指示詞、`namespace` 宣告、`var` 型別推斷、`as`／`is` 型別轉換語法之逐句描述。摘要排除建構函式之樣板初始化與 `try/catch/finally` 例外處理之樣板重拋 ( rethrow ) 或記錄邏輯，除非該例外處理本身即決定業務結果。集合型別 ( `List<T>`、`Dictionary<TKey, TValue>`、`IEnumerable<T>` 等 ) 之操作收斂為其抽象角色（「暫存清單」、「索引對照表」），除非型別選型為理解行為之必要條件。巢狀 LINQ 查詢或巢狀 Lambda 運算式，摘要為其最外層抽象目的，內層細節僅於必要時展開。

### III. 語意分塊 (Semantic Chunking)

切分邊界依循類別 ( Class )、結構 ( Struct )、介面 ( Interface )、命名空間 ( Namespace ) 或檔案之自然邊界，禁止以固定行數切分單一 `.cs` 檔案。標示為 `private` 或 `internal` 之輔助方法，其摘要併入呼叫者之摘要範圍，不個別產出摘要。以 `partial` 修飾之部分類別 ( Partial Class ) 分散於多檔案者，須合併各部分定義後產出單一摘要，不因檔案分離而重複或割裂摘要內容。介面實作鏈 ( 介面宣告、實作類別、擴充方法 Extension Method ) 共同完成單一功能者，辨識其呼叫鏈後標註各分塊於流程中之角色。

### IV. 領域詞彙映射 (Domain Vocabulary Mapping)

摘要禁止直接沿用 C# 識別字（如 `_camelCase` 私有欄位前綴、`I` 開頭之介面命名慣例本身）作為摘要用詞，除非該識別字已是領域詞彙。領域詞彙之映射依據 XML 文件註解 ( `/// <summary>` )、命名空間名稱、介面命名、單元測試（xUnit／NUnit／MSTest）案例命名，禁止臆測未出現於程式碼上下文之業務語意。運算子多載或隱含轉換運算子 ( `implicit operator` ) 之語意與領域詞彙產生歧義時，標註為待釐清事項。摘要中對同一領域概念，於同一文件內固定使用單一詞彙，不因程式碼中出現多個同義識別字（如 `Count`、`Length`、`Size`）而交替使用不同摘要詞彙。

## Interpreting Constraints

`async`／`await` 方法之非同步語意須於摘要中明確標註，不得省略以致與同步阻塞方法混淆。

```csharp
public async Task<User> GetUserAsync(int id)
```
摘要：「非同步取得使用者資料」，禁止摘要為「取得使用者資料」而省略非同步語意。

LINQ 查詢鏈須摘要為單一集合轉換操作，不得逐一描述各查詢方法呼叫。

```csharp
var result = items.Where(x => x.IsActive).Select(x => x.Name).ToList();
```
摘要：「篩選出啟用項目並取出其名稱清單」。

特性標註 ( Attribute，如 `[HttpGet]`、`[Obsolete]`、`[Serializable]` ) 須標註其宣告式後設資料語意，不得與方法本體之執行邏輯合併同一敘述句。

```csharp
[HttpGet("users/{id}")]
public IActionResult GetUser(int id)
```
摘要：「處理取得指定使用者資料之 GET 請求」。

委派 ( Delegate ) 與事件 ( Event ) 之回呼或通知語意須於摘要中明確標註，不得省略。

```csharp
public event EventHandler<OrderPlacedEventArgs> OrderPlaced;
```
摘要：「訂單建立完成時觸發通知事件」。

`yield return` 產生之疊代器方法 ( Iterator Method ) 須標註其延遲執行 ( Lazy Evaluation ) 語意，不得摘要為一般函式回傳。

## Governance

本細則依循程式摘要憲章 (`.codekit/memory/constitution/code-summarization.md`) 之四項核心原則衍生，任一條目與憲章原則牴觸時，以憲章為準。修訂程序：條目之新增、刪除或重新定義，須標示異動對應之核心原則編號與差異內容。版本控制依循語意化版本規則：主要版本對應本細則治理規則或條目之不相容變更；次要版本對應新增條目或章節、或既有條目之大幅擴充；補丁版本對應文字澄清、錯字修正、非語意性修訂。合規性審查：C# 程式碼摘要產出前，須逐項核對本細則之 Code Rules 與 Interpreting Constraints，未通過核對之摘要不得視為最終產出。

**Version**: 1.0.0 | **Ratified**: 2026-07-13 | **Last Amended**: 2026-07-13
