FROM ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
    vim \
    curl \
    gdb \
    && rm -rf /var/lib/apt/lists/* \
    wget 

RUN apt-get update && apt-get install -y libboost-all-dev

WORKDIR /workspace

CMD ["/bin/bash"]