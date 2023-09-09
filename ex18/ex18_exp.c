#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*comparator)(int a, int b);

void die(const char *msg) {
  if (errno) {
    perror(msg);
  } else {
    printf("%s", msg);
  }
  exit(1);
}

void bubble_sort(int *list, int size, comparator comp) {
  int i = 0;
  int j, tmp;
  for (i = 0; i < size; ++i) {
    for (j = i + 1; j < size; ++j) {
      if (comp(list[j], list[i]) > 0) {
        tmp = list[j];
        list[j] = list[i];
        list[i] = tmp;
      }
    }
  }
}

void test_bubble_sort(int *list, int size, comparator comp) {
  int i = 0;
  bubble_sort(list, size, comp);
  for (i = 0; i < size; ++i) {
    printf("%d, ", list[i]);
  }
  printf("\n");
}

int soted_order(int a, int b) { return a > b; }

int reverse_order(int a, int b) { return b > a; }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    die("Usage: ex18_exp 12 3 123 15 44");
  }
  char **pointer = argv + 1;
  int size = argc - 1;

  int *list = malloc(size * sizeof(int));
  if (!list) {
    die("Can not malloc more space");
  }
  for (int i = 0; i < size; ++i) {
    list[i] = atoi(pointer[i]);
  }

  test_bubble_sort(list, size, soted_order);
  test_bubble_sort(list, size, reverse_order);

  free(list);
  return 0;
}
