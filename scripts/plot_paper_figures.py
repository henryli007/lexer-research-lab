from __future__ import print_function
import csv, os
import matplotlib.pyplot as plt
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__))); RAW=os.path.join(ROOT,"results","raw"); FIG=os.path.join(ROOT,"results","figures"); os.makedirs(FIG,exist_ok=True)
plt.rcParams.update({"figure.figsize":(6.5,4.0),"font.size":10,"axes.spines.top":False,"axes.spines.right":False})
def rows(name):
    p=os.path.join(RAW,name)
    return list(csv.DictReader(open(p))) if os.path.exists(p) and os.path.getsize(p) else []
def save(name):
    plt.tight_layout(); plt.savefig(os.path.join(FIG,name+".pdf")); plt.savefig(os.path.join(FIG,name+".svg")); plt.close()
def empty(title):
    plt.text(.5,.5,"missing data",ha="center",va="center"); plt.title(title)
perf=rows("lexer_performance.csv"); methods=["baseline_dfa","regex_derivative","code_driven_dfa","mode_lexer"]; corpora=[]
for r in perf:
    if r["file"] not in corpora: corpora.append(r["file"])
if perf:
    x=list(range(len(corpora))); w=.18
    for k,m in enumerate(methods): plt.bar([i+(k-1.5)*w for i in x],[float(next((z["throughput_mb_s"] for z in perf if z["method"]==m and z["file"]==c),0)) for c in corpora],w,label=m)
    plt.xticks(x,corpora,rotation=30,ha="right");plt.ylabel("Throughput (MB/s)");plt.xlabel("Corpus");plt.legend(fontsize=8)
else: empty("Lexer throughput")
save("fig1_lexer_throughput")
a=rows("automata_stats.csv")
if a: plt.bar([r["automaton"] for r in a],[int(r["states"]) for r in a]);plt.ylabel("States");plt.xlabel("Automaton")
else: empty("Automata states")
save("fig2_automata_states")
inc=rows("incremental_results.csv")
if inc: 
    names=[r["case_name"] for r in inc]; plt.bar(names,[float(r["reuse_rate"]) for r in inc]);plt.ylabel("Token reuse rate (%)");plt.xlabel("Edit case");plt.xticks(rotation=35,ha="right")
else: empty("Incremental reuse")
save("fig3_incremental_reuse_rate")
if inc: plt.bar(names,[float(r["speedup"]) for r in inc]);plt.ylabel("Speedup over full lexing");plt.xlabel("Edit case");plt.xticks(rotation=35,ha="right")
else: empty("Incremental speedup")
save("fig4_incremental_speedup")
prop=rows("property_failures_summary.csv")
if prop: plt.bar([r["property"] for r in prop],[int(r["fail_count"]) for r in prop]);plt.ylabel("Fail count");plt.xlabel("Property");plt.xticks(rotation=35,ha="right")
else: empty("Property failures")
save("fig5_property_failures")
diag=rows("diagnostics_distribution.csv")
if diag: plt.bar([r["diagnostic"] for r in diag],[int(r["count"]) for r in diag]);plt.ylabel("Count");plt.xlabel("Diagnostic code");plt.xticks(rotation=30,ha="right")
else: empty("Diagnostics distribution")
save("fig6_diagnostics_distribution")
modes=rows("lexical_modes_results.csv")
if modes:
    x=[r["mode_demo"] for r in modes]; plt.bar(x,[int(r["mode_transitions"]) for r in modes],label="mode transitions");plt.plot(x,[int(r["tokens"]) for r in modes],marker="o",label="tokens");plt.ylabel("Count");plt.xlabel("Mode demo");plt.legend()
else: empty("Lexical modes")
save("fig7_lexical_modes_transitions")
t=rows("tdfa_results.csv")
if t: plt.bar([r["demo"] for r in t],[int(r["tag_operations"]) for r in t]);plt.ylabel("Tag operations");plt.xlabel("TDFA demo")
else: empty("TDFA tags")
save("fig8_tdfa_tag_operations")
if perf:
    small=[r for r in perf if r["method"] in ("baseline_dfa","code_driven_dfa") and r["file"]!="malformed_mixed.sy"]
    labels=[r["file"]+"-"+r["method"] for r in small]; plt.bar(labels,[float(r["throughput_mb_s"]) for r in small]);plt.ylabel("Throughput (MB/s)");plt.xticks(rotation=35,ha="right")
else: empty("Code vs table DFA")
save("fig9_code_dfa_vs_table_dfa")
rt=rows("roundtrip_results.csv")
if rt:
    x=[os.path.basename(r["file"]) for r in rt]; plt.plot(x,[1 if r["type_stable"]=="true" else 0 for r in rt],marker="o",label="type stable");plt.plot(x,[1 if r["lexeme_stable"]=="true" else 0 for r in rt],marker="s",label="lexeme stable");plt.ylabel("Stable (0/1)");plt.xlabel("Corpus");plt.legend();plt.xticks(rotation=25,ha="right")
else: empty("Roundtrip")
save("fig10_roundtrip_stability")
de=rows("diagnostic_engine_results.csv")
if de:
    agg={}
    for r in de: agg[r["diagnostic_code"]]=agg.get(r["diagnostic_code"],0)+int(r["fix_hints"])
    plt.bar(list(agg),list(agg.values()));plt.ylabel("Fix hints");plt.xlabel("Diagnostic code");plt.xticks(rotation=30,ha="right")
else: empty("Diagnostic fixes")
save("fig11_diagnostic_fix_hints")
