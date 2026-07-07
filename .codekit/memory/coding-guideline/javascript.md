# JavaScript Guideline

JavaScript 為動態型別、直譯式（Interpreted）程式語言，採用原型鏈（Prototype-based）物件導向模型，具備一級函式（First-Class Function）、閉包（Closure）、事件迴圈（Event Loop）與 Promise/async-await 非同步機制，廣泛應用於瀏覽器前端與 Node.js 伺服器端開發。

## Coding Rules

### I. Meaningful Naming (有意義的命名)

- 變數與函式命名採 camelCase；類別命名採 PascalCase；常數採 UPPER_SNAKE_CASE，禁止使用單字母命名（迴圈計數器 `i`、`j`、`k` 等傳統慣例除外）。
- 布林變數或旗標命名須以 `is`、`has`、`should` 等前綴表達真偽語意（例如 `isValid`、`hasPermission`）。
- 同一概念於整個程式碼庫須使用一致詞彙，禁止對同一事物使用多個不同名稱。

**理由**：一致且具語意的命名降低跨檔案、跨團隊協作時的理解成本。

---

### II. Small, Single-Purpose Functions (小型單一目的函式)

- 函式（含箭頭函式、方法）須只負責單一職責；函式長度超過 30 行須評估拆分。
- 巢狀回呼（Callback）超過 2 層須改以 Promise 鏈或 `async`/`await` 重構，避免回呼地獄（Callback Hell）。
- 參數個數超過 3 個須改以物件參數（Options Object）封裝取代。
- 巢狀迴圈或條件分支超過 2 層須以衛語句（Guard Clause）或提早回傳（Early Return）重構。

**理由**：小型函式易於理解、測試與重用，降低認知負擔。

---

### III. Self-Documenting Code Over Comments (自我說明優先於註解)

- 程式碼須透過命名與結構表達意圖；註解僅用於解釋「為何」而非「做什麼」。
- 公開函式與模組之 JSDoc 註解僅描述參數、回傳值與拋出例外，禁止贅述實作步驟。
- 禁止保留註解掉的程式碼、過時註解或與實作行為不一致的註解。

**理由**：程式碼是唯一不會過期的文件；註解易與實作脫節，造成誤導。

---

### IV. No Duplication (DRY, Don't Repeat Yourself)

- 重複邏輯須抽取為共用函式或工具模組，禁止跨檔案複製貼上相同邏輯。
- 優先使用陣列高階函式（`map`、`filter`、`reduce`）取代重新實作既有迭代邏輯。
- 共用常數、設定值須集中於單一模組（Single Source of Truth），禁止於多個檔案中重複宣告相同意義的常數。

**理由**：重複邏輯造成維護時多處修改風險，容易產生不一致缺陷。

---

### V. Fail Fast & Explicit Error Handling (快速失敗與顯式錯誤處理)

- 偵測到不合法狀態或非預期輸入，須立即拋出 `Error`（或其子類別）並中止當前操作，禁止靜默忽略。
- 禁止回傳 `undefined`、`null` 掩蓋錯誤而不加說明；`async` 函式須以 `try`/`catch` 或 `.catch()` 明確處理拒絕（Rejected）狀態，禁止遺留未處理的 Promise 拒絕（Unhandled Promise Rejection）。
- 禁止使用空的 `catch (error) {}` 區塊吞噬例外而不記錄或重新拋出。

**理由**：儘早暴露錯誤可縮小除錯範圍，避免錯誤狀態擴散至系統其他部分。

---

### VI. Input Validation at Boundaries (邊界輸入驗證)

- 所有外部輸入（HTTP 請求主體、查詢參數、使用者輸入、環境變數、`JSON.parse` 結果）進入函式或路由處理常式邊界時，須完成型別、範圍、格式驗證。
- 禁止信任任何未經驗證的外部資料；驗證失敗須拒絕處理並回報明確錯誤。
- 已於邊界驗證之資料在內部模組間傳遞時，禁止重複進行相同驗證造成邏輯冗贅。

**理由**：邊界驗證阻絕不可信資料流入核心邏輯，降低注入與例外風險。

---

### VII. Assertions & Preconditions (斷言與前置條件)

- 函式前置條件須以明確的防護子句表達（例如 `if (!value) throw new Error('...')`），用於偵測不應發生之程式錯誤。
- 開發階段診斷用之 `console.assert` 僅用於除錯輸出，禁止作為控制流程或錯誤處理手段。
- 關鍵安全性檢查須以顯式 `if` 檢查搭配拋出例外實作，禁止依賴僅於開發環境生效之斷言機制。

**理由**：明確的防護子句將隱性假設轉換為可執行檢查，使違反假設的狀態立即可見。

---

### VIII. Immutability & Minimized Side Effects (不變性與最小化副作用)

- 變數宣告優先使用 `const`；僅在確實需要重新賦值時使用 `let`，禁止使用 `var`。
- 函式須避免修改輸入參數；需要衍生新資料時，優先使用展開運算子（Spread Operator）或 `Object.freeze` 建立新值而非原地修改。
- 避免使用可變（mutable）全域變數與模組層級共享狀態；必要之副作用須於函式命名或文件明確標示。

**理由**：不變性與最小副作用降低狀態追蹤複雜度，提升可測試性與並行安全性。

---

### IX. Consistent Formatting & Structure (一致的格式與結構)

- 專案須以 ESLint 與 Prettier 統一格式化規則（縮排、引號、分號、換行），並以自動化工具強制執行。
- 模組匯入（`import`）順序須一致（外部套件、內部模組、相對路徑），並依邏輯分組。
- 每個檔案原則上對應單一類別、元件或功能模組，禁止同一專案內混用不同組織風格。

**理由**：一致格式降低視覺解析成本，使程式碼審查聚焦於邏輯而非風格差異。

---

### X. Boy Scout Rule (童子軍原則)

- 每次修改程式碼時，須讓其比修改前更清晰整潔，禁止在既有混亂基礎上疊加新的混亂。
- 修改程式碼時發現的 ESLint 警告須一併處理，禁止在未說明理由的情況下新增 `eslint-disable`。
- 發現技術債務須記錄或於能力範圍內即時修正，不得無限期擱置。

**理由**：持續性微幅改善避免程式碼腐化累積至無法維護的臨界點。

## Design Constraints

### I. Single Responsibility Principle (SRP)

- 每個模組（Module）或類別對應單一職責；當一個模組同時承擔多項職責時，須拆分為獨立模組。
- 函式長度超過 30 行，須檢視是否違反單一職責並評估拆分。

**理由**：單一職責使變更範圍可控，避免修改一處邏輯連帶影響無關功能。

---

### II. Open/Closed Principle (OCP)

- 擴展須透過高階函式（Higher-Order Function）、組合（Composition）或類別繼承（`extends`）達成，禁止直接修改已穩定且被多處引用之匯出函式或類別。
- 新行為優先以傳入策略函式（Strategy Function）或設定物件參數化既有函式的方式達成，而非修改其內部邏輯。

**理由**：降低修改已驗證程式碼所帶來的回歸風險，使系統可持續擴展。

---

### III. Liskov Substitution Principle (LSP)

- 子類別（透過 `extends` 繼承）覆寫父類別方法時，不得削弱父類別的前置條件，亦不得強化後置條件。
- 禁止以拋出「未實作」錯誤（例如 `throw new Error('Not implemented')`）的方式覆寫父類別方法作為常態行為；若行為無法一致替代，須以組合（Composition）或混入（Mixin）取代繼承。

**理由**：確保多型行為的一致性，防止呼叫端因替換子型別而產生隱性執行期錯誤。

---

### IV. Interface Segregation Principle (ISP)

- 模組匯出（Export）須依使用方需求拆分為小型、專一之函式或物件，禁止匯出強迫呼叫方依賴不需要方法的大型物件。
- 共用物件之方法數超過 5 個時，須評估是否應拆分為多個職責明確的模組。

**理由**：細粒度模組使依賴關係精確，降低不必要的耦合。

---

### V. Dependency Inversion Principle (DIP)

- 高層模組不得直接 `import` 低層模組之具體實作；依賴須以函式參數、回呼函式（Callback）或注入的物件形式傳入（依賴注入）。
- 業務邏輯函式禁止在內部直接建立具體依賴實例；具體實作須於呼叫端（進入點模組）組裝並傳入。

**理由**：依賴反轉使高層邏輯可在不修改的情況下替換底層實作，提升可測試性與可替換性。

---

### VI. High Cohesion, Low Coupling

- 每個模組僅負責單一明確的功能群組，相關邏輯須集中於同一模組內。
- 模組間的依賴關係須最小化；跨模組溝通僅能透過明確匯出的函式或物件進行，禁止直接存取其他模組之私有（未匯出）狀態。
- 模組內部實作細節須以未匯出（未 `export`）的變數與函式封裝，僅暴露必要之公開介面。

**理由**：高內聚確保變更影響範圍可預測；低耦合確保模組可獨立替換、測試與部署。

---

### VII. Separation of Concerns (SoC)

- 資料存取、業務邏輯、呈現層（DOM 操作或 UI 元件）須分置於不同模組，禁止於同一函式或元件內混合三者邏輯。
- 跨切面關注點（日誌記錄、快取、驗證）須以中介層（Middleware）或裝飾函式（Higher-Order Function）實作，禁止散佈於業務邏輯程式碼各處。

**理由**：關注點分離使各層可獨立演進，降低連鎖修改風險，提升可測試性與可維護性。

## Governance

- 本指南須遵循 `.codekit/memory/constitution/coding-guideline.md` 與 `.codekit/memory/constitution/software-design.md` 兩份憲章之原則，若指南內容與憲章衝突，以憲章為準。
- 指南修訂須記錄變更原因、影響範圍，並由專案維護者核准後方可生效。
- 版本控制遵循語意版本規則：
  - 主要版本（MAJOR）：規則重新定義或不相容變更。
  - 次要版本（MINOR）：新增規則或章節，或大幅擴展具體指導方針。
  - 補丁版本（PATCH）：措詞澄清、錯字修正、非語意改進。
- 合規性審查於每次程式碼審查（Code Review）時逐條對照本指南執行。

**Version**: 1.0.0 | **Ratified**: 2026-07-07 | **Last Amended**: 2026-07-07
