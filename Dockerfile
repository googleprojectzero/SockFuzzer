# This Dockerfile prepares a simple Debian build environment.

# docker build --pull -t builder .
# docker run -t -i -v $PWD:/source builder /bin/bash
FROM debian:testing

RUN apt-get update && apt-get install -y \
    autoconf \
    curl \
    cmake \
    git \
    g++-multilib \
    libbsd-dev \
    libprotobuf-dev \
    libtool \
    ninja-build \
    patchelf \
    protobuf-compiler \
    python \
    wget

# Fetch a recent clang build from Chromium
RUN curl -s https://raw.githubusercontent.com/chromium/chromium/master/tools/clang/scripts/update.py | python - --output-dir=/clang
ENV PATH "$PATH:/clang/bin"

# You can now build using cmake. I use a subdirectory "build".
WORKDIR /source/build
