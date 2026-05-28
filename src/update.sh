#! /usr/bin/env bash

printf "Compiling\n"
sudo gcc -shared -fPIC -o libcutils.so cutils.c

printf "Copying to /usr/lib\n"
sudo cp libcutils.so /usr/lib

sudo cp cutils.h /usr/include
sudo ldconfig

