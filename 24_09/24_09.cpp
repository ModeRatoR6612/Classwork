#include <iostream>

void count_primes(bool * isNotPrime, size_t n) {
    if ( n < 2 ) return;
    for (size_t i = 2; i < n; ++i) {
        if (isNotPrime[i]) {
            continue;
        }
        for ( size_t j = 2*i; j < n; j += i ) {
            isNotPrime[j] = true;
        }
    }
}

int main() {
    const size_t N = 50;
    bool isNotPrime[N] = {};
    count_primes(isNotPrime, N);

    for (size_t i = 0; i < N; i++) {
        if (!isNotPrime[i]) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}