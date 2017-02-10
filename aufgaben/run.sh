#!/bin/bash


program_args=$1
CFLAGS="-DDEBUG -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -fno-common -g -O3 -std=gnu11"

gcc $CFLAGS $program_args $2 $3  || exit 

#Run program and report memory leak cases
valgrind ./a.out

echo "cleaning up"
rm -f *.out
