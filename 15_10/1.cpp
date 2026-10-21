#include <iostream>

void mult(int * a, int * b, int * c, size_t m1, size_t n, size_t m2) {
  size_t p = 0;
  size_t b_c = 0;
  for (size_t i=0; i<m1*n; i++) {
    for (size_t j=0; j<m2; j++) {
      c[p] = a[]
    }
  }
}

int main() {
  int a[] = {1, 2, 3, 4, 5, 6};
  int b[] = {7, 8, 9, 0, 1, 2};

  size_t n = 3;
  size_t m1 = 2;
  size_t m2 = 3;

  int c[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  mult(a, b, c, m1, n, m2);

  for (size_t i=0; i<9; i++) {
    if (i == 3 || i == 6) {
      std::cout << '\n';
    }
    std::cout << c[i] << ' ';
  }

  return 0;
}
