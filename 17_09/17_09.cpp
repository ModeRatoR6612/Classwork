#include  <iostream>

unsigned int pow(int a, int p) {
    if (p == 0) return 1;
    if (p == 1) return a;
    if (p == 2) return a*a;
    return pow(a, p/2) * pow(a, p/2);
}

int main() {
    unsigned int a = 2; unsigned int p = 1;
    if (p % 2 == 0) {
        std::cout << pow(a, p);
    }
    else {
        std::cout << pow(a, p-1) * a << std::endl;
    }
}