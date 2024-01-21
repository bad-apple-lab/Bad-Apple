#pragma once

#include "base.hpp"

class Printer : public Outer {
private:
    Timer *timer;
    int not_clear;

public:
    LL clk;
    Printer(
        std::string audio,
        LL clk,
        int _not_clear,
        int play_audio,
        int debug) : not_clear(_not_clear) {
        timer = new Timer(clk);
        timer->slp(debug ? 3 : 1);
        if (play_audio) {
            playa(audio);
        }
        printf(not_clear ? "\n" : "\x1b[256F\x1b[0J");
        fflush(stdout);
        timer->bg();
    }

    virtual inline void print_a_frame(char *buffer, int print_size) {
        printf(not_clear ? "\n" : "\x1b[256F");
        fwrite(buffer, 1, print_size, stdout);
        fflush(stdout);
        timer->wait();
    }
};
