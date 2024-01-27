#pragma once

#include "font/consola_ascii_0_ff.h"

const int MAXCOL = 0x100;

class Font {
private:
    char o[MAXCOL][MAXCOL];
    FILE *fp;
    inline int g() {
        int c = getc(fp);
        while (c == '\n' || c == '\r') {
            c = getc(fp);
        }
        return c;
    }
    inline void init() {
        for (auto i = 0; i < MAXCOL; i++) {
            std::memcpy(o[i], map65536[i], sizeof(map65536[i]));
        }
    }
    inline void init(const char *s) {
        if (!strlen(s)) {
            init();
            return;
        }
        fp = fopen(s, "r");
        if (!fp) {
            init();
            return;
        }
        for (auto i = 0; i < MAXCOL; i++) {
            for (auto j = 0; j < MAXCOL; j++) {
                o[i][j] = g();
            }
        }
        fclose(fp);
    }

public:
    Font() { init(); }
    Font(const char *s) { init(s); }
    Font(std::string s) { init(s.c_str()); }
    char get(int x, int y) { return o[x][y]; }
};
