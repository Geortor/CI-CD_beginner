CC = gcc
FLAG = -Wall -Wextra -Werror --std=c11

all: s21_cat

s21_cat: cat.c
	$(CC) $(FLAG) cat.c -o ../artifacts/s21_cat

clean:
	rm -rf *.o ../artifacts/s21_cat

rebuild: clean all
