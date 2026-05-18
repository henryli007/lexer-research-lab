# Method comparison

| Method | Level | Solves | Strength | Limitation |
|---|---|---|---|---|
| baseline NFA-DFA | production baseline | reference tokenization | stable correctness anchor | table-driven only |
| regex derivative | prototype | recognition by regex evolution | exposes symbolic state growth | subset demo, slower |
| incremental lexing | benchmark wrapper | editor edits | reuse/rescan metrics | conservative first pass |
| property testing | prototype | invariant discovery | finds edge cases cheaply | empirical, not proof |
| automata visualization | prototype | explain construction | visible NFA/DFA/MinDFA shrinkage | static graphs |
| lexical modes | prototype | context-sensitive scanning | clear state transitions | demo grammar only |
| TDFA | toy demo | submatch extraction | shows tag operations | no generator |
| code-driven DFA | benchmark wrapper | encoding comparison | future switch-DFA slot | currently baseline-backed |
| diagnostic engine | prototype | explanations/fix hints | richer teaching feedback | heuristic fixes |
| roundtrip | prototype | token-printer stability | catches stream drift | not source preservation |
