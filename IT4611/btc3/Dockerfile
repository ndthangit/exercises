FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install -y bind9 bind9utils bind9-doc net-tools iputils-ping dnsutils && \
    apt-get clean

CMD ["/bin/bash"]