# Rails Guideline

Ruby on Rails（以下簡稱 Rails）是一款採用 Ruby 程式語言、遵循 MVC（Model-View-Controller）架構模式的伺服器端 Web 應用程式框架，以「慣例優於配置（Convention over Configuration）」與「不要重複自己（DRY, Don't Repeat Yourself）」為核心設計哲學，透過 ActiveRecord、ActionController、ActionView 等元件提供資料存取、請求處理與畫面呈現的整合式開發架構。

## Coding Rules

### I. Meaningful Naming（有意義的命名）

- Model 命名為單數名詞的 CamelCase（如 `User`、`Order`），對應資料表命名為複數 snake_case（如 `users`、`orders`）；Controller 命名為複數名詞加 `Controller` 後綴（如 `UsersController`）。
- 方法、變數、資料庫欄位一律使用 snake_case，禁止於 Ruby 程式碼中使用駝峰式命名（camelCase）。
- 布林方法（回傳 `true`/`false`）須以 `?` 結尾（如 `valid?`、`active?`）；具破壞性或會拋出例外的方法須以 `!` 結尾（如 `save!`、`update!`）。
- 關聯（association）名稱須與對應 Model 名稱呼應（如 `belongs_to :user` 對應 `User` Model），同一概念於整個程式碼庫須使用一致詞彙。

**理由**：清晰且符合 Rails 慣例的命名降低理解成本，並使框架自動推導（如路由、資料表對應）得以正確運作。

---

### II. Small, Single-Purpose Methods（小型單一目的方法）

- 方法須只做一件事；Controller action 應保持精簡（建議不超過 10 行），複雜業務邏輯須移至 Model、Service Object 或 Concern。
- 參數個數超過 3 個須以 Hash 或關鍵字參數（keyword arguments）封裝，並評估抽出為獨立的 PORO（Plain Old Ruby Object）。
- 巢狀條件（`if`/`unless` 巢狀）超過 2 層須以衛語句（Guard Clause，如 `return if`）或抽取私有方法重構。

**理由**：小型方法易於理解、測試與重用，並符合「瘦 Controller、瘦 Model」的 Rails 慣例，避免邏輯集中於單一巨大方法。

---

### III. Self-Documenting Code Over Comments（自我說明優先於註解）

- 方法與變數命名須清楚表達意圖；除解釋「為何」之非顯而易見決策外，禁止撰寫描述「做什麼」的註解。
- 禁止保留被註解掉的程式碼（dead code）；Rails 產生器（generator）產生的預設樣板註解若無實質內容須清除。
- RDoc/YARD 文件註解僅用於公開 API 或共用 gem 介面，內部私有方法不強制要求。

**理由**：程式碼是唯一不會過期的文件；註解容易與實作行為脫節，造成誤導。

---

### IV. No Duplication（DRY, Don't Repeat Yourself）

- 重複邏輯須抽取為 Concern（`app/models/concerns`、`app/controllers/concerns`）、Service Object 或 Helper。
- View 中重複的畫面片段須抽取為 Partial（`_partial.html.erb`）並以 `render` 呼叫；重複的查詢邏輯須抽取為 Model Scope（`scope :active, -> { where(active: true) }`）。
- 驗證規則、常數須集中於 Model 或 `config/initializers`，禁止於多處硬編碼（hard code）相同數值。

**理由**：Rails 以 DRY 為核心哲學之一，重複邏輯造成維護時多處修改風險，容易產生不一致缺陷。

---

### V. Fail Fast & Explicit Error Handling（快速失敗與顯式錯誤處理）

- 需要明確失敗語意的流程（如背景任務、Rake Task）須使用會拋出例外的方法（`save!`、`create!`、`update!`）；面向使用者的表單流程使用 `save`／`update` 並檢查回傳值，透過 `errors` 物件呈現驗證訊息。
- 禁止使用空的 `rescue` 區塊吞噬例外（如 `rescue => e; end`）；例外處理須明確記錄（`Rails.logger`）或重新拋出。
- 自訂例外類別須繼承 `StandardError`，禁止直接 `rescue Exception`。

**理由**：儘早暴露錯誤可縮小除錯範圍，避免無效資料因例外被靜默吞噬而流入資料庫。

---

### VI. Input Validation at Boundaries（邊界輸入驗證）

- 所有外部輸入須經 Strong Parameters（`params.require(...).permit(...)`）過濾，禁止直接使用未過濾的 `params` 寫入資料庫。
- Model 層須以 ActiveRecord Validations（如 `validates :name, presence: true`）確保資料完整性，不得僅依賴前端或 Controller 驗證。
- 已於 Model 層驗證過的資料，於 Service Object 或其他內部模組間傳遞時，禁止重複進行相同驗證造成邏輯冗贅。

**理由**：邊界驗證阻絕不可信資料流入核心邏輯，並防止大量賦值（Mass Assignment）等注入風險。

---

### VII. Assertions & Preconditions（斷言與前置條件）

- 關鍵方法之前置條件須以明確檢查表達（如 Guard Clause 搭配 `raise ArgumentError`），用以偵測程式內部邏輯錯誤。
- 前置條件檢查禁止用於處理可預期的使用者輸入錯誤，該情境須改用第 VI 條之 Validation 機制。
- 正式環境（Production）建置不得移除關鍵前置條件檢查；測試程式碼中之期望值驗證另由 RSpec/Minitest 等測試框架之斷言語法（`expect`、`assert`）負責。

**理由**：明確的前置條件檢查將隱性假設轉換為可執行的檢查，使違反假設的狀態立即可見。

---

### VIII. Immutability & Minimized Side Effects（不變性與最小化副作用）

- 常數須以 `freeze` 凍結（如 `STATUSES = %w[active inactive].freeze`），避免執行期被意外修改。
- 方法應避免直接修改傳入參數；需要轉換資料時，優先使用回傳新物件的方法（如 `map`、`each_with_object`）而非會改變原陣列的破壞性方法（如 `map!`）。
- Model 的 Callback（`before_save`、`after_create` 等）須避免產生難以追蹤的隱性副作用；跨 Model 的狀態變更應改以 Service Object 明確表達。

**理由**：不變性與最小副作用降低狀態追蹤複雜度，避免 Callback 連鎖反應造成難以預期的資料變化。

---

### IX. Consistent Formatting & Structure（一致的格式與結構）

- 專案須採用 RuboCop 作為統一格式化與風格檢查工具，並強制執行於 CI。
- 縮排統一為 2 個空格，禁止使用 Tab；字串預設使用單引號，僅在需要插值（interpolation）時使用雙引號。
- 檔案結構須遵循 Rails 慣例目錄（`app/models`、`app/controllers`、`app/views`、`app/services` 等），禁止任意調整目錄語意或偏離慣例路徑。

**理由**：一致格式與慣例目錄結構降低視覺解析成本，並使團隊成員與框架工具（如自動載入 Autoloading）行為一致。

---

### X. Boy Scout Rule（童子軍原則）

- 修改既有檔案時，須同步修正明顯違反本指南的程式碼（如過長方法、重複邏輯），但不得擴大變更範圍至無關功能。
- 發現技術債務須以 `# TODO` 註明並記錄於議題追蹤系統，不得無限期擱置且不留下任何紀錄。

**理由**：持續性微幅改善避免程式碼腐化累積至無法維護的臨界點。

---

## Design Constraints

### I. Single Responsibility Principle (SRP)

- 每個 Model、Controller、Service Object 只能有一個引發變更的原因；Controller 不得包含業務邏輯，僅負責接收請求、呼叫 Model 或 Service、回傳回應。
- 當 Model 同時處理資料驗證、業務規則與外部服務呼叫等多重職責時，須拆分為 Concern 或獨立 Service Object。
- 單一方法超過 30 行，須檢視是否違反單一職責並評估拆分為私有方法或獨立類別。

**理由**：單一職責使變更範圍可控，避免修改一處邏輯連帶影響無關功能。

---

### II. Open/Closed Principle (OCP)

- 既有 Model、Service 對擴展開放、對修改封閉；新需求優先透過 Concern、Module 混入（mixin）、Decorator 或 Strategy Pattern 擴展，不得直接修改已上線且經過測試的核心邏輯。
- 修改既有已驗證的 Model 驗證規則或 Callback 行為，須附上充分理由與回歸測試佐證。

**理由**：降低修改已驗證程式碼所帶來的回歸風險，使系統可持續擴展。

---

### III. Liskov Substitution Principle (LSP)

- 使用 STI（Single Table Inheritance）時，子類別必須可完整替代父類別使用，且不改變程式正確性；子類別禁止覆寫父類別方法後產生不相容的回傳型別或副作用。
- 若繼承導致行為分歧過大（如子類別大量以 `is_a?` 判斷型別分支處理），須以組合（Composition）或委派（`delegate` 方法）取代繼承。

**理由**：確保多型行為的一致性，防止呼叫端因替換子型別而產生隱性執行期錯誤。

---

### IV. Interface Segregation Principle (ISP)

- Concern 與 Module 須依使用情境拆分，禁止建立巨大的通用 Concern 強迫所有引入的 Model 或 Controller 實作不需要的方法。
- 當一個 Concern 對外暴露的公開方法超過 5 個，須評估拆分為多個職責更單一的 Concern。

**理由**：細粒度 Concern 使依賴關係精確，降低不必要的耦合與非預期的方法污染（method pollution）。

---

### V. Dependency Inversion Principle (DIP)

- Service Object、Controller 不得直接依賴外部服務（如第三方 API Client）的具體實作類別；須透過可替換的抽象（Ruby 中以 Duck Typing 或明確定義的抽象類別表達）注入依賴。
- 外部串接（如金流、郵件、推播）須以 Adapter 或 Gateway 物件封裝，並透過建構子注入（如 `def initialize(gateway: DefaultGateway.new)`），禁止在 Service 內部直接以硬編碼方式實例化具體外部客戶端。

**理由**：依賴反轉使高層邏輯可在不修改的情況下替換底層實作，提升可測試性與可替換性。

---

### VI. High Cohesion, Low Coupling（高內聚、低耦合）

- 每個 Model、Controller、Service Object 僅負責單一明確功能群組；跨模組溝通僅透過公開方法或明確定義的介面（如 Service Object 的 `call` 方法）。
- 禁止跨 Model 直接存取彼此的內部狀態；所有跨模組存取須透過公開的 Model 方法或關聯（association）。
- 新增功能時，須優先評估是否歸屬於現有 Concern 或 Service，而非建立新的跨模組直接依賴。

**理由**：高內聚確保變更影響範圍可預測；低耦合確保模組可獨立替換、測試與部署。

---

### VII. Separation of Concerns (SoC)

- 嚴格遵循 MVC 分層：Model 負責資料與業務規則、View 負責呈現、Controller 負責流程調度，三者不得混合（禁止在 View 中撰寫查詢邏輯，禁止在 Controller 中撰寫複雜業務運算）。
- 路由（`config/routes.rb`）、驗證（Model Validations）、日誌（`Rails.logger`）須各自獨立管理，不得嵌入無關業務邏輯之中。
- 跨切面關注點（如 Logging、身份驗證 Authentication、快取 Caching）須以 Rack Middleware、Controller 的 `before_action`／`around_action` 或 Concern 實作，禁止散佈於各 Controller、Model 內重複撰寫。

**理由**：關注點分離使各層可獨立演進，降低連鎖修改風險，並符合 Rails MVC 架構的核心設計假設。

---

## Compliance Requirements

- 所有程式碼審查（Code Review）須逐一驗證上述 Coding Rules 與 Design Constraints 之遵守情況。
- 違反原則須在 PR 描述中列出具體理由，並獲得維護者明確核准方可合併。
- RuboCop、Reek 等靜態分析工具設定須與本指南保持一致，並於 CI 中強制執行。
- 新增或修改的邊界輸入處理程式碼（Strong Parameters、Validations），須附帶對應的驗證與例外處理測試案例（RSpec/Minitest）。

---

## Governance

- 本指南依據《程式指南憲章》與《程式設計憲章》制定，凌駕於 Rails 專案內其他非正式撰寫慣例。
- 指南修訂須記錄變更原因、影響範圍及遷移計畫，並由專案維護者核准後方可生效。
- 版本控制遵循語意版本規則：
  - 主要版本（MAJOR）：治理與原則發生不可兼容或重新定義的變更。
  - 次要版本（MINOR）：新增原則或章節，或大幅擴展與補充具體指導方針。
  - 補丁版本（PATCH）：措詞澄清、拼字錯誤修復、非語意改進。
- 合規性審查於每次里程碑（Milestone）結束時執行。

**Version**: 1.0.0 | **Ratified**: 2026-07-04 | **Last Amended**: 2026-07-04
