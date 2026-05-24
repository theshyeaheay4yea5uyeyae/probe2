#!/usr/bin/env bash
set -euo pipefail
rm -rf build dist
mkdir -p dist
cmake -S . -B build
cmake --build build --verbose
cp build/probe2.suprx dist/probe2.suprx
echo "OK: dist/probe2.suprx"
