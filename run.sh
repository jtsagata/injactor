#!/usr/bin/env bash

cmake --build cmake-build-debug -j $(nproc) && ./cmake-build-debug/src/injactor $@
