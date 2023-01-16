FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y && apt install -y make git curl \
    g++-9 clang-format \
    # g++-multilib \
    python3.8 pypy3 python3-autopep8 python3-pytest-pylint python3-pip 
RUN pip3 install invoke requests bs4 lxml CacheControl
RUN pip3 install atcoder-tools docopt==0.6.2 && pip3 install MarkupSafe==2.0.1
WORKDIR /home/

RUN mkdir -p '/home/tasks' && \
    mkdir -p  '/home/tmp' && \
    mkdir -p  '/home/samples' && \
    mkdir -p  '/home/limits' && \
    mkdir -p  '/home/ignore_dir'

CMD [ "sleep", "infinity" ]
