#include <iostream>

void copy(const int * src, size_t k, int * dst) {
  for (size_t i = 0; i < k; i++) {
    dst[i] = src[i];
  }
}

void paste(int * a, size_t k, int pasta) {
  for (size_t i = 0; i < k; i++) {
    a[i] = pasta;
  }
}

// void extend2_fs(int ** ptr_a, size_t k, size_t d, int fill) {
//
// }

int * extend_heap(const int * a, size_t k, size_t d, int fill) {
  int * arr = reinterpret_cast<int *>(malloc(sizeof(int) * (k+d)));
  if (arr != nullptr) {
    copy(a, k, arr);
    paste((arr + k), d, fill);
  }
  return arr;
}

int * extend_fs(const int * a, size_t k, size_t d, int fill) {
  int * arr = new int[k+d];
  copy(a, k, arr);
  paste((arr+k), d, fill);
  return arr;
}

int * add_row(const int * a, size_t n, size_t m, int fill) {
  return extend_fs(a, n*m, n, fill);
}

// n - столбцы
// m - строки

int * add_col(const int * a, size_t n, size_t m, int fill) {
  int * arr = new int[m * (n + 1)];
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      arr[i * (n + 1) + j] = a[i * n + j];
    }
    arr[i * (n + 1) + n] = fill;
  }
  return arr;
}

int main() {
  // const int a[] = {1, 2, 3, 4};
  // int * b = nullptr, * c = nullptr, * d = nullptr;
  // c = extend_heap(a, 4, 5, 0);
  // if (!c) {
  //   std::cerr << "bad alloc\n";
  //   return 1;
  // }
  // try {
  //   b = extend_fs(a, 4, 5, 0);
  //   d = extend_fs(a, 4, 5, 0);
  //   // extend2_fs(d, 14, 10, 10);
  // } catch (...) {
  //   delete[] b;
  //   delete[] d;
  //   free(c);
  //   free(d);
  //   std::cerr << "Bad alloc" << '\n';
  // }
  //
  // // to do
  //
  // free(c);
  // delete[] d;
  // delete[] b;
  const int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int n = 3; int m = 3;
  int * arr = add_col(a, n, m, 0);

  for (size_t i = 0; i < n*m; i++) {
    std::cout << arr[i] << std::endl;
  }
  delete[] arr;
  return 0;
}
