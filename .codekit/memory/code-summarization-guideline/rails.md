# Rails Guideline

Ruby on Rails ( Rails ) 為基於 Ruby 程式語言之伺服器端網頁應用程式框架，採用模型-視圖-控制器架構型態 ( MVC, Model-View-Controller )，特徵包含慣例優於設定 ( Convention over Configuration )、ActiveRecord 物件關聯對映 ( ORM )、路由 ( Routing ) 宣告式設定、回呼機制 ( Callback )、關注點模組 ( Concern )、遷移檔 ( Migration ) 資料庫版本控管。

## Code Rules

### I. 意圖提升 (Intent Elevation / What over How)

摘要禁止使用 `do`／`end`、`if`／`unless`、`each`、`return` 等 Ruby 關鍵字或方法作為摘要動詞，除非該操作本身即為使用者可觀察之行為。控制器 ( Controller ) 之 Action 方法摘要以其對應之 HTTP 請求業務目的為主軸，禁止逐行描述 `render`／`redirect_to` 呼叫順序。ActiveRecord 回呼 ( `before_save`、`after_create` 等 ) 摘要以其觸發時機所達成之業務效果為主軸，禁止描述回呼註冊語法本身。宣告式驗證與範圍方法 ( `validates`、`scope` ) 摘要以其約束或篩選之業務規則為主軸。

例：摘要為「驗證輸入範圍」，而非「若 `x < 0` 則回傳 `false`，否則檢查 `x > max` 並回傳對應布林值」。

### II. 去噪與抽象化 (De-noising and Abstraction)

摘要排除 `require`／`require_relative`、gem 引入宣告、ActiveSupport 語法糖（如 `present?`、`blank?`）之逐句描述。摘要排除 `rescue_from` 樣板化錯誤處理與樣板化之 Strong Parameters 過濾邏輯，除非其決定業務結果。ActiveRecord 查詢鏈 ( `where`、`joins`、`includes` 等 ) 收斂為單一抽象查詢操作，禁止逐一列舉鏈中各方法。巢狀關注點模組 ( Concern ) 或巢狀區塊 ( `each_with_object` 等 )，摘要為其最外層抽象目的，內層細節僅於必要時展開。

### III. 語意分塊 (Semantic Chunking)

切分邊界依循模型 ( Model )、控制器 ( Controller )、關注點 ( Concern )、服務物件 ( Service Object )、背景工作 ( Job ) 之自然邊界，禁止以固定行數切分單一檔案。標示為 `private`／`protected` 之輔助方法，其摘要併入呼叫者之摘要範圍，不個別產出摘要。MVC 跨檔案共同完成單一功能之呼叫鏈（路由、控制器、模型、視圖），辨識其呼叫鏈後產出涵蓋整體流程之摘要，並標註各分塊於流程中之角色。透過 Concern 混入 ( `include` ) 多個模型共用之邏輯，視為獨立語意區塊，並標註其被混入之模型範圍。

### IV. 領域詞彙映射 (Domain Vocabulary Mapping)

摘要禁止直接沿用 Rails／Ruby 識別字（如底線前綴之慣例私有方法、複數形資料表命名）作為摘要用詞，除非該識別字已是領域詞彙。領域詞彙之映射依據模型關聯命名（`has_many`、`belongs_to`）、路由命名（`resources`）、測試案例（RSpec／Minitest）命名，禁止臆測未出現於程式碼上下文之業務語意。ActiveRecord 關聯方法或 Rails 慣例命名（如 `current_user`）與領域詞彙產生歧義時，標註為待釐清事項。摘要中對同一領域概念，於同一文件內固定使用單一詞彙，不因程式碼中出現多個同義識別字而交替使用不同摘要詞彙。

## Interpreting Constraints

ActiveRecord 回呼 ( Callback，如 `before_save`、`after_commit` ) 之觸發時機語意須標註，不得省略。

```ruby
before_save :normalize_email

def normalize_email
  self.email = email.downcase
end
```
摘要：「儲存前將電子郵件正規化為小寫」。

Strong Parameters (`params.require(...).permit(...)`) 須標註其為輸入白名單過濾機制，不得與業務邏輯合併摘要。

```ruby
def user_params
  params.require(:user).permit(:name, :email)
end
```
摘要：「限定使用者可寫入之姓名與電子郵件欄位」。

路由宣告 (`resources`、`member`、`collection`) 之摘要須標註其對應之 RESTful 資源與 HTTP 動詞語意，不得逐行描述 DSL 語法本身。

```ruby
resources :orders, only: [:index, :show]
```
摘要：「開放訂單清單與單筆查詢之唯讀路由」。

ActiveRecord 關聯宣告 (`has_many`、`belongs_to`、`has_one`) 須標註其資料模型之關聯語意（一對多、多對一等），不得省略。

```ruby
class Order < ApplicationRecord
  belongs_to :customer
  has_many :line_items
end
```
摘要：「訂單歸屬單一顧客並包含多筆訂單明細」。

背景工作 ( Active Job，如 `perform_later` ) 須標註其非同步執行語意，不得摘要為同步呼叫。

```ruby
NotifyUserJob.perform_later(user.id)
```
摘要：「非同步排程通知使用者之背景工作」。

## Governance

本細則依循程式摘要憲章 (`.codekit/memory/constitution/code-summarization.md`) 之四項核心原則衍生，任一條目與憲章原則牴觸時，以憲章為準。修訂程序：條目之新增、刪除或重新定義，須標示異動對應之核心原則編號與差異內容。版本控制依循語意化版本規則：主要版本對應本細則治理規則或條目之不相容變更；次要版本對應新增條目或章節、或既有條目之大幅擴充；補丁版本對應文字澄清、錯字修正、非語意性修訂。合規性審查：Rails 程式碼摘要產出前，須逐項核對本細則之 Code Rules 與 Interpreting Constraints，未通過核對之摘要不得視為最終產出。

**Version**: 1.0.0 | **Ratified**: 2026-07-13 | **Last Amended**: 2026-07-13
