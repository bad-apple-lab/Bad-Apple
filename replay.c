// for embedded device

#include <time.h>
#include <stdio.h>

inline void second_sleep(int x) {
#if defined(__WINDOWS_) || defined(_WIN32)
    Sleep(x * 1000);
#else
    sleep(x);
#endif
}

FILE* fp;
inline int gt() {
    return getc(fp);
}
inline int r() {
    int c = gt();
    while (c < '0' || '9' < c) {
        c = gt();
    }
    int ans = 0;
    while ('0' <= c && c <= '9') {
        ans = (ans << 1) + (ans << 3) + c - '0';
        c = gt();
    }
    return ans;
}

int main(int argc, char** argv) {
    int not_clear = 1;

    fp = fopen("badapple.mp4.badapple", "r");

    const int x = r();
    const int y = r();
    const int clk = r();

    printf("[%d:%d %.2lfHz]\n", x, y, CLOCKS_PER_SEC / (double)clk);

    const int print_size = (x + 1) * y;
    char* buffer = (char*)malloc(print_size + 2);
    clock_t t0, t1;
    printf("BEGINNING... [replay]\n");
    fflush(stdout);
    second_sleep(1);
    printf(not_clear ? "\n" : "\x1b[256F\x1b[0J");
    t0 = clock();

    int i;
    for (i = 0;; i++) {
        if ((print_size + 1) ^ fread(buffer, 1, print_size + 1, fp)) {
            if (!i) {
                printf("The first frame is empty.");
                return 1;
            }
            break;
        }
        printf(not_clear ? "\n" : "\x1b[256F");
        fwrite(buffer, 1, print_size, stdout);
        fflush(stdout);
        t1 = clock();
        while (t1 - t0 < clk) {
            t1 = clock();
        }
        t0 = t1;
    }

    fclose(fp);
    return 0;
}
