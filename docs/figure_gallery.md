# Figure gallery

- `fig1_lexer_throughput.*` <- `lexer_performance.csv`: cross-method throughput.
- `fig2_automata_states.*` <- `automata_stats.csv`: automata size.
- `fig3_incremental_reuse_rate.*`, `fig4_incremental_speedup.*` <- `incremental_results.csv`: edit sensitivity.
- `fig5_property_failures.*` <- `property_failures_summary.csv`: observed invariant failures.
- `fig6_diagnostics_distribution.*` <- `diagnostics_distribution.csv`: diagnostic mix.
- `fig7_lexical_modes_transitions.*` <- `lexical_modes_results.csv`: mode activity.
- `fig8_tdfa_tag_operations.*` <- `tdfa_results.csv`: tag work.
- `fig9_code_dfa_vs_table_dfa.*` <- `lexer_performance.csv`: encoding comparison surface.
- `fig10_roundtrip_stability.*` <- `roundtrip_results.csv`: token-stream stability.
- `fig11_diagnostic_fix_hints.*` <- `diagnostic_engine_results.csv`: hint coverage.

Observations are intentionally modest: derivative recognition is slower; comment-oriented edits reduce reuse; code-driven DFA is not yet a fair standalone implementation.
