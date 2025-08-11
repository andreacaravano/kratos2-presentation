extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) {
    if (!(cond)) {
    ERROR: {
        reach_error();
        abort();
    }
    }
}
extern int __VERIFIER_nondet_int();

// Limited for performance reasons...
#define N 5

int main() {
    int a[N];

    for (int j = 0; j < N; j++) {
        a[j] = __VERIFIER_nondet_int();
    }

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = 1; i < N; i++) {
            if (a[i - 1] > a[i]) {
                int t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                swapped = 1;
            }
        }
    }

    int x, y;
    for (x = 0; x < N; x++) {
        for (y = x + 1; y < N; y++) {
            // multiple assertions!
            __VERIFIER_assert(a[x] <= a[y]);
        }
    }
    return 0;
}
