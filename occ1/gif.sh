#!/usr/bin/env bash

if [ ! -e "$1" ]
then
    echo "$0 file.gif" >&2
    exit 1
fi

set -ex

cargo build --release

rm -rf build
mkdir -p build
convert "$1" build/frame.png
for frame in build/frame-*.png
do
    target/release/occ1 --new-algo --no-show --zoom "$frame" "build/$(basename "$frame" .png).asm" 14 23 0x16
    #ASCII output: jp2a --background=dark --width=35 "$frame" | tee "build/$(basename "$frame" .png).txt"
done
