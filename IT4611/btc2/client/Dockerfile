FROM ubuntu:latest

RUN apt-get update && apt-get install -y vlc

# Create non-root user
RUN useradd -m vlcuser
USER vlcuser

WORKDIR /app