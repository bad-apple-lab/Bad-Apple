#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "base.hpp"

class Decoder_OpenCV : public Decoder {
private:
    cv::VideoCapture capture;
    cv::Mat frame;

public:
    Decoder_OpenCV(std::string _video) : Decoder(_video){};

    inline VideoProperties *analysis() {
        capture.open(video);
        if (!capture.isOpened()) {
            throws("Failed to read video.");
            return nullptr;
        }

        VideoProperties *vp = new VideoProperties();

        vp->width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
        vp->height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
        vp->nb_frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
        vp->rate = capture.get(cv::CAP_PROP_FPS);
        vp->duration = vp->nb_frames / vp->rate;

        return vp;
    }

    inline int read_a_frame(B *f) {
        capture >> frame;
        if (frame.empty()) {
            return 1;
        }
        cv::resize(frame, frame, cv::Size(x, y), 0, 0, cv::INTER_CUBIC);
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        // (x, y) (frame.cols, frame.rows) (72, 54)
        memcpy(f, frame.data, xy);
        return 0;
    }
};
