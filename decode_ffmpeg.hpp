#pragma once

#include "base.hpp"

namespace decode_ffmpeg {

const int BUFFER_SIZE = 1 << 8;
const int STDOUT_SIZE = 1 << 20;

inline int exec_r(const char *cmd, char *result) {
    FILE *p = r_popen(cmd);

    if (!p) return 1;
    int code = 0;

    int t = 0;
    while (!feof(p)) {
        fread(result + t, 1, BUFFER_SIZE, p);
        t += BUFFER_SIZE;
        if (t >= STDOUT_SIZE) {
            code = 2;
            break;
        }
    }
    pipe_pclose(p);

    return code;
}

std::string video;
FILE *fp;
int x, y, xy;
B *f;
}  // namespace decode_ffmpeg

inline void set_video(std::string _video, int _x, int _y) {
    using namespace decode_ffmpeg;
    video = _video;
    x = _x;
    y = _y;
    xy = x * y;
    f = (B *)malloc(xy);
}

inline VideoProperties *analysis_video() {
    using namespace decode_ffmpeg;

    std::string cmd = (std::string) "ffprobe -v quiet -show_streams -select_streams v \"" + video + "\"";
    // printf("%s\n", cmd.c_str());

    VideoProperties *vp = new VideoProperties();

    double rate_l, rate_r;  // fps = rate_l / rate_r;
    char result_c[STDOUT_SIZE];
    if (exec_r(cmd.c_str(), result_c)) {
        throws("Failed to analysis video.");
        return nullptr;
    }
    std::string result_s(result_c), _k;
    std::size_t p, p2;

    _k = "\nwidth=";
    p = result_s.find(_k);
    if (p == std::string::npos) {
        throws("This video has no width.");
        return nullptr;
    }
    p += _k.length();
    p2 = result_s.find("\n", p);
    sscanf(result_s.substr(p, p2 - p).c_str(), "%d", &vp->width);

    _k = "\nheight=";
    p = result_s.find(_k);
    if (p == std::string::npos) {
        throws("This video has no height.");
        return nullptr;
    }
    p += _k.length();
    p2 = result_s.find("\n", p);
    sscanf(result_s.substr(p, p2 - p).c_str(), "%d", &vp->height);

    _k = "\nnb_frames=";
    p = result_s.find(_k);
    if (p == std::string::npos) {
        p += _k.length();
        p2 = result_s.find("\n", p);
        sscanf(result_s.substr(p, p2 - p).c_str(), "%d", &vp->nb_frames);
    }

    double _l, _r;
    _k = "\nr_frame_rate=";
    p = result_s.find(_k);
    if (p == std::string::npos) {
        throws("This video has no frame rate.");
        return nullptr;
    }
    p += _k.length();
    p2 = result_s.find("/", p);
    sscanf(result_s.substr(p, p2 - p).c_str(), "%lf", &_l);
    p = p2 + 1;
    p2 = result_s.find("\n", p);
    sscanf(result_s.substr(p, p2 - p).c_str(), "%lf", &_r);
    if (_r < 1) {
        throws("This video has no frame rate.");
        return nullptr;
    }
    vp->rate = _l / _r;

    _k = "\nduration=";
    p = result_s.find(_k);
    if (p != std::string::npos) {
        p += _k.length();
        p2 = result_s.find("\n", p);
        sscanf(result_s.substr(p, p2 - p).c_str(), "%lf", &vp->duration);
    }

    return vp;
}

inline int ready_to_read() {
    using namespace decode_ffmpeg;

    std::string cmd = (std::string) "ffmpeg -v quiet -i \"" + video + "\" -vf scale=" + std::to_string(x) + ":" + std::to_string(y) + " -c:v rawvideo -pix_fmt gray -f rawvideo -";
    // printf("%s\n", cmd.c_str());

    fp = rb_popen(cmd);
    if (!fp) {
        throws("Failed to build pipe.");
        return 1;
    }
    return 0;
}

inline int read_a_frame() {
    using namespace decode_ffmpeg;
    return xy ^ fread(f, 1, xy, fp);
}

inline void decode(char *buffer, Font *map, int contrast_enhancement) {
    using namespace decode_ffmpeg;

    int max_pixel = -1, min_pixel = 256;
    if (contrast_enhancement) {
        for (auto j = 0; j < xy; j++) {
            if (f[j] > max_pixel) max_pixel = f[j];
            if (f[j] < min_pixel) min_pixel = f[j];
        }

        if (max_pixel ^ min_pixel) {
            for (auto j = 0; j < xy; j++) {
                f[j] = (f[j] - min_pixel) * 0xff / (max_pixel - min_pixel);
            }
        } else {
            memset(f, max_pixel & 128 ? 0xff : 0x00, xy);
        }
    }

    int buffer_tail = 0;
    for (auto j = 0; j < (y >> 1); j++) {
        for (auto k = 0; k < x; k++) {
            buffer[buffer_tail++] = map->get(f[(j << 1) * x + k], f[(j << 1 | 1) * x + k]);
        }
        buffer[buffer_tail++] = 10;
    }
    buffer[buffer_tail++] = 10;
}

inline void cls() {
    using namespace decode_ffmpeg;
    pipe_pclose(fp);
}