#include <getopt.h>
#include <stdio.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int v;
  int t;
} flag;

struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                {"number", no_argument, 0, 'n'},
                                {"squeeze-blank", no_argument, 0, 's'},
                                {0, 0, 0, 0}};

flag flagGet(int argc, char *argv[]) {
  int opt;
  flag fl = {0};
  int option_index = 0;
  while ((opt = getopt_long(argc, argv, "beEntTnvs", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        fl.b = 1;
        fl.n = 1;
        break;
      case 'e':
        fl.e = 1;
        fl.v = 1;
        break;
      case 'E':
        fl.e = 1;
        break;
      case 'n':
        if (!fl.b) fl.n = 1;
        break;
      case 's':
        fl.s = 1;
        break;
      case 't':
        fl.t = 1;
        fl.v = 1;
        break;
      case 'T':
        fl.t = 1;
        break;
      case 'v':
        fl.v = 1;
        break;
      default:
        printf("Неизвестная опция: %c\n", opt);
    }
  }
  return fl;
}

void show_non_printing(char curSym) {
  if ((signed char)curSym < 0) {
    printf("M-");
    curSym = (signed char)curSym + 128;
    if ((curSym >= 0 && curSym < 32) || curSym == 127) {
      printf("^");
      curSym += 64;
    }
    putc(curSym, stdout);
  } else if (curSym < 32 || curSym == 127) {
    if (curSym == '\n') {
      putchar(curSym);
    } else if (curSym == '\t') {
      printf("^I");
    } else {
      printf("^");
      curSym += 64;
      putc(curSym, stdout);
    }
  } else {
    putc(curSym, stdout);
  }
}

void print_char(int c, flag fl) {
  if ((fl.v && (unsigned char)c >= 128) ||
      ((fl.v && (c < 32 && c != '\n' && c != '\t')) || (c == 127))) {
    show_non_printing(c);
  } else {
    putchar(c);
  }
}

void print_line_end(flag fl) {
  if (fl.e) {
    putchar('$');
  }
}

void Cat_open(char *name, flag fl, int *line_number) {
  FILE *f = fopen(name, "rt");
  if (f != NULL) {
    int c;
    int prev = '\n';
    int empty_line_count = 0;

    while ((c = fgetc(f)) != EOF) {
      if (fl.s && prev == '\n' && c == '\n') {
        empty_line_count++;
        if (empty_line_count > 1) {
          continue;
        }
      } else {
        empty_line_count = 0;
      }

      if (prev == '\n' && (fl.n || (fl.b && c != '\n'))) {
        if (!(fl.b && c == '\n')) {
          printf("%6d\t", (*line_number)++);
        }
      }

      if (c == '\n') {
        print_line_end(fl);
        putchar(c);  // перенос строки
      } else if (c == '\t' && fl.t) {
        printf("^I");
      } else {
        print_char(c, fl);
      }

      prev = c;
    }

    if (fl.e && prev != '\n') {
      print_line_end(fl);
    }

    fclose(f);
  } else {
    printf("Я не нашел твой файл: %s\n", name);
  }
}

int main(int argc, char **argv) {
  flag fl = flagGet(argc, argv);

  if (optind == argc) {
    printf("Нет файлов для обработки\n");
    return 1;
  }

  int line_number = 1;

  for (int i = optind; i < argc; i++) {
    Cat_open(argv[i], fl, &line_number);
  }

  return 0;
}