#pragma once

#include <iostream>
#include <cstring>
#include <ctime>

#include "winux.hpp"
#include "font/consola_ascii_0_ff.h"

#define LL long long
#define B unsigned char

inline int endswith(std::string s,std::string sub){
    return s.rfind(sub)==(s.length()-sub.length())?1:0;
}

inline void throws(const char *s) {
    throw std::runtime_error(std::string(s));
}

inline void playa(std::string audio) {
    std::string cmd = "ffplay -v quiet -nodisp -autoexit -hide_banner \"" + audio + "\"";
    system(background_process(cmd).c_str());
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
            std::memcpy(o[i], map65536[i], sizeof(map65536[i]));
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
