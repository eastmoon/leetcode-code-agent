---
name: "codekit-code-summarization-constitution"
description: 程式碼工具，用於生成程式碼摘要憲章文件。
user-invocable: true
disable-model-invocation: false
---

## 任務

<requirement>
  請基於 **程式理解 ( Program Comprehension )**、**軟體逆向工程 ( Software Reverse Engineering )**、**程式碼摘要 ( Source Code Summarization )** 詳細解釋，並羅列包括 **意圖提升 (Intent Elevation / What over How)**、**去噪與抽象化 (De-noising and Abstraction)**、**語意分塊 (Semantic Chunking)**、**領域詞彙映射 (Domain Vocabulary Mapping)** 原則，彙整成摘要原則，並寫入憲章文件 code-summarization.md 檔案。
</requirement>

+ 讀取憲章生成工具 `.cluade/skills/codekit-generator-constitution/SKILL.md`。
+ 以 requirement 為輸入執行憲章生成工具。
