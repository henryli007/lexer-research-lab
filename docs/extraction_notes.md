# Extraction Notes

## 抽离出的文件

本独立模块从原始 `c--compiler` 中抽离并整理了以下内容：

- `src/lexer/lexer.cpp` -> `src/lexer/lexer.cpp`
- `src/lexer/automata.cpp` -> `src/lexer/automata.cpp`
- `include/c--/lexer/lexer.h` -> `include/cminus/lexer/lexer.h`
- `include/c--/lexer/automata.h` -> `include/cminus/lexer/automata.h`
- `include/c--/common/Token.h` -> `include/cminus/common/Token.h`
- `include/c--/common/Diagnostic.h` -> `include/cminus/common/Diagnostic.h`
- 新建 `include/cminus/common/LexResult.h`
- 新建最小 CLI：`tools/lexer_cli.cpp`
- 新建最小测试输入：`tests/inputs/*`

## 为什么不能直接复制 `Result.h`

原项目中的 `include/c--/common/Result.h` 同时定义了：

- `LexResult`
- `ParseResult`
- `IRResult`

而且它直接依赖：

- `c--/parser/AST.h`

这会把 parser / AST 的依赖链带入词法模块，导致“词法分析独立构建”目标失效。因此这里不直接复制原 `Result.h`，而是只抽出 lexer 真正需要的 `LexResult`，单独整理为 `include/cminus/common/LexResult.h`。

## 为什么不保留 parser / IR / live editor

当前项目目标已经改变：

- 不是继续维护完整课程编译器流水线
- 而是把 lexer 作为独立研究对象

因此不保留 parser、AST、IR、live editor 的原因是：

- 它们不是词法分析研究的必要依赖
- 会增加构建复杂度和头文件耦合
- 会让后续实验、论文复现、原型实现受到原主工程结构束缚
- 会模糊模块边界，不利于长期演化

## 当前独立模块的公共 API

当前对外 API 保持为：

```cpp
namespace cminus {

class Lexer {
public:
    LexResult tokenize(const std::string& source);
};

}
```

典型调用方式：

```cpp
cminus::Lexer lexer;
cminus::LexResult result = lexer.tokenize(source);
```

这个接口是当前与上游集成的稳定边界，后续即使扩展到 C++ 或更多语言，优先保持“调用模式不变、语义渐进扩展”。

## 未来如何继续扩展

建议沿着下面方向演进，而不是重新耦合回原 compiler 项目：

- 在 `include/cminus/common/` 下继续扩展 lexer 专用结果结构
- 在 `src/lexer/` 下增加实验性扫描器实现，保留稳定主入口
- 通过额外 CLI 参数或新工具程序做研究型验证，不污染核心 API
- 如需支持更多语言，优先扩展规则集和 automata 构造，而不是改变 `Lexer::tokenize` 调用方式
- 将接口和边界规则持续记录在 `docs/interface_contract.md`
