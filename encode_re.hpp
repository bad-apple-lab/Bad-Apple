#pragma once

#include "base.hpp"

class Encoder_Re : public Encoder {
private:
    FILE *fp;
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
            ans = ans * 10 + c - '0';
            c = gt();
        }
        return ans;
    }
    Font *fnt;
    B *frame;
    int contrast;

public:
    Encoder_Re(std::string video, char* name, int _debug = 0) : Encoder(_debug) {
        fp = fopen(video.c_str(), "r");

        x = r();
        y = r();
        clk = r();

        printf("[%d:%d %.2lfHz] -%s-> [replay] %s\n",
               x, y, CLOCKS_PER_SEC / (double)clk,
               name, debug ? "[debug]" : "");

        print_size = (x + 1) * y;
        buffer = (char *)malloc(print_size + 2);
    }

    inline int read_a_frame() {
        return (print_size + 1) ^ fread(buffer, 1, print_size + 1, fp);
    }
};
