# Method comparison

- **NFA-DFA baseline**: production reference scanner and correctness anchor.
- **Regex derivatives**: demonstrate direct recognition by symbolic regex evolution without constructing the same automaton pipeline.
- **Incremental lexing**: studies editor-like updates, token reuse, and rescan scope.
- **Property-based testing**: stresses lexer invariants over many generated inputs.
- **Automata visualization**: exposes how NFA, DFA, and MinDFA state counts change.

Current limits are intentional: the derivative lexer is a demo subset; incremental lexing uses a conservative first-pass boundary strategy; fuzzing is empirical rather than formal; visualization exports readable graphs rather than advanced layout metadata.
