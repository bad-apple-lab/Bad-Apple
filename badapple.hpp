#pragma once

#include "encode_re.hpp"
#include "encode_rt.hpp"
#include "preloader.hpp"
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

    if (audio.length()) {
        play_audio = not_exist(audio) ? 0 : 1;
    } else if (play_audio) {
        audio = video;
    }

    Encoder *encoder;
    if (endswith(video, ".badapple")) {
        encoder = new Encoder_Re(video, debug);
    } else {
        encoder = new Encoder_RT(video, font, x, y, fps, contrast = 0, debug = 0);
    }

    Outer *outer;
    if (preload) {
        outer = new Preloader(output, encoder->x, encoder->y, encoder->clk);
    } else {
        outer = new Printer(audio, encoder->clk, not_clear, play_audio, debug);
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
        outer->print_a_frame(encoder->buffer, encoder->print_size);
    }

    encoder->cls();
    outer->close();
    return 0;
}
