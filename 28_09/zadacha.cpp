#include <iostream>

void rm(int ** arr, size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    delete [] arr[i];
  }
  delete [] arr;
}

void print(int ** arr, size_t rows, const size_t * lns) {
  std::cout << arr[0][0];
  for (size_t j = 1; j < lns[0]; ++j) {
    std::cout << ' ' << arr[0][j];
  }

  for (size_t i = 1; i < rows; ++i) {
    std::cout << '\n' << arr[i][0];
    for (size_t j = 1; j < lns[i]; ++j) {
      std::cout << ' ' << arr[i][j];
    }
  }
  std::cout << '\n';
}

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows) {
  int ** arr = new int* [rows]();
  for (size_t i = 0; i < rows; i++) {
    arr[i] = new int [lns[i]]();
  }

  size_t p = 0;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < lns[i]; j++) {
      arr[i][j] = *(t + p);
      p++;
    }
  }

  return arr;
}

int main() {
  size_t rows = 4;
  size_t lns[4] = {4, 2, 4, 1};
  size_t n = 11;
  int t[11] = {5, 5, 5, 5, 6, 6, 7, 7, 7, 7, 8};

  int ** arr = convert(t, n, lns, rows);
  print(arr, rows, lns);
  rm(arr, rows);

  return 0;
}
