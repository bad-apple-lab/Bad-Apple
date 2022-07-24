#pragma once

#define DEBUG true

#include <iostream>
#include "consola_0_0ff.h"

#define LL long long
#define ULL unsigned long long
#define B unsigned char
#define pt putchar
#define gt getchar

inline void throws(const char *s) {
    throw std::runtime_error(std::string(s));
}

class VideoProperties {
public:
    int width, height, nb_frames = 1;
    double rate, duration = 0.0;
};

const int MAXCOL = 0x100;
char map[MAXCOL][MAXCOL];

class Font {
private:
    char o[MAXCOL][MAXCOL];
    FILE *f;
    inline int g() {
        int c = getc(f);
        while (c == 13 || c == 10) {
            c = getc(f);
        }
        return c;
    }
    inline void init() {
        for (auto i = 0; i < MAXCOL; i++) {
            std::memcpy(o[i], default_map[i], sizeof(default_map[i]));
        }
    }
    inline void init(const char *s) {
        if (!strlen(s)) {
            init();
            return;
        }
        f = fopen(s, "r");
        if (!f) {
            init();
            return;
        }
        for (auto i = 0; i < MAXCOL; i++) {
            for (auto j = 0; j < MAXCOL; j++) {
                g();
                o[i][j] = g();
            }
        }
        fclose(f);
    }

public:
    Font() { init(); }
    Font(const char *s) { init(s); }
    Font(std::string s) { init(s.c_str()); }
    char get(int x, int y) { return o[x][y]; }
};
