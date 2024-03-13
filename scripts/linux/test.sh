#! /bin/bash

ROOT=$(dirname $0)/../..
ctest --test-dir ${ROOT}/build
