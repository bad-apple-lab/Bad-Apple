#pragma once

#include <iostream>
#include <cstring>
#include <ctime>
#include <chrono>

#include "winux.hpp"
#include "font/consola_ascii_0_ff.h"

#define LL long long
#define B unsigned char

inline int endswith(std::string s, std::string sub) {
    return s.rfind(sub) < s.length() && s.rfind(sub) == (s.length() - sub.length());
}

inline void throws(const char *s) {
    throw std::runtime_error(std::string(s));
}

inline void playa(std::string audio) {
    std::string cmd = "ffplay -v quiet -nodisp -autoexit -hide_banner \"" + audio + "\"";
    system(background_process(cmd).c_str());
}

class Timer {
private:
    std::chrono::steady_clock::time_point t0;

public:
    LL clk;
    Timer(LL c) : clk(c) {}
    void bg() {
        t0 = std::chrono::steady_clock::now();
    }
    int wait() {
        auto t1 = std::chrono::steady_clock::now();
        while ((LL)std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() < clk) {
            t1 = std::chrono::steady_clock::now();
        }
        t0 = t1;
        return 0;
    }
    void slp(int s) {
        second_sleep(s);
    }
};

class VideoProperties {
public:
    int width, height, nb_frames = 1;
    double rate, duration = 0.0;
};

class Decoder {
public:
    std::string video;
    int x, y, xy;

    Decoder(std::string _video) { video = _video; }
    virtual VideoProperties *analysis() {}
    virtual inline int ready_to_read(int _x, int _y) {
        x = _x;
        y = _y;
        xy = x * y;
        return 0;
    }
    virtual inline int read_a_frame(B *f) {}
    virtual inline void cls() {
        return;
    }
};

class Encoder {
public:
    int x, y, mo = 1, print_size;
    LL clk;
    char *buffer;
    virtual int read_a_frame() {}
    virtual void refresh_buffer() {}
    virtual void cls() {}
};

const int MAXCOL = 0x100;

class Font {
private:
    char o[MAXCOL][MAXCOL];
    FILE *f;
    inline int g() {
        int c = getc(f);
        while (c == '\n' || c == '\r') {
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
