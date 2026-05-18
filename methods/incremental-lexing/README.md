# Incremental lexing

Experimental wrapper around the baseline lexer. The first implementation uses line-start safe boundaries, extends the boundary backward when an edit is inside an open block comment, and reports reuse/speedup against a full-lex reference run.
