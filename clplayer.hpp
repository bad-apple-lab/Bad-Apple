#pragma once

#include "clplayer/clplayer.hpp"
#include "util.hpp"

inline Cmd* get_player(
    std::string video,
    std::string audio,
    std::string player,
    int perload = 0) {
    if (perload) {
        return new Nothing();
    }

    if (audio.length()) {
        if (not_exist(audio)) {
            audio = video;
        }
        if (!player.length()) {
            player = "ffmpeg";
        }
    } else if (player.length()) {
        audio = video;
    } else {
        return new Nothing();
    }

    if (player == "auto" || player == "ffmpeg" || player == "ffplay") {
        return new FFplayPlayer(audio);
    }
    if (player == "mpv") {
        return new MpvPlayer(audio);
    }
    if (player == "mpg123" || player == "mpg") {
        return new Mpg123Player(audio);
    }
    if (player == "cmus" || player == "cmus-remote") {
        return new CmusPlayer(audio);
    }
    throws("Bad Player!!: " + player);
}
