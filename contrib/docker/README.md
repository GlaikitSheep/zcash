# votecoin Dockerfile

This is an example Dockerfile to run the votecoind daemon in a containerized Debian base OS. The image pulls the apt package built by Electric Coin Company.

The output of building this image should be accessible at https://hub.docker.com/r/electriccoinco/votecoind

## Defaults

The image will run as a non-root user, `votecoind` with uid `2001`. When mapping volumes from the host into the container, these permissions must be used, or rebuild the image with your custom values.

## Run time configuration

The goal is to follow the default votecoind startup behavior as closely as possible.

At startup, the image will execute the [./entrypoint.sh](./entrypoint.sh) script. This script uses environmental variables to configure the command line parameters, do a little house cleaning, and start votecoind.

### Available environment variables

If defined, the value is assigned to the value of the corresponding flag.

```
VOTECOIND_NETWORK
VOTECOIND_LOGIPS
VOTECOIND_EXPERIMENTALFEATURES
VOTECOIND_GEN
VOTECOIND_ZSHIELDCOINBASE
VOTECOIND_RPCUSER
VOTECOIND_RPCPASSWORD
VOTECOIND_RPCBIND
VOTECOIND_ALLOWIP
VOTECOIND_TXINDEX
VOTECOIND_INSIGHTEXPLORER
VOTECOIND_ZMQPORT
VOTECOIND_ZMQBIND
```

### Additional configuration

Any provided command line parameters are passed from the entrypoint.sh script to votecoind.

You can skip using environmental variables at all, and instead provide a fully configured `votecoin.conf` file and map to `/srv/votecoind/.votecoin/votecoin.conf` at startup.

## Examples

### See the installed version

This command will create a container, print the version information of the votecoind software installed and then exit and remove the container.

Run
```
docker run --rm electriccoinco/votecoind --version
```

Output
```
VoteCoin Daemon version v2.1.0-1

In order to ensure you are adequately protecting your privacy when using VoteCoin,
please see <https://z.cash/support/security/>.

Copyright (C) 2009-2019 The Bitcoin Core Developers
Copyright (C) 2015-2019 The VoteCoin Developers

This is experimental software.

Distributed under the MIT software license, see the accompanying file COPYING
or <https://www.opensource.org/licenses/mit-license.php>.
```

### Persist data to the host

For this example, we'll create a place for votecoind to store the blockchain data, create a new container that uses that location, and run it in the background.

```
mkdir {./zcash-params-dir,./votecoin-data-dir}
sudo chown -R 2001.2001 {./zcash-params-dir,./votecoin-data-dir}
docker run -d --name my_votecoind \
  -v $(pwd)/votecoin-data-dir:/srv/votecoind/.votecoin \
  -v $(pwd)/zcash-params-dir/srv/votecoind/.zcash-params \
  electriccoinco/votecoind
```  

Follow the logs to see its activity.

```
docker logs -f my_votecoind
```
