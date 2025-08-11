extern void abort(void);
extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__((__nothrow__, __leaf__))
__attribute__((__noreturn__));
void reach_error() { __assert_fail("0", "EvenOdd03.c", 3, "reach_error"); }

/*
 * Recursive implementation integer addition.
 *
 * Author: Matthias Heizmann
 * Date: 2013-07-13
 *
 */

extern int __VERIFIER_nondet_int(void);

int isOdd(int n);
int isEven(int n);

// returns 1 if the input n is odd
int isOdd(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return isEven(n - 1);
    }
}

// returns 1 if the input n is even
int isEven(int n) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 0;
    } else {
        return isOdd(n - 1);
    }
}

int main() {
    int n = __VERIFIER_nondet_int();
    if (n < 0 || n > 400) return 0;

    int result = isEven(n);  // 1 if even, 0 if odd
    int mod = n % 2;         // 0 if even, 1 if odd

    if (result < 0 || result == mod) {
        return 0;
    } else {
    // our case
    ERROR: {
        reach_error();
        abort();
    }
    }
}
