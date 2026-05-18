from __future__ import print_function
import csv, os
import matplotlib.pyplot as plt
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__))); RAW=os.path.join(ROOT,"results","raw"); FIG=os.path.join(ROOT,"results","figures"); os.makedirs(FIG,exist_ok=True)
plt.rcParams.update({"figure.figsize":(6.5,4.0),"font.size":10,"axes.spines.top":False,"axes.spines.right":False})
def rows(name):
    with open(os.path.join(RAW,name)) as f:return list(csv.DictReader(f))
def save(name):
    plt.tight_layout(); plt.savefig(os.path.join(FIG,name+".pdf")); plt.savefig(os.path.join(FIG,name+".svg")); plt.close()
perf=rows("lexer_performance.csv"); corpora=[]; methods=["baseline_dfa","regex_derivative"]
for r in perf:
    if r["file"] not in corpora: corpora.append(r["file"])
vals={m:[float(next(x["throughput_mb_s"] for x in perf if x["method"]==m and x["file"]==c)) for c in corpora] for m in methods}
x=range(len(corpora)); w=.36; plt.bar([i-w/2 for i in x],vals[methods[0]],w,label="baseline_dfa",hatch="//");plt.bar([i+w/2 for i in x],vals[methods[1]],w,label="regex_derivative",hatch="\\\\");plt.xticks(list(x),corpora,rotation=30,ha="right");plt.ylabel("Throughput (MB/s)");plt.xlabel("Corpus");plt.legend();save("fig1_lexer_throughput")
a=rows("automata_stats.csv"); plt.bar([r["automaton"] for r in a],[int(r["states"]) for r in a]);plt.ylabel("States");plt.xlabel("Automaton");save("fig2_automata_states")
inc=rows("incremental_results.csv"); names=[r["case_name"] for r in inc]; plt.bar(names,[float(r["reuse_rate"]) for r in inc]);plt.ylabel("Token reuse rate (%)");plt.xlabel("Edit case");plt.xticks(rotation=35,ha="right");save("fig3_incremental_reuse_rate")
plt.bar(names,[float(r["speedup"]) for r in inc]);plt.ylabel("Speedup over full lexing");plt.xlabel("Edit case");plt.xticks(rotation=35,ha="right");save("fig4_incremental_speedup")
prop=rows("property_fuzz_results.csv"); plt.bar([r["property"] for r in prop],[int(r["fail_count"]) for r in prop]);plt.ylabel("Fail count");plt.xlabel("Property");plt.xticks(rotation=35,ha="right");plt.title("Property failures (no failures observed)" if all(int(r["fail_count"])==0 for r in prop) else "Property failures");save("fig5_property_failures")
diag=rows("diagnostics_distribution.csv"); plt.bar([r["diagnostic"] for r in diag],[int(r["count"]) for r in diag]);plt.ylabel("Count");plt.xlabel("Diagnostic type");plt.xticks(rotation=30,ha="right");save("fig6_diagnostics_distribution")
