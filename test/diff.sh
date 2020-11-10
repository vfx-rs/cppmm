#!/usr/bin/env bash

for f in \
    c-typedesc.cpp \
    c-typedesc.h  \
    c-imageio.cpp  \
    c-imageio.h  \
    c-filesystem.cpp \
    c-filesystem.h;
    do diff $f ../test/oiio_min/example_output/$f; done

for f in \
    half.cpp half.h
    do diff $f ../test/half/example_output/$f; done
