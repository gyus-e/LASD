#!/bin/bash
make -f makefile.valgrind -j
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-error-list=yes --verbose --log-file=valgrind.log ./main > out.txt
cat valgrind.log