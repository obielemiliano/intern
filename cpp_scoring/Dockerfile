FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libssl-dev \
    wget \
    git \
    python3 \
    nlohmann-json3-dev \
    libasio-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy project files
COPY . /app

# Generate crow_all.h
RUN mkdir -p include && \
    git clone https://github.com/CrowCpp/Crow.git crow_temp && \
    python3 crow_temp/scripts/merge_all.py crow_temp/include include/crow_all.h && \
    rm -rf crow_temp

# Build the project
RUN mkdir -p build && cd build && cmake .. && make -j$(nproc)

EXPOSE 8081
CMD ["/app/build/cpp_scoring"]
