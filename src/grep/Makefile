SHELL := /bin/bash
CC = gcc
FLAG = -Wall -Wextra -Werror
FILE = test.txt

all: s21_grep

s21_grep: grep.c
	$(CC) $(FLAG) grep.c -o ../artifacts/s21_grep

tests:
	-diff <(../artifacts/s21_grep so $(FILE)) <(grep so $(FILE))
	-diff <(../artifacts/s21_grep -e so $(FILE)) <(grep -e so $(FILE))
	-diff <(../artifacts/s21_grep -i so $(FILE)) <(grep -i so $(FILE))
	-diff <(../artifacts/s21_grep -v so $(FILE)) <(grep -v so $(FILE))
	-diff <(../artifacts/s21_grep -c so $(FILE)) <(grep -c so $(FILE))
	-diff <(../artifacts/s21_grep -l so $(FILE)) <(grep -l so $(FILE))
	-diff <(../artifacts/s21_grep -n so $(FILE)) <(grep -n so $(FILE))

clean:
	rm -rf *.o s21_grep

rebuild: clean all
