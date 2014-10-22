#!/bin/bash
# a very specific testing script. Written to speed up testing process
if [ $# -ne 1 ]
then
    echo "please supply a test to run"
    exit 1
fi
    echo "im making test no $1"
    make
    ./hw2.out < allanShit/s$1.in > outputs/m$1.out
    ./hw2.mac < allanShit/s$1.in > outputs/a$1.out
    echo "i just ran tests!"
    diff outputs/a$1.out outputs/m$1.out > outputs/cmp$1
    echo "i just diff'd"
    cat outputs/cmp$1