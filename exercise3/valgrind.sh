#!/bin/bash
make -f makefile.valgrind -j6
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-error-list=yes --verbose --log-file=valgrind.log ./main > output.txt
cat valgrind.log