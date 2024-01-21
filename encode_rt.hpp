#pragma once

#include "base.hpp"

#ifdef DECODE_FFMPEG
#include "decode_ffmpeg.hpp"
#else
#ifdef DECODE_OPENCV
#include "decode_opencv.hpp"
#endif
#endif

class Encoder_RT : public Encoder {
private:
    Font *fnt;
    B *frame;
    int contrast;
    
#ifdef DECODE_FFMPEG
        Decoder_FFmpeg *decoder;
#else
#ifdef DECODE_OPENCV
        Decoder_OpenCV *decoder;
#endif
#endif

public:
    int xy;
    Encoder_RT(
        std::string video,
        std::string font,
        int _x,
        int _y,
        int fps,
        int _contrast = 0,
        int debug = 0) {
        fnt = new Font(font);

        x = _x;
        y = _y + (_y & 1);
        xy = x * y;
        contrast = _contrast;

#ifdef DECODE_FFMPEG
        decoder = new Decoder_FFmpeg(video);
#else
#ifdef DECODE_OPENCV
        decoder = new Decoder_OpenCV(video);
#endif
#endif

        VideoProperties *vp = decoder->analysis();
        if (!vp) {
            throws("Failed to analysis video.");
            return;
        }

        mo = 0.5 + vp->rate / fps;
        if (!mo) {
            mo = 1;
        }
        clk = mo * 1000000LL / vp->rate;

        printf("[%d:%d %.2lfHz] -> [%d:%d %.2lfHz] %.3lfs/%dms %s\n",
               vp->width, vp->height, vp->rate,
               x, y, vp->rate / mo,
               vp->duration, clk / 1000,
               debug ? "[debug]" : "");
        // [1444:1080 29.97Hz] -> [76:54 9.99Hz] 232.065s [debug]

        if (decoder->ready_to_read(x, y)) {
            throws("Failed to read video.");
            return;
        }

        print_size = (x + 1) * (y >> 1);
        frame = (B *)malloc(xy);
        buffer = (char *)malloc(print_size + 2);
    }

    inline int read_a_frame() {
        return decoder->read_a_frame(frame);
    }

    inline void refresh_buffer() {
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
    }

    inline void cls() {
        decoder->cls();
    }
};
