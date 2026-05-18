# Figure gallery

- `fig1_lexer_throughput.*` from `lexer_performance.csv`: throughput comparison between the baseline and derivative demo.
- `fig2_automata_states.*` from `automata_stats.csv`: state counts across NFA, DFA, MinDFA.
- `fig3_incremental_reuse_rate.*` from `incremental_results.csv`: retained token suffix by edit case.
- `fig4_incremental_speedup.*` from `incremental_results.csv`: incremental/full timing ratio.
- `fig5_property_failures.*` from `property_fuzz_results.csv`: observed property failures.
- `fig6_diagnostics_distribution.*` from `diagnostics_distribution.csv`: malformed-input diagnostic mix.

Early observations should stay modest: the derivative demo is expected to trade engineering simplicity for lower performance than the baseline, while block-comment edits can force broad rescans because lexical mode leaks across lines.
