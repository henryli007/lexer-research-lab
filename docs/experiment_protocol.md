# Experiment protocol

Build with `python scripts/build.py all`; generate deterministic corpora with `python benchmarks/scripts/generate_corpus.py`; reproduce the whole study with `python benchmarks/scripts/run_all_benchmarks.py`.

Metrics: `throughput_mb_s = bytes / 1024 / 1024 / seconds`; `speedup = full_lex_us / incremental_lex_us`; `reuse_rate = reused_tokens / total_old_tokens * 100`; `tag_operations` counts recorded TDFA tag writes; `type_stable` and `lexeme_stable` compare first- and second-pass token streams.

CSV families cover lexer performance, derivative mismatches, incremental cases/failures, property summaries, diagnostics, automata states, lexical modes, TDFA, code-DFA, diagnostic explanations, and roundtrip checks. All figures are regenerated from `results/raw/*.csv`.
