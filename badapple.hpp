#pragma once

#include "encode_re.hpp"
#include "encode_rt.hpp"
#include "printer.hpp"

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
    if (not_exist(video)) {
        throws("Open video file failed.");
        return 1;
    }

    if (output.length()) {
        preload = 1;
    } else if (preload) {
        output = video + ".badapple";
    }

    Encoder *enc;
    if (endswith(video, ".badapple")) {
        if (preload) {
            throws("Video file is already preloaded.");
            return 1;
        }
        enc = new Encoder_Re(video, debug);
    } else {
        enc = new Encoder_RT(video, font, x, y, fps, contrast, debug);
    }

    Outer *outer;
    if (preload) {
        outer = new Preloader(output, enc->x, enc->y, enc->clk, debug);
    } else {
        outer = new Printer(video, audio, enc->clk, not_clear, play_audio, debug);
    }

    for (auto i = 0;; i++) {
        if (enc->read_a_frame()) {
            if (!i) {
                throws("The first frame is empty.");
                return 1;
            }
            break;
        }
        if (i % enc->mo) continue;
        enc->refresh_buffer();
        outer->print_a_frame(enc->buffer, enc->print_size);
    }

    enc->cls();
    outer->close();
    return 0;
}
