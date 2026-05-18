from __future__ import print_function
import os, random
ROOT=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT=os.path.join(ROOT,"benchmarks","corpora")
random.seed(42)
stmt="int counter_{0} = {1};\n"
def write(name,text):
    p=os.path.join(OUT,name); open(p,"w").write(text)
def sized(target):
    s=[]; i=0
    while len("".join(s))<target:
        s.append(stmt.format(i,i%997)); i+=1
    return "".join(s)[:target]
write("small.sy",sized(1024))
write("medium.sy",sized(50*1024))
write("large.sy",sized(1024*1024))
write("comments_heavy.sy","".join("// line comment {0}\nint a{0}={0}; /* block {0} */\n".format(i) for i in range(4000)))
write("identifiers_heavy.sy","".join("value_{0}=value_{1}+value_{2};\n".format(i,i+1,i+2) for i in range(10000)))
write("malformed_mixed.sy","int ok=1;\n12abc\n1.\n1..2\n@\n/* unterminated comment")
