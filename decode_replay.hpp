#pragma once

#include "base.hpp"

namespace decode_replay {
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
}  // namespace decode_replay

inline void compress(int x, int y, int clk, FILE* _fp) {
    using namespace decode_replay;
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

inline int replay(
    std::string video,
    std::string audio,
    int not_clear = 0,
    int play_audio = 0) {
    using namespace decode_replay;

    fp = fopen(video.c_str(), "r");

    const int x = r();
    const int y = r();
    const int clk = r();

    printf("[%d:%d %.2lfHz]\n", x, y, CLOCKS_PER_SEC / (double)clk);

    const int print_size = (x + 1) * y;
    char* buffer = (char*)malloc(print_size + 2);
    Timer *timer=new Timer(clk);

#ifdef DEBUG
    printf("BEGINNING... [replay] [debug]\n");
    fflush(stdout);
    timer->slp(3);
#else
    printf("BEGINNING... [replay]\n");
    fflush(stdout);
    timer->slp(1);
#endif
    if (play_audio) {
        playa(audio);
    }
    printf(not_clear ? "\n" : "\x1b[256F\x1b[0J");
    fflush(stdout);
    timer->bg();

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
        timer->wait();
    }

    fclose(fp);
    return 0;
}
