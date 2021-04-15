#!/usr/bin/env bash

export LC_ALL=C
set -exo pipefail

# Debian 9
docker build . -f Dockerfile-build-python.apt --build-arg FROMBASEOS=debian --build-arg FROMBASEOS_BUILD_TAG=9 -t electriccoinco/votecoind-build-debian9
docker push electriccoinco/votecoind-build-debian9
docker build . -f Dockerfile-bbworker.apt --build-arg BASEOS=debian --build-arg FROMBASEOS=debian --build-arg FROMBASEOS_BUILD_TAG=9 -t electriccoinco/votecoind-bbworker-debian9
docker push electriccoinco/votecoind-bbworker-debian9

# Debian 10
docker build . -f Dockerfile-build.apt --build-arg FROMBASEOS=debian --build-arg FROMBASEOS_BUILD_TAG=10 -t electriccoinco/votecoind-build-debian10
docker push electriccoinco/votecoind-build-debian10
docker build . -f Dockerfile-gitian.apt --build-arg FROMBASEOS=debian --build-arg FROMBASEOS_BUILD_TAG=10 -t electriccoinco/votecoind-gitian-debian10
docker push electriccoinco/votecoind-gitian-debian10
docker build . -f Dockerfile-bbworker.apt --build-arg BASEOS=debian --build-arg FROMBASEOS=debian --build-arg FROMBASEOS_BUILD_TAG=10 -t electriccoinco/votecoind-bbworker-debian10
docker push electriccoinco/votecoind-bbworker-debian10

# Ubuntu 16.04
docker build . -f Dockerfile-build.apt --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=16.04 -t electriccoinco/votecoind-build-ubuntu1604
docker push electriccoinco/votecoind-build-ubuntu1604
docker build . -f Dockerfile-gitian.apt --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=1604 -t electriccoinco/votecoind-gitian-ubuntu1604
docker push electriccoinco/votecoind-gitian-ubuntu1604
docker build . -f Dockerfile-bbworker.apt --build-arg BASEOS=ubuntu --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=1604 -t electriccoinco/votecoind-bbworker-ubuntu1604
docker push electriccoinco/votecoind-bbworker-ubuntu1604

# Ubuntu 18.04, 20.04
docker build . -f Dockerfile-build.apt --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=18.04 -t electriccoinco/votecoind-build-ubuntu1804
docker build . -f Dockerfile-build.apt --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=20.04 -t electriccoinco/votecoind-build-ubuntu2004
docker push electriccoinco/votecoind-build-ubuntu1804
docker push electriccoinco/votecoind-build-ubuntu2004
docker build . -f Dockerfile-gitian.apt --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=1804 -t electriccoinco/votecoind-gitian-ubuntu1804
docker build . -f Dockerfile-gitian.apt --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=2004 -t electriccoinco/votecoind-gitian-ubuntu2004
docker push electriccoinco/votecoind-gitian-ubuntu1804
docker push electriccoinco/votecoind-gitian-ubuntu2004
docker build . -f Dockerfile-bbworker.apt --build-arg BASEOS=ubuntu --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=1804 -t electriccoinco/votecoind-bbworker-ubuntu1804
docker build . -f Dockerfile-bbworker.apt --build-arg BASEOS=ubuntu --build-arg FROMBASEOS=ubuntu --build-arg FROMBASEOS_BUILD_TAG=2004 -t electriccoinco/votecoind-bbworker-ubuntu2004
docker push electriccoinco/votecoind-bbworker-ubuntu1804
docker push electriccoinco/votecoind-bbworker-ubuntu2004

# Centos8
docker build . -f Dockerfile-build.centos8 -t electriccoinco/votecoind-build-centos8
docker build . -f Dockerfile-bbworker.centos8  -t electriccoinco/votecoind-bbworker-centos8
docker push electriccoinco/votecoind-build-centos8
docker push electriccoinco/votecoind-bbworker-centos8

# Arch 20200908
docker build . -f Dockerfile-build.arch --build-arg ARCHLINUX_TAG=20200908 -t electriccoinco/votecoind-build-arch
docker build . -f Dockerfile-bbworker.arch  -t electriccoinco/votecoind-bbworker-arch
docker push electriccoinco/votecoind-build-arch
docker push electriccoinco/votecoind-bbworker-arch