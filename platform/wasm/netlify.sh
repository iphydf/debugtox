#!/bin/bash

set -eux -o pipefail

tar -C /opt -zxf <(curl -L https://github.com/TokTok/dockerfiles/releases/download/nightly/qtox-wasm-buildhome.tar.gz)

. '/opt/buildhome/emsdk/emsdk_env.sh'

emcmake cmake \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_FIND_ROOT_PATH='/opt/buildhome;/opt/buildhome/qt' \
  -GNinja \
  -B_build-wasm \
  -H.

cmake --build _build-wasm

mkdir _site

cp \
  _build-wasm/qtloader.js \
  _build-wasm/qtlogo.svg \
  _build-wasm/debugtox.js \
  _build-wasm/debugtox.wasm \
  _site
cp _build-wasm/debugtox.html \
  _site/index.html
