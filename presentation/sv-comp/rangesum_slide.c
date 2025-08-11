/*
 * Benchmarks used in the paper "Commutativity of Reducers"
 * which was published at TACAS 2015 and
 * written by Yu-Fang Chen, Chih-Duo Hong, Nishant Sinha, and Bow-Yaw Wang.
 * http://link.springer.com/chapter/10.1007%2F978-3-662-46681-0_9
 *
 * We checks if a function is "deterministic" w.r.t. all possible permutations
 * of an input array.  Such property is desirable for reducers in the
 * map-reduce programming model.  It ensures that the program always computes
 * the same results on the same input data set.
 */

extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }
extern int __VERIFIER_nondet_int(void);

int N;

void init_nondet(int x[N]) {
    int i;
    for (i = 0; i < N; i++) {
        x[i] = __VERIFIER_nondet_int();
    }
}

int rangesum(int x[N]) {
    int i, cnt = 0;
    long long ret = 0;

    // sum up array values
    for (i = 0; i < N; i++) {
        // a bug! only the second half is summed up...
        if (i > N / 2) {
            ret = ret + x[i];
            cnt = cnt + 1;
        }
    }

    // standard average
    if (cnt != 0)
        return ret / cnt;
    else
        return 0;
}

int main() {
    // array size
    N = __VERIFIER_nondet_int();
    if (N > 1) {
        int x[N], temp, ret1, ret2, ret3;
        // initialize the array
        init_nondet(x);

        // base sum
        ret1 = rangesum(x);

        // swap x[0] and x[1]
        temp = x[0];
        x[0] = x[1];
        x[1] = temp;
        ret2 = rangesum(x);

        // shift left (circularly)
        temp = x[0];
        for (int i = 0; i < N - 1; i++) {
            x[i] = x[i + 1];
        }
        x[N - 1] = temp;
        ret3 = rangesum(x);

        // compare results
        if (ret1 != ret2 || ret1 != ret3) {
            reach_error();
        }
    }
    return 1;
}
