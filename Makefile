SHELL := powershell.exe
.SHELLFLAGS := -NoProfile -Command

CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude

BUILD_DIR := build
LEXER_BIN := $(BUILD_DIR)/lexer_cli.exe

LEXER_SRCS := \
    tools/lexer_cli.cpp \
    src/lexer/lexer.cpp \
    src/lexer/automata.cpp

.PHONY: all baseline derivative incremental fuzz automata-viz benchmark figures run clean

all: baseline derivative incremental fuzz automata-viz
baseline: $(LEXER_BIN)
derivative:
	python scripts/build.py derivative
incremental:
	python scripts/build.py incremental
fuzz:
	python scripts/build.py fuzz
automata-viz:
	python scripts/build.py automata-viz
	python scripts/build.py automata-stats
benchmark:
	python benchmarks/scripts/run_all_benchmarks.py
figures:
	python scripts/plot_paper_figures.py

$(BUILD_DIR):
	if (-not (Test-Path '$(BUILD_DIR)')) { New-Item -ItemType Directory '$(BUILD_DIR)' | Out-Null }

$(LEXER_BIN): $(LEXER_SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LEXER_SRCS) -o $(LEXER_BIN)

run: $(LEXER_BIN)
	./build/lexer_cli tests/inputs/valid_basic.sy

clean:
	if (Test-Path '$(BUILD_DIR)') { $$removed = $$false; for ($$i = 0; $$i -lt 5 -and -not $$removed; $$i++) { try { Remove-Item -Recurse -Force '$(BUILD_DIR)' -ErrorAction Stop; $$removed = $$true } catch { Start-Sleep -Milliseconds 200 } }; if (Test-Path '$(BUILD_DIR)') { throw 'failed to remove $(BUILD_DIR)' } }
