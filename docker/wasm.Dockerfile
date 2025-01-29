FROM toxchat/qtox:wasm-builder AS builder

ENV PKG_CONFIG_PATH="/work/lib/pkgconfig"

COPY CMakeLists.txt /qtox/
COPY src /qtox/src/
RUN . "/work/emsdk/emsdk_env.sh" \
 && emcmake cmake \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_FIND_ROOT_PATH="/work;/work/qt" \
  -GNinja \
  -B_build-wasm \
  -H. \
 && cmake --build _build-wasm

RUN mkdir _site \
 && cp \
 _build-wasm/qtloader.js \
 _build-wasm/qtlogo.svg \
 _build-wasm/debugtox.html \
 _build-wasm/debugtox.js \
 _build-wasm/debugtox.wasm \
 _site

FROM alpine:3.21 AS venv

RUN apk add curl \
  gcc \
  linux-headers \
  musl-dev \
  py3-pip \
  py3-virtualenv \
  python3-dev

# Create a virtual environment for qtwasmserver.
RUN python3 -m venv /work/venv \
 && . /work/venv/bin/activate \
 && CFLAGS=-Wno-int-conversion pip3 install brotli httpcompressionserver netifaces \
 && curl -L https://raw.githubusercontent.com/qt/qtbase/refs/heads/dev/util/wasm/qtwasmserver/qtwasmserver.py -o /work/venv/bin/qtwasmserver.py \
 && chmod +x /work/venv/bin/qtwasmserver.py

FROM alpine:3.21

RUN apk add python3

COPY --from=venv /work/venv /work/venv
COPY --from=builder /qtox/_site /qtox/_site

ENV PORT=8000
WORKDIR /qtox/_site
CMD . /work/venv/bin/activate \
 && qtwasmserver.py \
 --cross-origin-isolation \
 --all-interfaces \
 --compress-never \
 --port "$PORT"
