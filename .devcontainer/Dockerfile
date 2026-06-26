FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y --no-install-recommends \
    ca-certificates \
    git \
    openssh-client \
    gpg \
    gpg-agent \
    build-essential \
    pkg-config \
    cmake \
    libgtest-dev \
    libgmock-dev \
    valgrind \
    gcovr

ARG USERNAME=user
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN deluser --remove-home ubuntu
RUN groupadd --gid $USER_GID $USERNAME
RUN useradd --uid $USER_UID --gid $USER_GID -m $USERNAME