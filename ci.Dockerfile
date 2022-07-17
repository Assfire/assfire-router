FROM debian:11.4

RUN apt-get update -y && apt-get install -y clang wget
RUN wget https://github.com/bazelbuild/bazelisk/releases/download/v1.12.0/bazelisk-linux-amd64 && chmod +x bazelisk-linux-amd64 && mv bazelisk-linux-amd64 /usr/bin/bazel
ENV CC=cc
