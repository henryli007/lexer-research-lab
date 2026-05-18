from __future__ import print_function
import os, sys
root=os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),"results","figures")
names=["fig1_lexer_throughput","fig2_automata_states","fig3_incremental_reuse_rate","fig4_incremental_speedup","fig5_property_failures","fig6_diagnostics_distribution"]
bad=[]
for n in names:
    for ext in ("pdf","svg"):
        p=os.path.join(root,n+"."+ext)
        if not os.path.exists(p) or os.path.getsize(p)<=0: bad.append(p)
if bad:
    print("missing or empty figures:"); print("\n".join(bad)); sys.exit(1)
print("all required figures exist")
