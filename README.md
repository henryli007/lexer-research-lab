# lexer-research-lab

从 `c--compiler` 剥离的独立词法分析实验模块，面向词法分析专题学习、实验与论文复现/扩展，避免依赖 parser、AST、IR 或 editor 主流程。

## 项目定位
- 保留 `cminus::Lexer` 公共接口，便于作为上游组件复用
- 只关注词法规则、自动机构造、扫描与诊断，不引入 parser / AST / IR 依赖
- 当前目录可独立编译、运行、维护与扩展

## 当前能力
- 手写 NFA
- NFA 到 DFA
- DFA 最小化
- 最长匹配
- 关键字、标识符、整数、浮点数、运算符、分隔符识别
- `//` 行注释跳过
- `/* ... */` 块注释跳过
- 未闭合注释、非法字符、畸形数字诊断
- token line/column 记录
- automata stats 输出

## Research Methods
- baseline NFA-DFA lexer
- regex derivative lexer demo
- incremental lexing experiment
- property-based testing / fuzzing
- automata visualization

## 目录概览
```text
lexer-research-lab/
|-- README.md
|-- Makefile
|-- include/
|   `-- cminus/
|       |-- common/
|       |   |-- Diagnostic.h
|       |   |-- LexResult.h
|       |   `-- Token.h
|       `-- lexer/
|           |-- automata.h
|           `-- lexer.h
|-- src/
|   `-- lexer/
|       |-- automata.cpp
|       `-- lexer.cpp
|-- tools/
|   `-- lexer_cli.cpp
|-- tests/
|   |-- expected/
|   |   `-- README.md
|   `-- inputs/
|       |-- invalid_malformed_number.sy
|       |-- invalid_unexpected_char.sy
|       |-- invalid_unterminated_comment.sy
|       |-- valid_basic.sy
|       `-- valid_comments.sy
`-- docs/
    |-- extraction_notes.md
    |-- interface_contract.md
    `-- research_plan.md
```

## 公共 API
当前保持原 lexer 的最小公共接口不变：

```cpp
cminus::Lexer lexer;
cminus::LexResult result = lexer.tokenize(source);
```

`LexResult` 结构如下：

```cpp
struct LexResult {
    bool success = false;
    std::vector<Token> tokens;
    std::string errorMessage;
    std::vector<Diagnostic> diagnostics;
};
```

接口兼容性规则见 [docs/interface_contract.md](docs/interface_contract.md)。

## 构建方式
```bash
make
```

跨平台构建推荐：
```bash
python scripts/build.py all
```

## 运行方式
```bash
./build/lexer_cli tests/inputs/valid_basic.sy
```

## 调试方式
```bash
LEXER_STATS=1 ./build/lexer_cli tests/inputs/valid_basic.sy
DIAGNOSTICS_JSON=1 ./build/lexer_cli tests/inputs/invalid_unterminated_comment.sy
```

## How to Run Experiments
```bash
python benchmarks/scripts/generate_corpus.py
python scripts/build.py all
python benchmarks/scripts/run_all_benchmarks.py
python scripts/plot_paper_figures.py
```

## Figures
- `fig1_lexer_throughput`: baseline vs derivative throughput
- `fig2_automata_states`: NFA/DFA/MinDFA state counts
- `fig3_incremental_reuse_rate`: token reuse after edits
- `fig4_incremental_speedup`: speedup over full lexing
- `fig5_property_failures`: fuzzing property failures
- `fig6_diagnostics_distribution`: diagnostic mix on malformed inputs

## 后续研究方向
- 正则表达式系数
- Tagged DFA / TDFA
- 增量词法分析
- DFA 可视化
- property-based testing
- 错误诊断增强

## 相关文档
- [docs/extraction_notes.md](docs/extraction_notes.md)
- [docs/research_plan.md](docs/research_plan.md)
