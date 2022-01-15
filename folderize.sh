#!/usr/bin/env bash

for i in {19..1}; do
    value=$(printf "%02d" $i)
    echo "$i"
    mkdir "$value"
    mv "$i"*.* "$value" 
done