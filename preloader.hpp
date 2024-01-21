#pragma once

#include "base.hpp"

class Preloader {
private:
    FILE* fp;
    inline void pt(int c) {
        fputc(c, fp);
    }
    void w(int x) {
        if (x >= 10) w(x / 10);
        pt(x % 10 + '0');
    }

public:
    Preloader(int x, int y, int clk, FILE* _fp) {
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
};
