// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2012-2021 The SV-Benchmarks Community
// SPDX-FileCopyrightText: 2012 FBK-ES <https://es.fbk.eu/>
//
// SPDX-License-Identifier: Apache-2.0

extern void abort(void);
void assume_abort_if_not(int cond) {
    if (!cond) {
        abort();
    }
}
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

extern unsigned int __VERIFIER_nondet_uint(void);
void __VERIFIER_assert(int cond) {
    if (!(cond)) {
    ERROR: {
        reach_error();
        abort();
    }
    }
    return;
}
/* https://graphics.stanford.edu/~seander/bithacks.html#ModulusDivisionEasy */
#include <assert.h>

int main() {
    /* Compute modulus division by (1 << s) - 1 without a division operator */
    unsigned int n = __VERIFIER_nondet_uint(); /* numerator */
    unsigned int s = __VERIFIER_nondet_uint(); /* s > 0 */
    // (s is less than 32 of course)
    unsigned int d;
    unsigned int m; /* n % d goes here. */
    assume_abort_if_not(s < 32);
    d = (1 << s) - 1; /* so d is either 1, 3, 7, 15, 31, ...) */

    if (d > 0) {
        m = n;           // n is the numerator, m will contain the result
        while (n > d) {  // iteratively reduces the operation span
            m = 0;
            while (n > 0) {  // incrementally builds up coefficients a_i
                m += n & d;  // extracts a_0
                n = n >> s;  // then, will form a_1...
            }
            n = m;
        }
        /* Now m is a value from 0 to d, but since with modulus division
         * we want m to be 0 when it is d. */
        if (m == d) {  // m could be d, so we make it circulating back to 0
            m = 0;
        }

        __VERIFIER_assert(m == n % d);
    }

    return 0;
}
