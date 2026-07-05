#!/bin/env bash

gcc xgetscr.c $(pkg-config --cflags --libs x11 xinerama) -o xgetscr
