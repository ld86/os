#!/bin/bash

while [[ 1 ]]; do nc $1 $2 | perl -ne 's/(.{20})/$1\n/g; print'; sleep 0.1; clear; done
