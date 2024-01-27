#pragma once

#include <chrono>

#include "winux.hpp"

#define B unsigned char
#define LL long long

const int BUF_SIZE = 1 << 8;

inline int endswith(std::string s, std::string sub) {
    return s.rfind(sub) < s.length() && s.rfind(sub) == (s.length() - sub.length());
}

inline void throws(std::string s) {
    throw std::runtime_error(s);
}

inline int not_exist(std::string s) {
    FILE *fp;
    fp = fopen(s.c_str(), "rb");
    if (!fp) {
        return 1;
    }
    fclose(fp);
    return 0;
}

inline int exec_r(const char *cmd, char *res, int res_size = BUF_SIZE) {
    FILE *p = r_popen(cmd);
    if (!p) return -1;

    int t = 0;
    while (!feof(p)) {
        if (t + BUF_SIZE < res_size) {
            t += fread(res + t, 1, BUF_SIZE, p);
        } else {
            t += fread(res + t, 1, res_size - t - 1, p);
            break;
        }
    }

    pipe_pclose(p);
    res[t] = 0;
    return t;
}

class Timer {
private:
    std::chrono::steady_clock::time_point t0;

public:
    LL clk;
    Timer(LL c) : clk(c) {}
    inline void bg() {
        t0 = std::chrono::steady_clock::now();
    }
    inline int wait() {
        auto t1 = std::chrono::steady_clock::now();
        while ((LL)std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() < clk) {
            t1 = std::chrono::steady_clock::now();
        }
        t0 = t1;
        return 0;
    }
    inline void slp(int s) {
        second_sleep(s);
    }
};
