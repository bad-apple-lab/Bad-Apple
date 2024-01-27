#pragma once

#include <chrono>

#include "winux.hpp"
#include "util.hpp"
#include "font.hpp"

#define LL long long
#define B unsigned char

inline void playa(std::string audio) {
    std::string cmd = "ffplay -v quiet -nodisp -autoexit -hide_banner \"" + audio + "\"";
    system(background_process(cmd).c_str());
}

class Player {
private:
    std::string audio;
    int play_audio = 0;

public:
    Player(
        std::string video,
        std::string _audio,
        int _play_audio,
        int perload = 0) {
        if (perload) {
            return;
        }
        if (_audio.length()) {
            play_audio = 1;
            if (not_exist(_audio)) {
                audio = video;
            } else {
                audio = _audio;
            }
        } else if (_play_audio) {
            play_audio = 1;
            audio = video;
        }
    }

    inline void play() {
        if (play_audio) {
            playa(audio);
        }
    }
};

inline void player_playa(
    std::string video,
    std::string audio,
    int play_audio,
    int perload = 0) {
    Player *player = new Player(video, audio, play_audio, perload);
    player->play();
}

class Timer {
private:
    std::chrono::steady_clock::time_point t0;

public:
    LL clk;
    Timer(LL c) : clk(c) {}
    inline void bg() {
        t0 = std::chrono::steady_clock::now();
    }
    inline int wait() {
        auto t1 = std::chrono::steady_clock::now();
        while ((LL)std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() < clk) {
            t1 = std::chrono::steady_clock::now();
        }
        t0 = t1;
        return 0;
    }
    inline void slp(int s) {
        second_sleep(s);
    }
};

class VideoProperties {
public:
    int width, height, nb_frames = 1;
    double rate, duration = 0.0;
};

class Decoder {
public:
    std::string video;
    int x, y, xy;

    Decoder(std::string _video) { video = _video; }
    virtual inline VideoProperties *analysis() { return nullptr; }
    virtual inline int ready_to_read(int _x, int _y) {
        x = _x;
        y = _y;
        xy = x * y;
        return 0;
    }
    virtual inline int read_a_frame(B *f) { return 1; }
    virtual inline void cls() {}
};

class Encoder {
public:
    int x, y, mo = 1, print_size;
    LL clk;
    char *buffer;
    virtual inline int read_a_frame() { return 1; }
    virtual inline void refresh_buffer() {}
    virtual inline void cls() {}
};

class Outer {
public:
    virtual inline void print_a_frame(char *, int) {}
    virtual inline void close() {}
};
