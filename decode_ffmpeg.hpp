#pragma once

#include "base.hpp"

class Decoder_FFmpeg : public Decoder {
private:
    const int STDOUT_SIZE = 1 << 20;
    FILE *fp;

public:
    Decoder_FFmpeg(std::string _video) : Decoder(_video){};

    inline VideoProperties *analysis() {
        std::string cmd = "ffprobe -v quiet -show_streams -select_streams v";
        cmd += " \"" + video + "\"";
        // printf("%s\n", cmd.c_str());

        VideoProperties *vp = new VideoProperties();

        double rate_l, rate_r;  // fps = rate_l / rate_r;
        char result_c[STDOUT_SIZE];
        int t = exec_r(cmd.c_str(), result_c, STDOUT_SIZE);
        if (t <= 0) {
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

    inline int ready_to_read(int _x, int _y) {
        x = _x;
        y = _y;
        xy = x * y;
        std::string cmd = "ffmpeg -v quiet -i \"" + video + "\"";
        cmd += " -vf scale=" + std::to_string(x) + ":" + std::to_string(y);
        cmd += " -c:v rawvideo -pix_fmt gray -f rawvideo -";
        // printf("%s\n", cmd.c_str());

        fp = rb_popen(cmd);
        if (!fp) {
            throws("Failed to build pipe.");
            return 1;
        }
        return 0;
    }

    inline int read_a_frame(B *f) {
        return xy ^ fread(f, 1, xy, fp);
    }

    inline void cls() {
        pipe_pclose(fp);
    }
};
