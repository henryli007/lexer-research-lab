from __future__ import print_function
import os, sys
ROOT=os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),"results","figures")
names=["fig1_lexer_throughput","fig2_automata_states","fig3_incremental_reuse_rate","fig4_incremental_speedup","fig5_property_failures","fig6_diagnostics_distribution","fig7_lexical_modes_transitions","fig8_tdfa_tag_operations","fig9_code_dfa_vs_table_dfa","fig10_roundtrip_stability","fig11_diagnostic_fix_hints"]
bad=[]
for n in names:
    for ext in ("pdf","svg"):
        p=os.path.join(ROOT,n+"."+ext)
        if not os.path.exists(p) or os.path.getsize(p)<=0: bad.append(p)
print("checked",len(names)*2,"figure files;",len(bad),"missing_or_empty")
if bad: print("\n".join(bad)); sys.exit(1)
