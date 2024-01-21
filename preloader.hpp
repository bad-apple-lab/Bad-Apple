#pragma once

#include "base.hpp"

class Preloader : public Outer {
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
    Preloader(std::string output, int x, int y, int clk) {
        fp = fopen(output.c_str(), "w");
        if (!fp) {
            throws("Open output file failed.");
            return;
        }
        w(x);
        pt(32);
        w(y >> 1);
        pt(32);
        w(clk);
        // pt(32);
        // pt(10);
        pt(10);
    }

    inline void print_a_frame(char* buffer, int print_size) {
        fwrite(buffer, 1, print_size + 1, fp);
    }

    inline void close() { fclose(fp); }
};
