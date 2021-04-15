FROM debian:10

RUN apt-get update \
  && apt-get install -y gnupg2 apt-transport-https curl

ARG VOTECOIN_SIGNING_KEY_ID=6DEF3BAF272766C0

ARG VOTECOIN_VERSION=
# The empty string for VOTECOIN_VERSION will install the apt default version,
# which should be the latest stable release. To install a specific
# version, pass `--build-arg 'VOTECOIN_VERSION=<version>'` to `docker build`.

ARG VOTECOIND_USER=votecoind
ARG VOTECOIND_UID=2001

RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys $VOTECOIN_SIGNING_KEY_ID \
  && echo "deb [arch=amd64] https://apt.z.cash/ stretch main" > /etc/apt/sources.list.d/votecoin.list \
  && apt-get update

RUN if [ -z "$VOTECOIN_VERSION" ]; \
    then apt-get install -y votecoin; \
    else apt-get install -y votecoin=$VOTECOIN_VERSION; \
    fi; \
    votecoind --version

RUN useradd --home-dir /srv/$VOTECOIND_USER \
            --shell /bin/bash \
            --create-home \
            --uid $VOTECOIND_UID\
            $VOTECOIND_USER
USER $VOTECOIND_USER
WORKDIR /srv/$VOTECOIND_USER
RUN mkdir -p /srv/$VOTECOIND_USER/.votecoin/ \
    && touch /srv/$VOTECOIND_USER/.votecoin/votecoin.conf

ADD entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
