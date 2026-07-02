# C# Guideline

C# 為 Microsoft 開發之靜態型別、物件導向程式語言，運行於 .NET 執行環境（CLR），支援介面、泛型、委派、非同步（async/await）、LINQ 與可為 Null 參考型別（Nullable Reference Types）等語言特性。

## Coding Rules

### I. Meaningful Naming (有意義的命名)

- 類別（class）、介面（interface）、列舉（enum）與方法命名須使用 PascalCase，並揭示意圖，禁止使用單字母、縮寫或無意義代稱（如 `Data`、`Tmp`、`Mgr`）。
- 區域變數與參數命名須使用 camelCase；私有欄位（private field）命名須以 `_` 為前綴並使用 camelCase（如 `_orderCount`）。
- 介面命名須以 `I` 為前綴（如 `IRepository`）；類別命名為名詞或名詞片語，方法命名為動詞或動詞片語。
- 同一概念於整個程式碼庫須使用一致詞彙，禁止對同一事物使用多個不同名稱（如同時使用 `Get`、`Fetch`、`Retrieve` 表示相同行為）。

**理由**：清晰命名降低理解成本，減少因命名歧義導致的誤用與缺陷。

---

### II. Small, Single-Purpose Functions (小型單一目的方法)

- 方法（method）須只做一件事，混合多層抽象之方法須拆分為私有方法（private method）。
- 參數個數超過 3 個須以參數物件（Parameter Object）或 `record` 封裝取代。
- 巢狀層級（if/for 巢狀）超過 2 層須改寫為衛語句（Guard Clause）或抽取子方法。

**理由**：小型方法易於理解、單元測試與重用，降低認知負擔。

---

### III. Self-Documenting Code Over Comments (自我說明優先於註解)

- 程式碼須透過命名與結構表達意圖；XML 文件註解（`///`）僅用於說明公開 API 的「為何」而非「做什麼」。
- 禁止保留註解掉的程式碼（commented-out code）、過時註解或與實作行為不一致的註解。
- 禁止使用註解彌補命名不良或結構混亂的程式碼。

**理由**：程式碼是唯一不會過期的文件；註解易與實作脫節，造成誤導。

---

### IV. No Duplication (DRY, Don't Repeat Yourself)

- 相同邏輯禁止複製貼上；重複出現兩次以上的邏輯須抽取為共用方法、擴充方法（Extension Method）或共用服務類別。
- 常數須以 `const` 或 `static readonly` 定義於單一來源，禁止於多處硬編碼相同字面值（Magic String/Number）。
- 業務規則須有單一權威來源，禁止於多個類別重複實作相同規則。

**理由**：重複邏輯造成維護時多處修改風險，容易產生不一致缺陷。

---

### V. Fail Fast & Explicit Error Handling (快速失敗與顯式錯誤處理)

- 偵測到不合法狀態或非預期輸入，須立即以 `throw` 拋出例外（如 `ArgumentException`、`InvalidOperationException`），禁止以空的 `catch` 區塊靜默吞噬例外。
- 禁止回傳 `null` 掩蓋錯誤；優先啟用可為 Null 參考型別（Nullable Reference Types，`<Nullable>enable</Nullable>`），或改用例外、`Result<T>` 型別明確表達失敗狀態。
- 例外（Exception）僅用於例外狀況，禁止以 `try/catch` 作為正常流程控制手段（如以例外取代迴圈跳出邏輯）。

**理由**：儘早暴露錯誤可縮小除錯範圍，避免錯誤狀態擴散至系統其他部分。

---

### VI. Input Validation at Boundaries (邊界輸入驗證)

- 所有外部輸入（HTTP 請求、API 回應、檔案內容、環境變數）進入公開方法（public method）或 API 端點（Controller Action）時，須完成型別、範圍、格式驗證。
- 公開方法之參數驗證須以 `ArgumentNullException.ThrowIfNull`、`ArgumentException` 或 Guard Clause 於方法開頭明確表達，禁止信任任何未經驗證之外部資料。
- 已於邊界驗證之資料在內部方法（private/internal method）間傳遞時，禁止重複進行相同驗證造成邏輯冗贅。

**理由**：邊界驗證阻絕不可信資料流入核心邏輯，降低注入與崩潰風險。

---

### VII. Assertions & Preconditions (斷言與前置條件)

- 方法對於前置條件、後置條件、不變量須以 `Debug.Assert` 或明確條件判斷式表達。
- `Debug.Assert` 僅用於偵測程式錯誤（Bug），禁止用於處理可預期的執行期錯誤（如使用者輸入錯誤）；`Debug.Assert` 於 Release 建置會被移除，關鍵檢查須改以明確例外（Exception）實作。
- 正式環境（Release）建置須保留關鍵前置條件檢查，禁止完全移除防護。

**理由**：斷言將隱性假設轉換為可執行的檢查，使違反假設的狀態立即可見。

---

### VIII. Immutability & Minimized Side Effects (不變性與最小化副作用)

- 資料結構優先使用 `record`、`record struct` 或具 `init` 存取子（accessor）之屬性，取代可變（mutable）類別。
- 欄位預設宣告為 `readonly`；方法禁止修改輸入參數或靜態（static）欄位所代表之全域狀態。
- 對外暴露集合須使用 `IReadOnlyList<T>`、`IReadOnlyCollection<T>` 或 `ImmutableArray<T>`，禁止直接暴露 `List<T>` 等可變集合。
- 共享狀態之存取須以 `lock` 或並行集合（Concurrent Collection）最小化競態風險。

**理由**：不變性與最小副作用降低狀態追蹤複雜度，提升可測試性與並行安全性。

---

### IX. Consistent Formatting & Structure (一致的格式與結構)

- 專案須以 `.editorconfig` 統一縮排、換行與大括號位置規則，並以 Roslyn Analyzer 或 StyleCop 強制執行。
- `using` 指示詞（using directive）排序須一致（System 命名空間優先），並移除未使用之 `using`。
- 檔案、資料夾與命名空間（namespace）結構須一致對應（如 `Namespace.Folder.ClassName`），禁止同一專案內混用不同組織慣例。

**理由**：一致格式降低視覺解析成本，使程式碼審查聚焦於邏輯而非風格差異。

---

### X. Boy Scout Rule (童子軍原則)

- 每次修改程式碼時，須讓其比修改前更清晰整潔，禁止在既有混亂基礎上疊加新的混亂。
- 發現技術債務（Technical Debt）須以 `// TODO:` 標記並記錄追蹤事項，或於能力範圍內即時修正，不得無限期擱置。

**理由**：持續性微幅改善避免程式碼腐化累積至無法維護的臨界點。

## Design Constraints

### I. Single Responsibility Principle (SRP)

- 每個類別（class）或方法只能有一個引發變更的原因。
- 當一個類別同時承擔多於一項職責時（如同時處理資料存取與業務邏輯），須立即拆分為獨立類別。
- 方法本體超過 30 行，須檢視是否違反單一職責並評估拆分。

**理由**：單一職責使變更範圍可控，避免修改一處邏輯連帶影響無關功能。

---

### II. Open/Closed Principle (OCP)

- 既有類別對擴展開放、對修改封閉；新需求須透過介面（interface）、抽象類別（abstract class）或策略模式（Strategy Pattern）擴展，不得直接修改已穩定的核心類別。
- 不預期被繼承之類別須以 `sealed` 修飾，明確表達封閉狀態；擴展須以組合（Composition）或擴充方法（Extension Method）實作。
- 任何修改既有已驗證類別行為之變更，須附上充分理由與影響評估。

**理由**：降低修改已驗證程式碼所帶來的回歸風險，使系統可持續擴展。

---

### III. Liskov Substitution Principle (LSP)

- 衍生類別（derived class）須可完整替代基底類別（base class）或介面使用，且不改變程式正確性。
- 覆寫（override）方法禁止削弱基底類別之前置條件，亦不得強化後置條件；禁止於覆寫方法中拋出 `NotImplementedException` 破壞契約。
- 若繼承導致行為不一致或違反基底型別契約，須以組合取代繼承。

**理由**：確保多型行為的一致性，防止呼叫端因替換衍生型別而產生隱性執行期錯誤。

---

### IV. Interface Segregation Principle (ISP)

- 介面（interface）須依使用方需求拆分；禁止建立大型通用介面，強迫實作類別實作不需要之方法。
- 當介面方法數超過 5 個時，須評估是否應拆分為多個角色介面（如將 `IRepository` 拆分為 `IReadableRepository`、`IWritableRepository`）。

**理由**：細粒度介面使依賴關係精確，降低不必要的編譯期與執行期耦合。

---

### V. Dependency Inversion Principle (DIP)

- 高層模組（如 Service）不得直接依賴低層模組（如 Repository）之具體實作；雙方均須依賴抽象（interface）。
- 依賴注入（Dependency Injection，透過建構子注入）為標準實踐；禁止在業務邏輯類別內部以 `new` 直接實例化具體依賴。
- 抽象層（interface）定義於高層模組所在之命名空間，由低層模組實作該抽象。

**理由**：依賴反轉使高層邏輯可在不修改的情況下替換底層實作，提升可測試性與可替換性。

---

### VI. High Cohesion, Low Coupling (高內聚低耦合)

- 每個類別或命名空間（namespace）僅負責單一明確的功能群組，相關邏輯須集中於同一單元內。
- 類別間依賴關係須最小化；跨命名空間溝通僅能透過公開介面（public interface）進行。
- 內部實作細節須以 `internal` 或 `private` 存取修飾詞封裝，禁止跨類別直接存取內部狀態。
- 新增功能時，須優先評估是否歸屬於現有類別或命名空間，而非建立新的跨模組依賴路徑。

**理由**：高內聚確保變更影響範圍可預測；低耦合確保模組可獨立替換、測試與部署。

---

### VII. Separation of Concerns (SoC)

- 資料存取層（Repository / DbContext）、業務邏輯層（Service）、呈現層（Controller / View）須分屬不同類別與命名空間，不得混合於同一類別。
- 每個層次僅允許向相鄰層傳遞資料，禁止 Controller 直接呼叫 Repository 或存取 DbContext。
- 設定（Configuration）、路由（Routing）、驗證（Validation）、日誌（Logging）須各自獨立管理，不得嵌入業務邏輯類別中。
- 跨切面關注點（Logging、Security、Caching）須以 Middleware、Action Filter 或 Attribute 實作，禁止散佈於業務邏輯程式碼各處。

**理由**：關注點分離使各層可獨立演進，降低連鎖修改風險，提升可測試性與可維護性。

## Governance

- 本指南凌駕於所有其他 C# 開發慣例與口頭約定之上，適用範圍涵蓋所有以 C# 撰寫之程式碼。
- 指南修訂須記錄變更原因、影響範圍及遷移計畫，並由專案維護者核准後方可生效。
- 版本控制遵循語意版本規則：
  - 主要版本（MAJOR）：原則重新定義或不相容變更。
  - 次要版本（MINOR）：新增原則或章節，或大幅擴展具體指導方針。
  - 補丁版本（PATCH）：措詞澄清、錯字修正、非語意改進。
- 所有程式碼審查（Code Review）須逐一驗證上述 Coding Rules 與 Design Constraints 之遵守情況；違反須於 PR 描述中列出具體理由並獲得維護者核准方可合併。
- 合規性審查於每次里程碑（Milestone）結束時執行。

**Version**: 1.0.0 | **Ratified**: 2026-07-01 | **Last Amended**: 2026-07-01
