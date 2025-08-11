int glbl;

int f(int x) {
    if (glbl > 0) {
        return x - 1;
    } else {
        glbl = 0;
        return x;
    }
}

int main(void) {
    int y;
    y = f(23);
}