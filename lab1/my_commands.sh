#!/usr/bin/env bash
./echo_arg csc209 > echo_out.txt
./echo_stin < echo_stdin.c
./count 209 | wc
ls -S | head -1 | ./echo_stdin
