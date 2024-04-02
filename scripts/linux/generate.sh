#! /bin/bash

ROOT=$(dirname $0)/../..
cmake ${ROOT} -B ${ROOT}/build -DSOS_BUILD_TESTS=${1:-OFF} -DCMAKE_VERBOSE_MAKEFILE=${2:-OFF}
