# JavaScript Guideline

JavaScript 為動態型別、直譯式（或即時編譯）、支援多重典範（原型導向物件、函式式、事件驅動）之程式語言，特徵包含原型鏈繼承 ( Prototype Chain )、閉包 ( Closure )、事件迴圈與非同步機制 ( Event Loop、Promise、`async`／`await` )、一級函式 ( First-class Function )、動態型別強制轉換 ( Type Coercion )。

## Code Rules

### I. 意圖提升 (Intent Elevation / What over How)

摘要禁止使用 `for`、`while`、`if`、`switch`、`return` 等 JavaScript 關鍵字作為摘要動詞，除非該操作本身即為使用者可觀察之行為。閉包 ( Closure ) 之摘要以其封裝狀態保存或私有化之意圖為主軸，禁止逐行描述外層函式變數如何被內層函式捕捉。`Promise`／`async`／`await` 鏈之摘要以非同步業務目的為主軸，禁止複述 `.then()` 鏈式呼叫語法本身。箭頭函式 ( Arrow Function ) 與回呼函式 ( Callback ) 之摘要以其註冊之事件或處理目的為主軸，禁止複述函式傳遞語法本身。

例：摘要為「驗證輸入範圍」，而非「若 `x < 0` 則回傳 `false`，否則檢查 `x > max` 並回傳對應布林值」。

### II. 去噪與抽象化 (De-noising and Abstraction)

摘要排除 `import`／`require` 模組載入陳述、`console.log` 等除錯輸出陳述、寬鬆比較 (`==`) 造成之隱性型別轉換之逐句描述。摘要排除樣板化之 `try/catch` 與 `Promise.catch` 純記錄錯誤邏輯，除非該處理本身即決定業務結果。陣列與物件操作方法鏈 ( `map`、`filter`、`reduce` 等 ) 收斂為單一抽象角色，禁止逐一列舉鏈中各方法。閉包所產生之巢狀函式，摘要為其最外層抽象目的，內層細節僅於必要時展開。

### III. 語意分塊 (Semantic Chunking)

切分邊界依循函式、類別 ( Class )、模組 ( ES Module／CommonJS ) 之自然邊界，禁止以固定行數切分單一檔案。未匯出 ( non-exported ) 之私有輔助函式，其摘要併入呼叫者之摘要範圍，不個別產出摘要。同一功能拆分於多個模組檔案（如 controller、service、model）之呼叫鏈，辨識其呼叫鏈後產出涵蓋整體流程之摘要，並標註各分塊於流程中之角色。立即呼叫函式運算式 ( IIFE, Immediately Invoked Function Expression ) 與其內部邏輯視為單一語意區塊，不拆分摘要。

### IV. 領域詞彙映射 (Domain Vocabulary Mapping)

摘要禁止直接沿用 JavaScript 識別字（如駝峰式命名之縮寫、`_` 開頭之慣例私有欄位命名）作為摘要用詞，除非該識別字已是領域詞彙。領域詞彙之映射依據 JSDoc 註解、模組或檔案命名、測試案例（Jest／Mocha）命名，禁止臆測未出現於程式碼上下文之業務語意。原型方法或 `this` 綁定所產生之語意與領域詞彙產生衝突時，標註為待釐清事項。摘要中對同一領域概念，於同一文件內固定使用單一詞彙，不因程式碼中出現多個同義識別字而交替使用不同摘要詞彙。

## Interpreting Constraints

非同步語意 ( `Promise`、`async`／`await`、回呼函式 ) 須於摘要中明確標註，不得省略以致與同步執行邏輯混淆。

```javascript
async function fetchUser(id) {
  return await api.get(`/users/${id}`);
}
```
摘要：「非同步取得使用者資料」，禁止摘要為「取得使用者資料」而省略非同步語意。

`this` 綁定語意依函式宣告方式（一般函式與箭頭函式）而異，若該差異影響行為則須標註。

```javascript
class Counter {
  increment = () => { this.count++; };
}
```
摘要：「以箭頭函式綁定實例上下文之遞增方法」，避免與一般方法 `this` 動態綁定之語意混淆。

動態型別強制轉換 ( Type Coercion，如 `+` 號兼具字串串接與數字相加之雙重語意 ) 須標註其實際運算語意，不得逕以運算符號字面摘要。

```javascript
const total = "5" + 3; // "53"
```
摘要標註：「字串串接」，禁止摘要為「相加」。

事件迴圈中微任務與巨集任務 ( Microtask／Macrotask，如 `Promise`、`setTimeout` ) 之排程順序若影響業務結果，須標註其非同步排程語意。

解構賦值 ( Destructuring ) 與展開運算子 ( Spread／Rest Operator ) 之摘要以其資料萃取或合併意圖為主軸，不逐一描述語法本身。

```javascript
const { name, ...rest } = user;
```
摘要：「取出使用者名稱並保留其餘屬性」。

## Governance

本細則依循程式摘要憲章 (`.codekit/memory/constitution/code-summarization.md`) 之四項核心原則衍生，任一條目與憲章原則牴觸時，以憲章為準。修訂程序：條目之新增、刪除或重新定義，須標示異動對應之核心原則編號與差異內容。版本控制依循語意化版本規則：主要版本對應本細則治理規則或條目之不相容變更；次要版本對應新增條目或章節、或既有條目之大幅擴充；補丁版本對應文字澄清、錯字修正、非語意性修訂。合規性審查：JavaScript 程式碼摘要產出前，須逐項核對本細則之 Code Rules 與 Interpreting Constraints，未通過核對之摘要不得視為最終產出。

**Version**: 1.0.0 | **Ratified**: 2026-07-13 | **Last Amended**: 2026-07-13
