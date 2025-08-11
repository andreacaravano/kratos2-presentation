#
#                  Politecnico di Milano
#
#        Students: Caravano Andrea, Cantele Alberto, Cancelliere Biagio
#
#   Last modified: 09/04/2025
#
#     Description: Dockerfile for the Kratos2 tool presentation, development container with C/C++ development, debugging and analysis chain

# Python's Debian-based image
FROM --platform=linux/amd64 python:3.11-bookworm
# Python 3.11 is the maximum supported version for C2Kratos (see https://stackoverflow.com/a/77411659)

#### PYTHON DEPENDENCIES (for the C to Kratos conversion tool) ####
RUN pip install pycparser pcpp

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get dist-upgrade -y \
    && apt-get -y install --no-install-recommends gdb hotspot valgrind build-essential cmake nano curl tar gzip \
    && apt clean
# kcachegrind and massif-visualizer are left out (no GUI)

#### TEST GCC ####
RUN gcc --version

#### DOWNLOAD KRATOS2 ####
ARG KRATOS_RELEASE=https://kratos.fbk.eu/releases/kratos-2.2-linux64.tar.gz
ARG DESTINATION_FOLDER=kratos-2.2-linux64
RUN mkdir /tmp/kratos
WORKDIR /tmp/kratos
RUN curl --output ./release ${KRATOS_RELEASE}
RUN mkdir /kratos
RUN tar -zxvf ./release
RUN mv ./${DESTINATION_FOLDER}/* /kratos
RUN chmod 755 /kratos/bin/kratos
RUN rm -rf /tmp/kratos

#### UPDATE SYSTEM AND PYTHON PATH WITH KRATOS EXECUTABLE AND TOOLS ####
ENV PATH="$PATH:/kratos/bin"
ENV PYTHONPATH="/kratos/tools"

#### CLEAN UP ####
WORKDIR /
RUN rm -rf /tmp/*

#### ADD DEFAULT USER ####
ARG USER=kratosuser
ENV USER=${USER}
RUN adduser --disabled-password ${USER}

ENV USER_HOME=/home/${USER}
RUN chown -R ${USER}:${USER} ${USER_HOME}

USER ${USER}
WORKDIR ${USER_HOME}