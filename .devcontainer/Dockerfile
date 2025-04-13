ARG BASE=mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04
FROM $BASE

RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | gpg --dearmor -o /etc/apt/trusted.gpg.d/llvm-archive-keyring.gpg \ 
    && echo "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-20 main" > /etc/apt/sources.list.d/llvm.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
    clang-20 \
    clangd-20 \
    clang-tidy-20 \
    libclang-20-dev \
    clang-tools-20 \
    clang-format-20 \
    libstdc++-12-dev \
    libc++-12-dev \
    libc++abi-12-dev \
    libfmt-dev \
    libgtest-dev \
    cmake-format \
    && rm -rf /var/lib/apt/lists/*

ENTRYPOINT [ "bash" ]