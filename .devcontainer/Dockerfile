FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y && apt install -y make git curl \
    g++-9 clang-format \
    # g++-multilib \
    python3.8 pypy3 python3-autopep8 python3-pytest-pylint python3-pip 
RUN pip3 install requests bs4 lxml CacheControl
RUN pip3 install atcoder-tools
WORKDIR /home/

CMD [ "sleep", "infinity" ]
