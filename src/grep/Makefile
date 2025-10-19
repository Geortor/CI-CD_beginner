SHELL := /bin/bash
CC = gcc
FLAG = -Wall -Wextra -Werror
FILE = test.txt

all: grep

grep: grep.c
	$(CC) $(FLAG) grep.c -o ../artifacts/grep

tests:
	-diff <(../artifacts/grep so $(FILE)) <(grep so $(FILE))
	-diff <(../artifacts/grep -e so $(FILE)) <(grep -e so $(FILE))
	-diff <(../artifacts/grep -i so $(FILE)) <(grep -i so $(FILE))
	-diff <(../artifacts/grep -v so $(FILE)) <(grep -v so $(FILE))
	-diff <(../artifacts/grep -c so $(FILE)) <(grep -c so $(FILE))
	-diff <(../artifacts/srep -l so $(FILE)) <(grep -l so $(FILE))
	-diff <(../artifacts/grep -n so $(FILE)) <(grep -n so $(FILE))

clean:
	rm -rf *.o grep

rebuild: clean all
