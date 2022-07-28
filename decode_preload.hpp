#pragma once

#include "base.hpp"

namespace decode_preload {
FILE* fp;
inline void pt(int c) {
    fputc(c, fp);
}
void w(int x) {
    if (x >= 10) w(x / 10);
    pt(x % 10 + '0');
}
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
}  // namespace decode_preload

inline void compress(int x, int y, int clk, FILE* _fp) {
    using namespace decode_preload;
    fp = _fp;
    w(x);
    pt(32);
    w(y >> 1);
    pt(32);
    w(clk);
    // pt(32);
    // pt(10);
    pt(10);
}

inline int play_preload(
    std::string video,
    std::string audio,  // default use video
    int not_clear = 0,
    int play_audio = 0) {
    using namespace decode_preload;

    fp = fopen(video.c_str(), "r");

    const int x = r();
    const int y = r();
    const int clk = r();

    printf("[%d:%d %.2lfHz]\n", x, y, CLOCKS_PER_SEC / (double)clk);

    const int print_size = (x + 1) * y;
    char* buffer = (char*)malloc(print_size + 2);
    clock_t t0, t1;
#ifdef DEBUG
    printf("BEGINNING... [debug]\n");
    fflush(stdout);
    second_sleep(3);
#else
    printf("BEGINNING...\n");
    fflush(stdout);
    second_sleep(1);
#endif
    if (audio.length())
        playa(audio);
    else if (play_audio)
        playa(video);
    printf(not_clear ? "\n" : "\x1b[256F\x1b[0J");
    t0 = clock();

    for (auto i = 0;; i++) {
        if ((print_size + 1) ^ fread(buffer, 1, print_size + 1, fp)) {
            if (!i) {
                throws("The first frame is empty.");
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
