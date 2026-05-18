# Experiment protocol

Environment: local C++11 toolchain plus Python 3 and matplotlib. Build with `python scripts/build.py all`. Corpora are generated deterministically by `python benchmarks/scripts/generate_corpus.py`.

Metrics:
- `throughput_mb_s = input_bytes / 1024 / 1024 / elapsed_seconds`
- `speedup = full_lex_ms / incremental_lex_ms`
- `reuse_rate = reused_tokens / total_old_tokens * 100`

Reproduce the full pipeline with `python benchmarks/scripts/run_all_benchmarks.py`, then regenerate figures with `python scripts/plot_paper_figures.py` and verify them with `python scripts/check_figures.py`.
