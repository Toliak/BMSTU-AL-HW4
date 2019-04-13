FROM alpine
RUN apk add build-base g++ gcc git cmake
WORKDIR root/BMSTU_AL_HW4/
COPY . .
RUN cmake --version && mkdir -p cmake-build-debug
WORKDIR cmake-build-debug/
RUN cmake ..
RUN cmake --build .
ENTRYPOINT /root/BMSTU_AL_HW4/cmake-build-debug/BMSTU_HW_4