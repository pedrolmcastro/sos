#! /bin/bash

ROOT=$(dirname $0)/../..
clang-format -i --fail-on-incomplete-format --style=file ${ROOT}/include/sos/*/*.hpp ${ROOT}/tests/src/*/*.cpp
