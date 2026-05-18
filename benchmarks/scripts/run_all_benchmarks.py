from __future__ import print_function
import csv, os, subprocess, sys, time
import json
ROOT=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
def exe(name): return os.path.join(ROOT,"build",name+(".exe" if os.name=="nt" else ""))
def run(cmd, **kw): return subprocess.run(cmd,cwd=ROOT,**kw)
def perf_row(method,path):
    data=open(path,"rb").read(); t=time.time()
    if method=="baseline_dfa": p=run([exe("lexer_cli"),path],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    else: p=run([exe("derivative_lexer_cli"),path],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    ms=(time.time()-t)*1000.0; toks=max(0,len(p.stdout.splitlines())-1); mb=len(data)/(1024.0*1024.0); return [method,os.path.basename(path),len(data),toks,ms,mb/(ms/1000.0) if ms else 0,p.returncode==0]
run([sys.executable,"scripts/build.py","all"],check=True)
run([sys.executable,"benchmarks/scripts/generate_corpus.py"],check=True)
raw=os.path.join(ROOT,"results","raw"); os.makedirs(raw,exist_ok=True)
corpora=[os.path.join(ROOT,"benchmarks","corpora",x) for x in ["small.sy","medium.sy","large.sy","comments_heavy.sy","identifiers_heavy.sy","malformed_mixed.sy"]]
with open(os.path.join(raw,"lexer_performance.csv"),"w",newline="") as f:
    w=csv.writer(f); w.writerow(["method","file","input_bytes","tokens","elapsed_ms","throughput_mb_s","success"])
    for c in corpora:
        w.writerow(perf_row("baseline_dfa",c)); w.writerow(perf_row("regex_derivative",c))
run([exe("incremental_bench"),os.path.join(ROOT,"benchmarks","corpora","large.sy"),os.path.join(ROOT,"methods","incremental-lexing","tests","edit_cases.jsonl")],check=True)
run([exe("lexer_fuzz"),"--cases","1000","--seed","42"],check=True)
with open(os.path.join(raw,"automata_stats.csv"),"w") as f: run([exe("automata_stats_dump")],stdout=f,check=True)
p=run([exe("lexer_cli"),os.path.join(ROOT,"benchmarks","corpora","malformed_mixed.sy")],stdout=subprocess.PIPE,stderr=subprocess.PIPE,env=dict(os.environ,DIAGNOSTICS_JSON="1"))
counts={}
for line in p.stderr.decode(errors="ignore").splitlines():
    if line.startswith("{"):
        try:
            code=json.loads(line).get("code","UNKNOWN"); counts[code]=counts.get(code,0)+1
        except Exception:
            pass
with open(os.path.join(raw,"diagnostics_distribution.csv"),"w",newline="") as f:
    w=csv.writer(f); w.writerow(["diagnostic","count"])
    for k in sorted(counts): w.writerow([k,counts[k]])
run([exe("export_automata_dot")],check=True)
run([sys.executable,"scripts/plot_paper_figures.py"],check=True)
