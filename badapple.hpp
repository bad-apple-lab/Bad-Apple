#pragma once

#define DEBUG false

#include <iostream>
#include <cstring>
#include <ctime>
#include "winux.hpp"
#include "consola_0_0ff.h"

#define LL long long
#define ULL unsigned long long
#define B unsigned char
#define pt putchar
#define gt getchar

inline void throws(const char *s) {
    throw std::runtime_error(std::string(s));
}

const int BUFFER_SIZE = 1 << 8;
const int STDOUT_SIZE = 1 << 20;
const int MAXCOL = 0x100;

inline int exec_r(const char *cmd, char *result) {
    FILE *pipe = r_popen(cmd);

    if (!pipe) return 1;
    int code = 0;

    int t = 0;
    while (!feof(pipe)) {
        fread(result + t, 1, BUFFER_SIZE, pipe);
        t += BUFFER_SIZE;
        if (t >= STDOUT_SIZE) {
            code = 2;
            break;
        }
    }
    pipe_pclose(pipe);

    return code;
}

FILE *f;
inline int g() {
    int c = getc(f);
    while (c == 13 || c == 10) {
        c = getc(f);
    }
    return c;
}

inline void ffplaya(std::string audio) {
    std::string cmd = "ffplay -v quiet -nodisp -autoexit -hide_banner \"" + audio + "\"";
    system(background_process(cmd).c_str());
}

inline int play(
    std::string video,
    std::string audio,  // default use video
    std::string font,   // default use map in "consola_0_0ff.h"
    int x,              // width
    int y,              // height
    int fps,            // rate
    int contrast_enhancement = 0,
    int play_audio = 0) {
    std::string cmd;

    // analysis video
    cmd = (std::string) "ffprobe -v quiet -show_streams -select_streams v \"" + video + "\"";
    // printf("%s\n", cmd.c_str());

    int width, height;
    double rate_l, rate_r;  // fps = rate_l / rate_r;
    double duration = 0.0;
    char result_c[STDOUT_SIZE];
    if (exec_r(cmd.c_str(), result_c)) {
        throws("Failed to analysis video.");
        return 1;
    } else {
        // sscanf(result, "%d%d%lf%d", &width, &height, &duration, &nb_frames);
        std::string result_s(result_c), _k;
        std::size_t p, p2;

        _k = "\nwidth=";
        p = result_s.find(_k);
        if (p == std::string::npos) {
            throws("This video has no width.");
            return 1;
        }
        p += _k.length();
        p2 = result_s.find("\n", p);
        sscanf(result_s.substr(p, p2 - p).c_str(), "%d", &width);

        _k = "\nheight=";
        p = result_s.find(_k);
        if (p == std::string::npos) {
            throws("This video has no height.");
            return 1;
        }
        p += _k.length();
        p2 = result_s.find("\n", p);
        sscanf(result_s.substr(p, p2 - p).c_str(), "%d", &height);

        _k = "\nr_frame_rate=";
        p = result_s.find(_k);
        if (p == std::string::npos) {
            throws("This video has no frame rate.");
            return 1;
        }
        p += _k.length();
        p2 = result_s.find("/", p);
        sscanf(result_s.substr(p, p2 - p).c_str(), "%lf", &rate_l);
        p = p2 + 1;
        p2 = result_s.find("\n", p);
        sscanf(result_s.substr(p, p2 - p).c_str(), "%lf", &rate_r);

        _k = "\nduration=";
        p = result_s.find(_k);
        if (p != std::string::npos) {
            p += _k.length();
            p2 = result_s.find("\n", p);
            sscanf(result_s.substr(p, p2 - p).c_str(), "%lf", &duration);
        }
    }

    double rate = rate_l / rate_r;
    int mo = 0.5 + rate / fps;
    if (!mo) {
        mo = 1;
    }
    const LL clk = mo * rate_r / rate_l * CLOCKS_PER_SEC;

    // x+=x&1;
    y += y & 1;
    const int xy = x * y;
    printf("[%d:%d %.2lfHz] -> [%d:%d %.2lfHz] %.3lfs\n", width, height, rate, x, y, rate / mo, duration);
    // [1444:1080 29.97Hz] -> [76:54 9.99Hz] 232.065s

    const int print_size = (x + 1) * (y >> 1);
    char buffer[print_size];

    char map[MAXCOL][MAXCOL];

    if (font.size()) {
        f = fopen(font.c_str(), "rb");
        for (auto i = 0; i < MAXCOL; i++) {
            for (auto j = 0; j < MAXCOL; j++) {
                g();
                map[i][j] = g();
            }
            g();
        }
        fclose(f);
    } else {
        for (auto i = 0; i < MAXCOL; i++) {
            for (auto j = 0; j < MAXCOL; j++) {
                map[i][j] = default_map[i][j << 1];
            }
        }
    }

    // read video
    cmd = (std::string) "ffmpeg -v quiet -i \"" + video + "\" -vf scale=" + std::to_string(x) + ":" + std::to_string(y) + " -c:v rawvideo -pix_fmt gray -f rawvideo -";
    // printf("%s\n", cmd.c_str());

    // build pipe
    FILE *pipe = rb_popen(cmd);
    if (!pipe) {
        throws("Failed to build pipe.");
        return 1;
    }

    clock_t t0, t1;
    B *f = (B *)malloc(xy);

    printf("BEGINNING...");
    fflush(stdout);

    if (DEBUG) second_sleep(1);

    printf("\x1b[256F\x1b[0J");
    if (audio.size())
        ffplaya(audio);
    else if (play_audio)
        ffplaya(video);
    t0 = clock();
    for (auto i = 0;; i++) {
        int max_pixel = -1, min_pixel = 256;

        int z = fread(f, 1, xy, pipe);
        if (xy ^ z) {
            if (i == 0) {
                throws("The first frame is empty.");
                return 1;
            }
            break;
        }
        if (i % mo) {
            continue;
        }

        if (contrast_enhancement) {
            for (auto j = 0; j < xy; j++) {
                if (f[j] > max_pixel) max_pixel = f[j];
                if (f[j] < min_pixel) min_pixel = f[j];
            }
            if (max_pixel < 0 || min_pixel > 255) {
                throws("Failed to build pipe.");
                return 1;
            }

            if (max_pixel ^ min_pixel) {
                for (auto j = 0; j < xy; j++) {
                    f[j] = (f[j] - min_pixel) * 0xff / (max_pixel - min_pixel);
                }
            } else {
                memset(f, max_pixel & 128 ? 0xff : 0x00, xy);
            }
        }

        for (auto j = 0; j < (y >> 1); j++) {
            for (auto k = 0; k < x; k++) {
                buffer[j * (x + 1) + k] = map[f[(j << 1) * x + k]][f[(j << 1 | 1) * x + k]];
            }
            buffer[j * (x + 1) + x] = 10;
        }

        printf("\x1b[256F");
        fwrite(buffer, 1, print_size, stdout);
        fflush(stdout);

        t1 = clock();
        while (t1 - t0 < clk) {
            t1 = clock();
        }
        t0 = t1;
    }

    pipe_pclose(pipe);
    return 0;
}
