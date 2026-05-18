from pathlib import Path
Path(__file__).resolve().parents[1].joinpath("generated","cminus_switch_lexer.cpp").write_text(
    "// generated prototype hook for switch-based DFA\n"
)
