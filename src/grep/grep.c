#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int i;          // Игнорировать регистр
  int n;          // Номера строк
  int v;          // Инвертировать совпадения
  int e;          // Шаблон для поиска
  int l;          // Печать только имен файлов
  int c;          // Подсчет строк с совпадениями
  char *pattern;  // Шаблон для поиска
} flag;

// Функция для обработки флагов
flag flagGet(int argc, char *argv[]) {
  int opt;
  flag fl = {0, 0, 0, 0, 0, 0, NULL};
  while ((opt = getopt(argc, argv, "inevlc")) != -1) {
    switch (opt) {
      case 'i':
        fl.i = 1;
        break;
      case 'n':
        fl.n = 1;
        break;
      case 'v':
        fl.v = 1;
        break;
      case 'e':
        fl.e = 1;
        if (optind < argc) {
          fl.pattern = argv[optind];
          optind++;
        }
        break;
      case 'l':
        fl.l = 1;
        break;
      case 'c':
        fl.c = 1;
        break;
      default:
        fprintf(stderr,
                "Использование: %s [-i] [-n] [-v] [-e шаблон] [-l] [-c] шаблон "
                "[файл...]\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  if (!fl.e && optind < argc) {
    fl.pattern = argv[optind];
    optind++;
  }
  return fl;
}

// Функция для открытия и чтения файла, и печати строк, совпадающих с шаблоном
void grepFile(char *filename, flag fl) {
  FILE *file = strcmp(filename, "-") == 0 ? stdin : fopen(filename, "r");
  if (file == NULL) {
    perror("fopen");
    return;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_num = 0;
  int match_count = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    line_num++;
    int match = 0;
    if (fl.i) {
      // Игнорировать регистр, конвертируя строку и шаблон в нижний регистр
      char *lower_line = strdup(line);
      char *lower_pattern = strdup(fl.pattern);
      for (int i = 0; lower_line[i]; i++)
        lower_line[i] = tolower(lower_line[i]);
      for (int i = 0; lower_pattern[i]; i++)
        lower_pattern[i] = tolower(lower_pattern[i]);
      match = strstr(lower_line, lower_pattern) != NULL;
      free(lower_line);
      free(lower_pattern);
    } else {
      match = strstr(line, fl.pattern) != NULL;
    }

    if (fl.v) {
      match = !match;
    }

    if (match) {
      match_count++;
      if (fl.l) {
        printf("%s\n", filename);
        break;
      } else if (!fl.c) {
        if (fl.n) {
          printf("%d:", line_num);
        }
        printf("%s", line);
      }
    }
  }

  if (fl.c) {
    printf("%d\n", match_count);
  }

  free(line);
  if (file != stdin) {
    fclose(file);
  }
}

int main(int argc, char **argv) {
  flag f = flagGet(argc, argv);

  if (f.pattern == NULL) {
    fprintf(stderr, "Ожидается шаблон\n");
    exit(EXIT_FAILURE);
  }

  if (optind == argc) {
    // Чтение из stdin, если файлы не указаны
    grepFile("-", f);
  } else {
    for (int i = optind; i < argc; i++) {
      grepFile(argv[i], f);
    }
  }

  return 0;
}
