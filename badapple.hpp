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

    if (endswith(video, ".badapple")) {
        return replay(video, audio, not_clear, play_audio);
    }

    Font *fnt = new Font(font);

    // x += x & 1;
    y += y & 1;
    const int xy = x * y;

#ifdef DECODE_FFMPEG
    Decoder_FFmpeg *decoder = new Decoder_FFmpeg(video.c_str());
#else
#ifdef DECODE_OPENCV
    Decoder_OpenCV *decoder = new Decoder_OpenCV(video);
#endif
#endif
    VideoProperties *vp = decoder->analysis();
    if (!vp) {
        throws("Failed to analysis video.");
        return 1;
    }

    int mo = 0.5 + vp->rate / fps;
    if (!mo) {
        mo = 1;
    }
    const LL clk = mo * 1000000LL / vp->rate;

    printf("[%d:%d %.2lfHz] -> [%d:%d %.2lfHz] %.3lfs %s\n",
           vp->width, vp->height, vp->rate,
           x, y, vp->rate / mo,
           vp->duration, debug ? "[debug]" : "");
    // [1444:1080 29.97Hz] -> [76:54 9.99Hz] 232.065s [debug]

    const int print_size = (x + 1) * (y >> 1);
    B *frame = (B *)malloc(xy);
    char *buffer = (char *)malloc(print_size + 2);
    Timer *timer = new Timer(clk);

    if (decoder->ready_to_read(x, y)) {
        throws("Failed to read video.");
        return 1;
    }

    if (preload) {
        fp = fopen(output.c_str(), "w");
        if (!fp) {
            printf("Open output file failed.\n");
            fflush(stdout);
            getchar();
            return 1;
        }
        compress(x, y, clk, fp);
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
        if (decoder->read_a_frame(frame)) {
            if (!i) {
                throws("The first frame is empty.");
                return 1;
            }
            break;
        }
        if (i % mo) continue;

        if (contrast) {
            int max_pixel = 0, min_pixel = 255;
            for (auto j = 0; j < xy; j++) {
                if (frame[j] > max_pixel) max_pixel = frame[j];
                if (frame[j] < min_pixel) min_pixel = frame[j];
            }

            if (max_pixel ^ min_pixel) {
                int range = max_pixel - min_pixel;
                for (auto j = 0; j < xy; j++) {
                    frame[j] = (frame[j] - min_pixel) * 0xff / range;
                }
            } else {
                memset(frame, max_pixel & 128 ? 0xff : 0x00, xy);
            }
        }

        int buffer_tail = 0;
        for (auto j = 0; j < (y >> 1); j++) {
            for (auto k = 0; k < x; k++) {
                buffer[buffer_tail++] = fnt->get(frame[(j << 1) * x + k],
                                                 frame[(j << 1 | 1) * x + k]);
            }
            buffer[buffer_tail++] = '\n';
        }
        buffer[buffer_tail++] = '\n';

        // for (int _ = 0; _ <= print_size; _++) {
        //     if (buffer[_] == '\n' || (buffer[_] <= 126 && buffer[_] >= 32))
        //         continue;
        //     printf("[%d:%d]", _, buffer[_]);
        //     fflush(stdout);
        //     throws("WTF");
        //     exit(0);
        // }

        if (preload) {
            fwrite(buffer, 1, print_size + 1, fp);
        } else {
            printf(not_clear ? "\n" : "\x1b[256F");
            fwrite(buffer, 1, print_size, stdout);
            fflush(stdout);
            timer->wait();
        }
    }

    decoder->cls();
    if (preload) {
        fclose(fp);
    }
    return 0;
}
