#include <iostream>

int ** concat_rows(
  const int * const * lhs, size_t n1, size_t m1,
  const int * const * rhs, size_t n2, size_t m2
) {
  int ** cols = new int * [n1+n2];

  for (size_t i=0; i<n1+n2; i++) {

  }

  for (size_t i=0; i<n1+n2; i++) {
    for (size_t j=0; j<m1; j++) {
      cols[i][j] = lhs[i][j];
    }
    for (size_t j=0; j<m2; j++) {
      cols[i][j] = rhs[i][j];
    }
  }
}