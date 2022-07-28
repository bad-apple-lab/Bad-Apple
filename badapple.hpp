#pragma once

#include "decode_replay.hpp"

#ifdef DECODE_FFMPEG
#include "decode_ffmpeg.hpp"
#else
#ifdef DECODE_OPENCV
#include "decode_opencv.hpp"
#endif
#endif

inline int play(
    std::string video,
    std::string output,  // default stdout
    std::string audio,   // default use video
    std::string font,    // default use map in "consola_0_0ff.h"
    int x,               // width
    int y,               // height
    int fps,             // frame rate
    int not_clear = 0,
    int contrast_enhancement = 0,
    int preload = 0,
    int play_audio = 0) {
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

    if(endswith(video,".badapple")){
        return replay(video,audio,not_clear,play_audio);
    }

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
    // char buffer[print_size + 2];
    char *buffer = (char *)malloc(print_size + 2);

    if (ready_to_read()) {
        throws("Failed to read video.");
        return 1;
    }

    clock_t t0, t1;

    if (preload) {
        fp = fopen(output.c_str(), "w");
        if (!fp) {
            printf("Open output file failed.\n");
            fflush(stdout);
            getchar();
            return 1;
        }
        compress(x,y,clk,fp);
    } else {
#ifdef DEBUG
        printf("BEGINNING... [debug]\n");
        fflush(stdout);
        second_sleep(3);
#else
        printf("BEGINNING...\n");
        fflush(stdout);
        second_sleep(1);
#endif
        if (audio.length())
            playa(audio);
        else if (play_audio)
            playa(video);
        printf(not_clear?"\n":"\x1b[256F\x1b[0J");
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
            printf(not_clear?"\n":"\x1b[256F");
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
    if (preload) {
        fclose(fp);
    }
    return 0;
}
