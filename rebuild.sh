#! /bin/bash

gcc -Wall -std=c99 -o HiddenInPlainText  src/*.c src/gamestate/*.c -l caca -l m
