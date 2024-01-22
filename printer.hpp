#pragma once

#include "base.hpp"

class Printer : public Outer {
private:
    Timer* timer;
    int not_clear;

public:
    LL clk;
    Printer(
        std::string video,
        std::string audio,
        LL clk,
        int _not_clear,
        int play_audio,
        int debug) : not_clear(_not_clear) {
        timer = new Timer(clk);
        timer->slp(debug ? 3 : 1);
        player_playa(video, audio, play_audio);
        printf(not_clear ? "\n" : "\x1b[256F\x1b[0J");
        fflush(stdout);
        timer->bg();
    }

    virtual inline void print_a_frame(char* buffer, int print_size) {
        printf(not_clear ? "\n" : "\x1b[256F");
        fwrite(buffer, 1, print_size, stdout);
        fflush(stdout);
        timer->wait();
    }
};

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
    Preloader(std::string output, int x, int y, int clk, int debug) {
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
