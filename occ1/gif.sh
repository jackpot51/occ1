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
    target/release/occ1 --no-show --zoom "$frame" "build/$(basename "$frame" .png).asm" 10
    #ASCII output: jp2a --background=dark --width=35 "$frame" | tee "build/$(basename "$frame" .png).txt"
done
