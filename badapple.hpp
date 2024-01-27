#pragma once

#include "encode_re.hpp"
#include "encode_rt.hpp"
#include "printer.hpp"

inline int play(
    std::string video,   // default "badapple.mp4"
    std::string output,  // default stdout
    std::string audio,   // default `video`
    std::string player,  // default ffmpeg
    std::string font,    // default "font/consola_0_0ff.h"
    std::string scale,   // width:height
    int fps,             // frame per second
    int not_clear = 0,
    int contrast = 0,
    int preload = 0,
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

    Cmd *clplayer(get_player(video, audio, player, preload));

    Encoder *enc;
    if (endswith(video, ".badapple")) {
        if (preload) {
            throws("Video file is already preloaded.");
            return 1;
        }
        enc = new Encoder_Re(video, clplayer->name, debug);
    } else {
        enc = new Encoder_RT(video, font, scale, fps, contrast, clplayer->name, debug);
    }

    Outer *outer;
    if (preload) {
        outer = new Preloader(output, enc->x, enc->y, enc->clk, debug);
    } else {
        outer = new Printer(enc->clk, not_clear, debug);
    }

    clplayer->start();

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
    outer->cls();
    clplayer->terminate();
    return 0;
}
