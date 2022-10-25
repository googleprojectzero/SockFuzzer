# Copyright 2022 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
