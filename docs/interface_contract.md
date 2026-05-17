# Interface Contract

本文件用于约束后续对 `cminus-lexer-lab` 的修改，尤其是后续 Codex 会话或协作者进行扩展时，避免破坏模块边界和公共接口。

## 1. 稳定公共入口

默认稳定入口保持为：

```cpp
cminus::Lexer lexer;
cminus::LexResult result = lexer.tokenize(source);
```

约束如下：

- 保留 `namespace cminus`
- 保留 `class Lexer`
- 保留 `LexResult Lexer::tokenize(const std::string& source)`
- 默认不改变 `LexResult` 的已有字段语义

## 2. 向后兼容优先

即使未来从 C-- 扩展到 C++ 或其他语言，也优先保持以下逻辑不变：

- 调用模式不变
- 返回结果的基本组织不变
- `Token` 仍然保留 `lexeme / type / grammar / attr / line / column`
- `Diagnostic` 仍然保留结构化错误信息能力

允许的扩展方式：

- 新增可选字段
- 新增辅助 API
- 新增实验性工具程序
- 新增语言配置或规则集

默认避免的变更：

- 重命名 `Lexer`
- 改写 `tokenize` 的返回类型
- 为了实验方便把 parser / AST / IR 依赖重新引入公共头

## 3. 模块边界

`include/`、`src/`、`tools/` 中不应出现对以下模块的实际依赖：

- parser
- AST
- IR
- live editor
- `third_part/compiler_ir`

如果未来需要与上游编译器集成，应由上游适配当前 lexer 模块，而不是反向把本模块重新耦合回去。

## 4. 词法规则变更原则

当前阶段默认不主动改变以下内容：

- token 输出语义
- 关键字 / 运算符 / 分隔符编码
- 最长匹配行为
- 现有诊断代码名

如果未来要研究新方法，应优先：

- 新增实现分支
- 保留基线实现可运行
- 明确记录行为差异

## 5. 文档同步要求

以下变更发生时，必须同步更新文档：

- 公共 API 变更：更新本文件和 `README.md`
- 研究路线调整：更新 `docs/research_plan.md`
- 抽离边界变化：更新 `docs/extraction_notes.md`

## 6. 默认决策

当后续会话遇到“为了方便修改接口”与“保持接口稳定”之间的冲突时，默认选择保持接口稳定，除非有明确需求要求破坏兼容性。
