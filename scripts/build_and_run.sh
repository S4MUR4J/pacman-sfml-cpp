#!/bin/bash
set -e
cd "$(dirname "$0")/.."

cmake -B build
cmake --build build

if [[ "$OSTYPE" == msys* || "$OSTYPE" == cygwin* ]]; then
    ./build/Pacman.exe
else
    ./build/Pacman
fi