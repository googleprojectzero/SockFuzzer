# This Dockerfile prepares a simple Debian build environment.

# docker build --pull -t builder .
# docker run -t -i -v $PWD:/source builder /bin/bash
FROM gcr.io/oss-fuzz-base/base-builder

RUN apt-get update && apt-get install -y \
    autoconf \
    cmake \
    git \
    g++-multilib \
    libtool \
    ninja-build \
    python

# Install Protobuf for C++ as the version in the base-builder repos may
# be outdated.
RUN curl -LO https://github.com/protocolbuffers/protobuf/releases/download/v3.18.1/protobuf-cpp-3.18.1.tar.gz
RUN tar xf protobuf-cpp-3.18.1.tar.gz
WORKDIR $SRC/protobuf-3.18.1
# Build statically
RUN ./configure --disable-shared
RUN make -j $(nproc)
RUN make install

WORKDIR $SRC
# You can now build using cmake. I use a subdirectory "build".
COPY build.sh $SRC
