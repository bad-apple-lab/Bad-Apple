#pragma once

#ifdef DECODE_FFMPEG
#include "decode_ffmpeg.hpp"
#else
#ifdef DECODE_OPENCV
#include "decode_opencv.hpp"
#endif
#endif

inline void ffplaya(std::string audio) {
    std::string cmd = "ffplay -v quiet -nodisp -autoexit -hide_banner \"" + audio + "\"";
    system(background_process(cmd).c_str());
}

inline int play(
    std::string video,
    std::string output,  // default stdout
    std::string audio,   // default use video
    std::string font,    // default use map in "consola_0_0ff.h"
    int x,               // width
    int y,               // height
    int fps,             // rate
    int contrast_enhancement = 0,
    int play_audio = 0) {
    Font *map = new Font(font);
    // x += x & 1;
    y += y & 1;
    set_video(video, x, y);

    VideoProperties *vp = analysis_video();
    if (!vp) {
        throws("Failed to analysis video.");
        return 1;
    }

    int mo = 0.5 + vp->rate / fps;
    if (!mo) {
        mo = 1;
    }
    const LL clk = mo / vp->rate * CLOCKS_PER_SEC;

    printf("[%d:%d %.2lfHz] -> [%d:%d %.2lfHz] %.3lfs\n", vp->width, vp->height, vp->rate, x, y, vp->rate / mo, vp->duration);
    // [1444:1080 29.97Hz] -> [76:54 9.99Hz] 232.065s

    const int print_size = (x + 1) * (y >> 1);
    char buffer[print_size + 2];

    if (ready_to_read()) {
        throws("Failed to read video.");
        return 1;
    }

    int preload = output.size();
    FILE *fp;
    if (preload) {
        fp = fopen(output.c_str(), "wb");
    }

    clock_t t0, t1;

    if (!preload) {
#ifdef DEBUG
        printf("BEGINNING... [debug]\n");
        fflush(stdout);
        second_sleep(3);
#else
        printf("BEGINNING...\n");
        fflush(stdout);
        second_sleep(1);
#endif
        if (audio.size())
            ffplaya(audio);
        else if (play_audio)
            ffplaya(video);
        printf("\x1b[256F\x1b[0J");
        t0 = clock();
    }

    for (auto i = 0;; i++) {
        if (read_a_frame()) {
            if (!i) {
                throws("The first frame is empty.");
                return 1;
            }
            break;
        }
        if (i % mo) continue;

        decode(buffer, map, contrast_enhancement);
#ifdef DEBUG
        for (int _ = 0; _ <= print_size; _++) {
            if (buffer[_] == 10 || (buffer[_] <= 126 && buffer[_] >= 32)) continue;
            printf("[%d:%d]", _, buffer[_]);
            throws("WTF");
            exit(0);
        }
#endif

        if (preload) {
            fwrite(buffer, 1, print_size + 1, fp);
        } else {
            printf("\x1b[256F");
            fwrite(buffer, 1, print_size, stdout);
            fflush(stdout);

            t1 = clock();
            while (t1 - t0 < clk) {
                t1 = clock();
            }
            t0 = t1;
        }
    }

    cls();
    return 0;
}
