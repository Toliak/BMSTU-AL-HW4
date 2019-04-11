FROM ubuntu:18.04
RUN apt-get -y update
RUN apt-get -y install software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get -y update
RUN apt-get -y install cmake g++-8 git
RUN apt-get -y upgrade
RUN ln -s /usr/bin/g++-8 /usr/local/bin/g++
WORKDIR ~/BMSTU-AL-HW4/
ARG CACHEBUST=1 
COPY . .
RUN cmake --version && mkdir -p cmake-build-debug
WORKDIR cmake-build-debug/
RUN cmake ..
RUN cmake --build .
ENTRYPOINT ./BMSTU_AL_HW4