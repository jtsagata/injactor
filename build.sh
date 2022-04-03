#!/usr/bin/env bash

set -x
yes | rm -r build
cmake -S . -B build -G "Ninja"
time cmake --build build -j $(nproc)
