#pragma once

#include "encode_re.hpp"
#include "encode_rt.hpp"
#include "preloader.hpp"

inline int play(
    std::string video,
    std::string output,  // default stdout
    std::string font,    // default "font/consola_0_0ff.h"
    std::string audio,   // default use video
    int x,               // width
    int y,               // height
    int fps,             // frame rate
    int not_clear = 0,
    int contrast = 0,
    int preload = 0,
    int play_audio = 0,
    int debug = 0) {
    FILE *fp;
    fp = fopen(video.c_str(), "rb");
    if (!fp) {
        printf("Open video file failed.\n");
        fflush(stdout);
        getchar();
        return 1;
    }
    fclose(fp);

    if (output.length()) {
        preload = 1;
    } else if (preload) {
        output = video + ".badapple";
    }

    if (audio.length()) {
        play_audio = 1;
        fp = fopen(audio.c_str(), "rb");
        if (!fp) {
            audio = video;
        } else {
            fclose(fp);
        }
    } else if (play_audio) {
        audio = video;
    }

    Encoder *encoder;
    if (endswith(video, ".badapple")) {
        encoder = new Encoder_Re(video, debug);
    } else {
        encoder = new Encoder_RT(video, font, x, y, fps, contrast = 0, debug = 0);
    }

    Timer *timer = new Timer(encoder->clk);

    if (preload) {
        fp = fopen(output.c_str(), "w");
        if (!fp) {
            printf("Open output file failed.\n");
            fflush(stdout);
            getchar();
            return 1;
        }
        Preloader *preloader = new Preloader(encoder->x, encoder->y, encoder->clk, fp);
    } else {
        printf("BEGINNING...\n");
        fflush(stdout);
        timer->slp(debug ? 3 : 1);
        if (play_audio) {
            playa(audio);
        }
        printf(not_clear ? "\n" : "\x1b[256F\x1b[0J");
        fflush(stdout);
        timer->bg();
    }

    for (auto i = 0;; i++) {
        if (encoder->read_a_frame()) {
            if (!i) {
                throws("The first frame is empty.");
                return 1;
            }
            break;
        }
        if (i % encoder->mo) continue;

        encoder->refresh_buffer();

        // printf("prt_sz %d \n", encoder->print_size);
        // for (int _ = 0; _ <= encoder->print_size; _++) {
        //     if (encoder->buffer[_] == '\n')
        //         continue;
        //     if (encoder->buffer[_] <= 126 && encoder->buffer[_] >= 32)
        //         continue;
        //     printf("[%d:%d]", _, encoder->buffer[_]);
        //     fflush(stdout);
        //     throws("WTF");
        //     exit(0);
        // }
        // fflush(stdout);
        // throws("WTF");
        // exit(0);

        if (preload) {
            fwrite(encoder->buffer, 1, encoder->print_size + 1, fp);
        } else {
            printf(not_clear ? "\n" : "\x1b[256F");
            fwrite(encoder->buffer, 1, encoder->print_size, stdout);
            fflush(stdout);
            timer->wait();
        }
    }

    encoder->cls();
    if (preload) {
        fclose(fp);
    }
    return 0;
}
