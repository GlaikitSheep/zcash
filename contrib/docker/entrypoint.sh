#!/usr/bin/env bash

export LC_ALL=C
set -eo pipefail

if [[ ${1} == "--version" ]];then
  votecoind --version
  exit 0
fi

env | sort | grep VOTECOIND || true
export VOTECOIND_CMD='votecoind -printtoconsole'

if [[ ! -n ${VOTECOIND_NETWORK} ]];then
  export VOTECOIND_NETWORK=mainnet
fi

case ${VOTECOIND_NETWORK} in
  testnet)
    VOTECOIND_CMD+=" -testnet -addnode=testnet.z.cash "
    ;;
  mainnet)
    VOTECOIND_CMD+=" -addnode=mainnet.z.cash "
    ;;
  *)
    echo "Error, unknown network: ${VOTECOIND_NETWORK}"
    exit 1
    ;;
esac

if [[ -n "${VOTECOIND_SHOWMETRICS}" ]];then VOTECOIND_CMD+=" -showmetrics=${VOTECOIND_SHOWMETRICS}";fi
if [[ -n "${VOTECOIND_LOGIPS}" ]];then VOTECOIND_CMD+=" -logips=${VOTECOIND_LOGIPS}";fi
if [[ -n "${VOTECOIND_EXPERIMENTALFEATURES}" ]];then VOTECOIND_CMD+=" -experimentalfeatures=${VOTECOIND_EXPERIMENTALFEATURES}";fi
if [[ -n "${VOTECOIND_GEN}" ]];then VOTECOIND_CMD+=" -gen=${VOTECOIND_GEN}";fi
if [[ -n "${VOTECOIND_ZSHIELDCOINBASE}" ]];then VOTECOIND_CMD+=" -zshieldcoinbase=${VOTECOIND_ZSHIELDCOINBASE}";fi
if [[ -n "${VOTECOIND_RPCUSER}" ]];then VOTECOIND_CMD+=" -rpcuser=${VOTECOIND_RPCUSER}";fi
if [[ -n "${VOTECOIND_RPCPASSWORD}" ]];then VOTECOIND_CMD+=" -rpcpassword=${VOTECOIND_RPCPASSWORD}";fi
if [[ -n "${VOTECOIND_RPCBIND}" ]];then VOTECOIND_CMD+=" -rpcbind=${VOTECOIND_RPCBIND}";fi
if [[ -n "${VOTECOIND_RPCPORT}" ]];then VOTECOIND_CMD+=" -rpcport=${VOTECOIND_RPCPORT}";fi
if [[ -n "${VOTECOIND_ALLOWIP}" ]];then VOTECOIND_CMD+=" -rpcallowip=${VOTECOIND_ALLOWIP}";fi
if [[ -n "${VOTECOIND_TXINDEX}" ]];then VOTECOIND_CMD+=" -txindex";fi
if [[ -n "${VOTECOIND_INSIGHTEXPLORER}" ]];then VOTECOIND_CMD+=" -insightexplorer";fi
if [[ -n "${VOTECOIND_ZMQPORT}" && -n "${VOTECOIND_ZMQBIND}" ]];then
  VOTECOIND_CMD+=" -zmqpubhashblock=tcp://${VOTECOIND_ZMQBIND}:${VOTECOIND_ZMQPORT}"
  VOTECOIND_CMD+=" -zmqpubhashtx=tcp://${VOTECOIND_ZMQBIND}:${VOTECOIND_ZMQPORT}"
  VOTECOIND_CMD+=" -zmqpubrawblock=tcp://${VOTECOIND_ZMQBIND}:${VOTECOIND_ZMQPORT}"
  VOTECOIND_CMD+=" -zmqpubrawtx=tcp://${VOTECOIND_ZMQBIND}:${VOTECOIND_ZMQPORT}"
  VOTECOIND_CMD+=" -zmqpubhashblock=tcp://${VOTECOIND_ZMQBIND}:${VOTECOIND_ZMQPORT}"
fi

votecoin-fetch-params
touch .votecoin/votecoin.conf
echo "Starting: ${VOTECOIND_CMD}"
eval exec "${VOTECOIND_CMD}" "${@}"
