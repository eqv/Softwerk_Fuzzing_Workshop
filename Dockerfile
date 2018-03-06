FROM ubuntu:18.04

RUN apt update
RUN apt-get install -y libfuzzer-5.0-dev clang-5.0 git

RUN git clone https://github.com/eqv/Softwerk_Fuzzing_Workshop.git

WORKDIR /Softwerk_Fuzzing_Workshop

CMD /bin/bash
