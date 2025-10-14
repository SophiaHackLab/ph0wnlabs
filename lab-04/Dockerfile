FROM alpine:3.19
LABEL author="cryptax"
LABEL version="ph0wnlab-04"
LABEL description="This is the Docker container for the r2ai workshop"

# Install build dependencies
RUN apk update && apk add --no-cache \
    automake \
    bash \
    build-base \
    clang \
    curl \
    gcc \
    git \
    jq \
    libc6-compat \
    libtool \
    linux-headers \
    make \
    man-db \
    meson \
    ninja \
    nodejs \
    pkgconfig \
    py3-pip \
    python3 \
    qemu-arm \
    tar \
    vim

# dockcode requires: libc6-compat

# Clone and install radare2 from GitHub
RUN git clone --depth=1 https://github.com/radareorg/radare2.git /opt/radare2 && \
    cd /opt/radare2 && \
    ./sys/install.sh

# R2ai requires curl and vim
#RUN git clone https://github.com/radareorg/r2ai.git /opt/r2ai && \
#    cd /opt/r2ai/src && \
#    make clean && make && make user-install

# Create a user
RUN addgroup -g 1000 work && \
    adduser -D -u 1000 -G work -h /home/work work && \
    mkdir -p /workshop && chown work:work /workshop
    
USER work
WORKDIR /home/work
ENV PS1="\[\e[97m\]\h\[\e[0m\]:\[\e[94m\]\w\[\e[0m\] \[\e[33m\]\$\[\e[0m\] "

# Initialize r2pm (Radare2 package manager)
RUN r2pm -U && r2pm -ci decai r2ai

# API key placeholder
# RUN echo "PUT-YOUR-API-KEY" > ~/.r2ai.groq-key

# Labs
COPY ./dockcode /workshop/dockcode
COPY ./README.md /workshop/README.md
COPY ./spoiler /workshop/spoiler

# Welcome message
RUN echo 'echo "======================================="' >> ~/.bashrc
RUN echo 'echo -e "        \e[97mR2AI Workshop\e[0m by @cryptax"' >> ~/.bashrc
RUN echo 'echo "                 ~~~~"' >> ~/.bashrc
RUN echo 'echo -e "     Exercises in \e[33m/workshop/\e[0m"' >> ~/.bashrc
RUN echo 'echo -e "     Install info in \e[33m/workshop/README.md\e[0m"' >> ~/.bashrc
RUN echo 'echo -e "  Already installed: \e[33mr2, r2ai, decai\e[0m"' >> ~/.bashrc
RUN echo 'echo "======================================="' >> ~/.bashrc

WORKDIR /workshop
ENTRYPOINT ["/bin/bash"]
