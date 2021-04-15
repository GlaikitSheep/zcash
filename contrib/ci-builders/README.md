# votecoind ci Docker images

These Dockerfiles can be used to build votecoind.

The current objective is to build a base image for each distribution that includes the system packages to build votecoind. From `build` images, more targeted images are created.

The process is meant to be automated, but an example `docker-build.sh` script is included.


## build images
`apt-package-list.txt` contains the required packages for debian based systems.

`Dockerfile-build.apt` uses that file, and some build time arguments, to build apt based build images.

Currently available images are hosted at
https://hub.docker.com/r/electriccoinco/votecoind-build/tags


## gitian images

`Dockerfile-gitian.apt` uses the build images to generate images for use with [gitian-builder](https://github.com/devrandom/gitian-builder)

Currently available images are hosted at https://hub.docker.com/r/electriccoinco/votecoind-gitian/tags


## bbworker images

`Dockerfile-bbworker.apt` uses the build images for use with [buildbot](https://buildbot.net)

- bbworker-buildbot.tac is a required worker boot file (most is overridden at instancitation)
- bbworker-requirements.txt is the python package requirements for the buildbot worker

Currently available images are hosted at https://hub.docker.com/r/electriccoinco/votecoind-bbworker/tags


### Stand alone, best effort images

Additional buildbot workers for Centos8 and Arch.

- Dockerfile-bbworker.arch
- Dockerfile-bbworker.centos8

