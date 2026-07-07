# C# Guideline

C# 為通用、靜態型別、物件導向程式語言，運行於 .NET 執行環境（Common Language Runtime）之上，具備自動記憶體管理（Garbage Collection）、屬性（Property）、事件（Event）、委派（Delegate）、LINQ 與非同步（async/await）等語言特性，廣泛應用於企業應用程式、Web 服務與桌面應用程式開發。

## Coding Rules

### I. Meaningful Naming (有意義的命名)

- 類別、方法、屬性、命名空間採 PascalCase；區域變數與參數採 camelCase；禁止使用單字母命名（迴圈計數器 `i`、`j`、`k` 等傳統慣例除外）。
- 介面命名須以 `I` 為前綴（例如 `IRepository`），明確表達其為抽象契約。
- 非同步方法（`async`）命名須以 `Async` 為後綴，明確表達其呼叫方式與回傳 `Task`/`Task<T>` 之語意。
- 禁止使用匈牙利命名法（Hungarian Notation）標示型別於變數名稱中；同一概念於整個方案（Solution）須使用一致詞彙。

**理由**：一致且具語意的命名降低跨檔案、跨團隊協作時的理解成本。

---

### II. Small, Single-Purpose Functions (小型單一目的函式)

- 方法（含區域函式、Lambda 運算式）須只負責單一職責；方法長度超過 30 行須評估拆分。
- LINQ 查詢鏈須維持可讀性，過長或巢狀之查詢運算式須拆分為具名區域函式或中繼變數。
- 巢狀迴圈或條件分支超過 2 層須以衛語句（Guard Clause）或提早回傳（Early Return）重構。

**理由**：小型方法降低認知負擔，並提升單元測試之覆蓋率與可讀性。

---

### III. Self-Documenting Code Over Comments (自我說明優先於註解)

- 優先使用列舉（`enum`）、記錄型別（`record`）與強型別別名取代裸露的整數或字串常數，以型別系統表達意圖。
- 註解僅用於解釋「為何」如此設計，禁止用於重述程式碼邏輯。
- 禁止保留註解掉的程式碼片段；版本控制系統已足以保留歷史紀錄。
- 公開 API 之 XML 文件註解（`///`）僅描述前置條件、後置條件與例外行為，禁止贅述實作步驟。

**理由**：型別系統與清晰結構是最可靠的文件，可隨程式碼變更同步更新。

---

### IV. No Duplication (DRY, Don't Repeat Yourself)

- 重複邏輯須抽取為方法、擴充方法（Extension Method）或泛型（Generic）工具類別，禁止跨檔案複製貼上相同邏輯。
- 優先使用標準函式庫（LINQ、`System.Linq`、`System.Collections.Generic`）取代重新實作既有演算法。
- 共用常數與設定值須集中於單一來源（例如 `appsettings.json` 搭配強型別選項類別），禁止於多個檔案中重複宣告相同意義的常數。

**理由**：重複邏輯造成多處修改風險，且違反標準函式庫已驗證之正確性與效能。

---

### V. Fail Fast & Explicit Error Handling (快速失敗與顯式錯誤處理)

- 可預期之錯誤情境須以例外（Exception）、可為 Null 參考型別（Nullable Reference Types）或明確結果型別（Result Pattern）回傳，禁止以特殊哨兵值（如 `-1`、未說明之 `null`）掩蓋錯誤。
- 實作 `IDisposable` 之資源須以 `using` 陳述式管理，確保例外拋出時資源仍正確釋放。
- 禁止使用空的 `catch { }` 區塊吞噬所有例外而不記錄或重新拋出；`catch (Exception)` 廣泛捕捉須附上明確理由。
- 例外僅用於例外狀況，禁止作為正常流程控制手段（例如以例外處理迴圈跳出）。

**理由**：顯式錯誤處理搭配 `using` 資源管理可避免資源洩漏與錯誤狀態擴散。

---

### VI. Input Validation at Boundaries (邊界輸入驗證)

- 所有外部輸入（HTTP 請求、使用者輸入、設定檔、外部服務回應）進入控制器（Controller）或公開方法邊界時，須完成型別、範圍與格式驗證（例如 Data Annotations、`FluentValidation`）。
- 禁止信任任何未經驗證的反序列化物件；驗證失敗須拒絕處理並回傳明確錯誤（例如 `400 Bad Request`）。
- 已於邊界驗證之資料在內部服務間傳遞時，禁止重複進行相同驗證造成邏輯冗贅。

**理由**：邊界驗證阻絕不可信資料流入核心業務邏輯，降低注入與例外風險。

---

### VII. Assertions & Preconditions (斷言與前置條件)

- 方法前置條件須以 `ArgumentNullException.ThrowIfNull`、`ArgumentException` 或 `Debug.Assert` 明確表達，用於偵測程式邏輯錯誤。
- `Debug.Assert` 僅用於偵測不應發生之程式錯誤，禁止用於處理可預期的執行期錯誤（例如使用者輸入格式錯誤）。
- 關鍵安全性檢查禁止完全依賴僅於 Debug 組態生效之 `Debug.Assert`；正式環境（Release）須以顯式例外檢查取代。

**理由**：斷言與防護子句將隱性假設轉換為可執行檢查，及早暴露邏輯錯誤。

---

### VIII. Immutability & Minimized Side Effects (不變性與最小化副作用)

- 優先使用 `record` 型別、`readonly` 欄位與 `init` 存取子建立預設不可變之資料結構。
- 唯讀存取參數優先使用 `in` 參數修飾詞或不可變集合介面（`IReadOnlyList<T>`、`IReadOnlyDictionary<TKey, TValue>`）避免不必要的複製與非預期修改。
- 避免使用可變（mutable）靜態欄位與全域狀態；必要之副作用須於方法命名或 XML 文件註解明確標示。

**理由**：預設不可變降低狀態追蹤複雜度，並減少多執行緒環境下的競態風險。

---

### IX. Consistent Formatting & Structure (一致的格式與結構)

- 專案須以 `.editorconfig` 統一縮排、換行與命名規則，並以 `dotnet format` 或 Roslyn 分析器（Analyzer）自動強制執行。
- 每個檔案僅定義單一公開類別、介面或列舉，檔案名稱須與型別名稱一致。
- 命名空間結構須對應資料夾結構，禁止同一方案內混用不同組織風格。

**理由**：一致格式與結構降低跨檔案閱讀與程式碼審查成本。

---

### X. Boy Scout Rule (童子軍原則)

- 每次修改程式碼時，須讓其比修改前更清晰整潔，禁止在既有混亂基礎上疊加新的混亂。
- 修改程式碼時發現的編譯器警告與可為 Null 參考型別（Nullable Reference Types）警告須一併處理，禁止留下已知但未修復的警告。
- 發現技術債務須記錄或於能力範圍內即時修正，不得無限期擱置。

**理由**：持續性微幅改善避免程式碼腐化累積至無法維護的臨界點。

## Design Constraints

### I. Single Responsibility Principle (SRP)

- 每個類別對應單一職責，並以獨立檔案組織；當類別（尤其是 Controller、Service）同時承擔多項職責時，須拆分為獨立類別。
- 局部類別（`partial class`）僅用於分離產生器（Generator）產出程式碼與手寫邏輯，禁止用於規避單一職責原則。

**理由**：單一職責使變更範圍可控，避免修改一處邏輯連帶影響無關功能。

---

### II. Open/Closed Principle (OCP)

- 擴展須透過介面實作、虛擬方法覆寫（`virtual`/`override`）或擴充方法（Extension Method）達成，禁止直接修改已穩定且被多處引用之公開類別。
- 不預期被繼承之類別須標記 `sealed`，明確表達封閉修改之邊界。

**理由**：降低修改已驗證程式碼所帶來的回歸風險，使系統可持續擴展。

---

### III. Liskov Substitution Principle (LSP)

- 衍生類別覆寫（`override`）方法時，不得強化前置條件或削弱後置條件，且不得拋出基底型別未宣告之例外類型。
- 禁止以拋出 `NotImplementedException` 的方式覆寫基底類別或介面方法；若行為無法一致替代，須以組合（Composition）取代繼承。
- 泛型型別參數之變異數（Variance，`in`/`out`）須正確標示，避免子型別替換時產生型別不安全操作。

**理由**：確保多型呼叫的行為一致性，避免呼叫端因型別替換產生隱性執行期錯誤。

---

### IV. Interface Segregation Principle (ISP)

- 介面須依使用方角色拆分為小型介面（例如 `IReadRepository<T>`、`IWriteRepository<T>`），禁止建立强迫實作方實作不需要方法之大型介面。
- 當介面方法數超過 5 個時，須評估是否應以顯式介面實作（Explicit Interface Implementation）或拆分角色介面因應。

**理由**：細粒度介面使依賴關係精確，降低不必要的耦合。

---

### V. Dependency Inversion Principle (DIP)

- 高層模組（Controller、Service）須依賴抽象介面，禁止直接依賴低層模組之具體實作類別。
- 依賴注入須透過建構子注入，並以內建相依性注入容器（`Microsoft.Extensions.DependencyInjection`）註冊介面與實作對應，禁止於業務邏輯內部以 `new` 直接實例化具體依賴。

**理由**：依賴反轉使高層邏輯可於不修改的情況下替換底層實作，提升可測試性與可替換性。

---

### VI. High Cohesion, Low Coupling

- 相關類別須依功能模組組織於相同命名空間與資料夾；模組間依賴關係須最小化。
- 跨組件（Assembly）存取僅能透過公開介面；內部實作類別須標記 `internal` 限制存取範圍。
- 禁止跨模組直接存取其他模組之內部欄位或私有狀態。

**理由**：高內聚確保變更影響範圍可預測；低耦合確保模組可獨立替換、測試與部署。

---

### VII. Separation of Concerns (SoC)

- 資料存取層（Repository）、業務邏輯層（Service）、呈現層（Controller/View）須實體分離，禁止於 Controller 或 Razor View 中直接撰寫業務邏輯或資料存取程式碼。
- 跨切面關注點（日誌記錄、例外處理、驗證）須以 ASP.NET Core Middleware 或 Action Filter 實作，禁止散佈於業務程式碼各處。

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
