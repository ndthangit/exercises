FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y vlc pulseaudio dbus-x11 xvfb && \
    apt-get clean

# Create non-root user
RUN useradd -m vlcuser && \
    mkdir -p /tmp/runtime-vlcuser && \
    chown -R vlcuser:vlcuser /tmp/runtime-vlcuser

USER vlcuser
WORKDIR /videos