#!/bin/sh

make clean
make TARGET=funkey

mkdir -p opk
cp temperature opk/temperature
cp -r ./fs opk/fs
cp Temperature.funkey-s.desktop opk/Temperature.funkey-s.desktop

mksquashfs ./opk Temperature.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk