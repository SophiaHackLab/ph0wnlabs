# Use a lightweight base image
FROM debian:bullseye-slim

# Install required tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    curl \
    build-essential \
    python3 \
    binutils \
    file \
    gdb \
    ca-certificates \
    && apt-get clean \
    && update-ca-certificates \
    && rm -rf /var/lib/apt/lists/*
    
# Install Radare2 from GitHub
RUN git clone https://github.com/radareorg/radare2.git /opt/radare2 && \
    cd /opt/radare2 && ./sys/install.sh 
    
# Set the working directory
WORKDIR /workspace

# Set bash as the default shell
CMD ["/bin/bash"]
