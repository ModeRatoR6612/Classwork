#include  <iostream>

double prob ( int value, int dice) {
    if (value >= 1 && value <= dice) {
        return 1.0 / dice;
    }
    return 0;
}

double prob_set(int value, int dice, size_t count) {
    if (count == 1) {
        return prob(value, dice);
    }
    if (value > dice * count || value < count) {
        return 0;
    }
    double p = 0;
    for (int i = 1; i <= dice; ++i) {
        double pi = prob(i, dice) * prob_set(value - i, dice, count - 1);
        p+=pi;
    }

    return p;
}

double prob_set_segment(int a, int b, int dice, size_t count) {
    double p = 0;
    for (int i = a; i <= b; ++i) {
        p += prob_set(i, dice, count);
    }
    return p;
}

double prob_set_segment_new(int a, int b, int dice, size_t count) {
    double p = 0;
    for (int i = a; i <= b; ++i) {
        p += prob_set(i, dice, count);
    }
    return p;
}


double diff_cubiks(int a, int b, const int * dice, size_t count) {
    double p = 0;
    for (size_t i= 0; i < count; ++i) {
        for (int j = a; j <= b; ++j) {
            p += prob_set(j, dice[i], count);
        }
    }
    return p;
}

int main() {
    int count = 3;
    int dices[count] = {3, 4, 5};
    std::cout << prob_set(10, 6, 2) << '\n';
    std::cout << prob_set_segment(2, 4, 4, 2) << '\n';
    std::cout << diff_cubiks(2, 4, dices, count) << '\n';
}