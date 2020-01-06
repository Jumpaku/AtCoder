FROM ubuntu:19.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y && apt install -y make g++ clang-format g++-multilib python3 pypy3 python3-autopep8 python3-pytest-pylint git

WORKDIR /home/

CMD [ "sleep", "infinity" ]
