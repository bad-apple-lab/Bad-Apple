#pragma once

// #define DECODE_FFMPEG
// #define DECODE_OPENCV

#include "cmdline/cmdline.h"
#include "badapple.hpp"

int main(int argc, char** argv) {
    std::string version = "v2.1.4";
    std::string footer = "\n  (BadApple-";

#ifdef DECODE_FFMPEG
    footer += "FFmpeg";
#else
#ifdef DECODE_OPENCV
    footer += "OpenCV";
#endif
#endif

    footer += "-" + short_os_name();
    footer += "-" + short_isa_name();
    footer += "-" + version + ")";

    cmdline::parser a;
    a.set_program_name("badapple");
    a.footer(footer.c_str());
    a.add<std::string>("input", 'i', "video file", false, "./badapple.mp4");
    a.add<std::string>("output", 'o', "[preload] output file", false, "");
    a.add<std::string>("font", 'f', "font data file", false, "");
    a.add<std::string>("audio", 'a', "audio file", false, "");
    a.add<std::string>("player", 'p', "player [ffmpeg mpv mpg123 cmus]", false, "");
    a.add<std::string>("scale", 's', "width:height (0 means auto)", false, "0:0");
    a.add<double>("rate", 'r', "frame rate", false, 1024.0);
    a.add("not_clear", '\0', "not clear screen (with ANSI) before each frame");
    a.add("contrast", '\0', "contrast enhancement");
    a.add("preload", '\0', "preload video (not play)");
    a.add("debug", '\0', "[debug]");
    a.parse_check(argc, argv);

    play(a.get<std::string>("input"), a.get<std::string>("output"),
         a.get<std::string>("audio"), a.get<std::string>("player"),
         a.get<std::string>("font"), a.get<std::string>("scale"), a.get<double>("rate"),
         a.exist("not_clear"), a.exist("contrast"), a.exist("preload"),
         a.exist("debug"));
}
