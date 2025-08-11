#include <assert.h>

int glbl = 0;

int f(int x) {
    if (glbl > 0) {
        return x - 1;
    } else {
        // our case
        glbl = 0;
        return x;
    }
}

void main(void) {
    int y;
    while (y > 0) {
        y = f(y);
    }

    // failure of the assertion
    // is an unreachable point!
    assert(glbl == 0);
}