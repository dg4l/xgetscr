#!/usr/bin/env bash

gcc xgetscr.c -O2 -g -lX11 -lXinerama -Wextra -pedantic -o xgetscr
