#!/usr/bin/env bash
set -e

ASSIMP_DIR="$(cd "$(dirname "$0")/../Vendor/assimp" && pwd)"
BUILD_DIR="$ASSIMP_DIR/build"

cmake -S "$ASSIMP_DIR" -B "$BUILD_DIR" \
  -DASSIMP_BUILD_TESTS=OFF \
  -DASSIMP_BUILD_ASSIMP_TOOLS=OFF \
  -DBUILD_SHARED_LIBS=OFF

cmake --build "$BUILD_DIR" --config Debug
cmake --build "$BUILD_DIR" --config Release