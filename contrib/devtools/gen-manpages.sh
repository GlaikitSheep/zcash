#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

VOTECOIND=${VOTECOIND:-$SRCDIR/votecoind}
VOTECOINCLI=${VOTECOINCLI:-$SRCDIR/votecoin-cli}
VOTECOINTX=${VOTECOINTX:-$SRCDIR/votecoin-tx}

[ ! -x $VOTECOIND ] && echo "$VOTECOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a VOTVERSTR <<< "$($VOTECOINCLI --version | head -n1 | awk '{ print $NF }')"
read -r -a VOTVER <<< "$(echo $VOTVERSTR | awk -F- '{ OFS="-"; NF--; print $0; }')"
read -r -a VOTCOMMIT <<< "$(echo $VOTVERSTR | awk -F- '{ print $NF }')"

# Create a footer file with copyright content.
# This gets autodetected fine for votecoind if --version-string is not set,
# but has different outcomes for votecoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$VOTECOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $VOTECOIND $VOTECOINCLI $VOTECOINTX; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=$VOTVER --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-$VOTCOMMIT//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
