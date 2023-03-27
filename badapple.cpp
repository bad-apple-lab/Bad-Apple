#pragma once

// #define DEBUG
// #define DECODE_FFMPEG
// #define DECODE_OPENCV

#include "cmdline/cmdline.h"
#include "badapple.hpp"

int main(int argc, char** argv) {
    std::string version = "v2.1.0";
    std::string footer = "\n  (BadApple-";

#ifdef DECODE_FFMPEG
    footer += "FFmpeg";
#else
#ifdef DECODE_OPENCV
    footer += "OpenCV";
#endif
#endif

    footer += "-" + short_os_name() + "-" + short_isa_name() + "-" + version + ")";

#ifdef DEBUG
    footer += " [debug]";
#endif

    cmdline::parser a;
    a.set_program_name("badapple");
    a.footer(footer.c_str());
    a.add<std::string>("input", 'i', "video file", false, "./badapple.mp4");
    a.add<std::string>("output", 'o', "[preload] output file", false, "");
    a.add<std::string>("audio", 'a', "audio file", false, "");
    a.add<std::string>("font", 'f', "font data file", false, "");
    a.add<std::string>("scale", 's', "width:height", false, "72:54");
    a.add<double>("rate", 'r', "frame rate", false, 1024.0);
    a.add("not_clear", '\0', "don't clear screen (using ANSI) before print a frame");
    a.add("contrast_enhancement", '\0', "contrast Enhancement");
    a.add("preload", '\0', "[preload]");
    a.add("play_audio", '\0', "play audio with ffplay");
    a.parse_check(argc, argv);

    int x, y;
    sscanf(a.get<std::string>("scale").c_str(), "%d:%d", &x, &y);
    play(a.get<std::string>("input"), a.get<std::string>("output"), a.get<std::string>("audio"), a.get<std::string>("font"), x, y, a.get<double>("rate"), a.exist("not_clear"), a.exist("contrast_enhancement"), a.exist("preload"), a.exist("play_audio"));
}
