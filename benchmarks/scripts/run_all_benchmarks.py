from __future__ import print_function
import csv, os, subprocess, sys, time
ROOT=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
RAW=os.path.join(ROOT,"results","raw")
CORPORA=["small.sy","medium.sy","large.sy","comments_heavy.sy","identifiers_heavy.sy","malformed_mixed.sy"]
def exe(n): return os.path.join(ROOT,"build",n+(".exe" if os.name=="nt" else ""))
def run(cmd, **kw): return subprocess.run(cmd,cwd=ROOT,stdout=subprocess.PIPE,stderr=subprocess.PIPE,**kw)
def ensure(): os.makedirs(RAW,exist_ok=True)
def perf(method,path,binary,extra=None):
    data=open(path,"rb").read(); t=time.perf_counter(); p=run([binary,path]); ms=(time.perf_counter()-t)*1000; mb=len(data)/1024.0/1024.0
    return [method,os.path.basename(path),len(data),max(0,len(p.stdout.splitlines())-1),ms,mb/(ms/1000.0) if ms else 0,p.returncode==0,p.stderr.decode(errors="ignore").strip()]
def safe(cmd): return run(cmd)
ensure()
subprocess.check_call([sys.executable,"scripts/build.py","all"],cwd=ROOT)
subprocess.check_call([sys.executable,"benchmarks/scripts/generate_corpus.py"],cwd=ROOT)
with open(os.path.join(RAW,"lexer_performance.csv"),"w",newline="") as f:
    w=csv.writer(f); w.writerow(["method","file","input_bytes","tokens","elapsed_ms","throughput_mb_s","success","error"])
    for c in CORPORA:
        p=os.path.join(ROOT,"benchmarks","corpora",c)
        w.writerow(perf("baseline_dfa",p,exe("lexer_cli")))
        w.writerow(perf("regex_derivative",p,exe("derivative_lexer_cli")))
        q=safe([exe("code_dfa_bench"),p]); data=open(p,"rb").read()
        code_rows=list(csv.DictReader(open(os.path.join(RAW,"code_dfa_results.csv")))) if os.path.exists(os.path.join(RAW,"code_dfa_results.csv")) else []
        last=code_rows[-1] if code_rows else {}
        w.writerow(["code_driven_dfa",c,len(data),last.get("tokens",0),float(last.get("elapsed_us",0))/1000.0,last.get("throughput_mb_s",0),q.returncode==0,q.stderr.decode(errors="ignore").strip()])
        t=time.perf_counter(); mq=safe([exe("mode_lexer_cli"),p,"--cminus"]); ms=(time.perf_counter()-t)*1000; mb=len(data)/1024.0/1024.0
        w.writerow(["mode_lexer",c,len(data),max(0,len(mq.stdout.splitlines())-1),ms,mb/(ms/1000.0) if ms else 0,mq.returncode==0,mq.stderr.decode(errors="ignore").strip()])
with open(os.path.join(RAW,"derivative_mismatches.csv"),"w",newline="") as f:
    w=csv.writer(f); w.writerow(["file","index","baseline_type","derivative_type","baseline_lexeme","derivative_lexeme","reason"])
    for c in ["small.sy","medium.sy"]:
        p=os.path.join(ROOT,"benchmarks","corpora",c)
        a=safe([exe("lexer_cli"),p]).stdout.decode(errors="ignore").splitlines()[1:]
        b=safe([exe("derivative_lexer_cli"),p]).stdout.decode(errors="ignore").splitlines()[1:]
        for i in range(max(len(a),len(b))):
            aa=a[i].split("\t") if i<len(a) else ["","","MISSING","","",""]
            bb=b[i].split(",") if i<len(b) else ["","","MISSING","",""]
            bt=aa[2] if len(aa)>2 else "MISSING"; dt=bb[2] if len(bb)>2 else "MISSING"; bl=aa[5] if len(aa)>5 else ""; dl=bb[3] if len(bb)>3 else ""
            if bt!=dt or bl!=dl: w.writerow([c,i,bt,dt,bl,dl,"type_or_lexeme_mismatch"])
safe([exe("incremental_bench"),os.path.join(ROOT,"benchmarks","corpora","medium.sy"),os.path.join(ROOT,"methods","incremental-lexing","tests","edit_cases.jsonl")])
safe([exe("lexer_fuzz"),"--cases","1000","--seed","42"])
with open(os.path.join(RAW,"automata_stats.csv"),"wb") as f: f.write(safe([exe("automata_stats_dump")]).stdout)
with open(os.path.join(RAW,"automata_minimization.csv"),"w",newline="") as f:
    rows=list(csv.DictReader(open(os.path.join(RAW,"automata_stats.csv")))); w=csv.writer(f); w.writerow(["stage","states","edges","accept_states"]); [w.writerow([r["automaton"],r["states"],r["edges"],r["accept_states"]]) for r in rows]
safe([exe("export_automata_dot")])
with open(os.path.join(RAW,"lexical_modes_results.csv"),"w",newline="") as f:
    w=csv.writer(f); w.writerow(["file","mode_demo","input_bytes","tokens","mode_transitions","elapsed_us","throughput_mb_s","success"])
    for fn,flag,demo in [("template_demo.txt","--template","template"),("cminus_comments.sy","--cminus","cminus")]:
        p=os.path.join(ROOT,"methods","lexical-modes","examples",fn); data=open(p,"rb").read(); t=time.perf_counter(); q=safe([exe("mode_lexer_cli"),p,flag]); us=(time.perf_counter()-t)*1e6; rows=q.stdout.decode(errors="ignore").splitlines()[1:]; trans=sum(1 for x in rows if x.endswith("TEMPLATE_TEXT->TEMPLATE_EXPR") or "->" in x.split(",")[-1]); w.writerow([fn,demo,len(data),len(rows),trans,int(us),(len(data)/1024.0/1024.0)/(us/1e6) if us else 0,q.returncode==0])
open(os.path.join(RAW,"tdfa_results.csv"),"w").close(); safe([exe("tdfa_demo"),"--float","123.45"]); safe([exe("tdfa_demo"),"--string","\"hello\\nworld\""])
open(os.path.join(RAW,"diagnostic_engine_results.csv"),"w").close()
for fn in ["malformed_number.sy","unterminated_comment.sy","unexpected_char.sy","isolated_bang.sy","invalid_operator_sequence.sy","chinese_punctuation.sy"]: safe([exe("diagnostic_demo"),os.path.join(ROOT,"methods","diagnostic-engine","examples",fn)])
open(os.path.join(RAW,"roundtrip_results.csv"),"w").close()
for c in ["small.sy","medium.sy","large.sy","malformed_mixed.sy"]: safe([exe("roundtrip_check"),os.path.join(ROOT,"benchmarks","corpora",c)])
subprocess.run([sys.executable,"scripts/plot_paper_figures.py"],cwd=ROOT)
subprocess.run([sys.executable,"scripts/check_figures.py"],cwd=ROOT)
