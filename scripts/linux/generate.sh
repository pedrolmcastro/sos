#! /bin/bash

ROOT=$(dirname $0)/../..
cmake ${ROOT} -B ${ROOT}/build -DSOS_BUILD_TESTS=${1:-OFF}
