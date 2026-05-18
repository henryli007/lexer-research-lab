# Roundtrip

Checks `source -> tokens -> printed source -> tokens` stability. Run `./build/roundtrip_check benchmarks/corpora/small.sy`. It validates token-stream stability, not exact source reconstruction, because comments and whitespace are intentionally discarded.
