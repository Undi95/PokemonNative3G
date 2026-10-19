# Environnement de build reproductible (Linux natif + Windows via mingw-w64)
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential git make python3 pkg-config ca-certificates curl \
        libpng-dev libsdl2-dev g++-mingw-w64-x86-64 binutils-mingw-w64-x86-64 \
    && rm -rf /var/lib/apt/lists/*
# SDL2 pour mingw (cible Windows), depuis les releases officielles libsdl-org
ARG SDL_VER=2.30.9
RUN curl -fsSL https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VER}/SDL2-devel-${SDL_VER}-mingw.tar.gz \
      | tar -xz -C /opt && mv /opt/SDL2-${SDL_VER} /opt/SDL2
RUN git config --global --add safe.directory '*'
WORKDIR /src
