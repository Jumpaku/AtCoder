FROM ubuntu:23.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y && apt install -y make git curl jq \
    g++-12 clang-format \
    python3.11 pypy3 python3-autopep8 python3-pytest-pylint python3-pip 
RUN pip3 install --break-system-packages requests bs4 lxml CacheControl
WORKDIR /work/

RUN mkdir -p '/work/tasks' && \
    mkdir -p  '/work/ignore_dir'

CMD [ "sleep", "infinity" ]
