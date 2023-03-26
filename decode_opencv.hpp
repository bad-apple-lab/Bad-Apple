#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "base.hpp"

namespace decode_opencv {

std::string video;
cv::VideoCapture capture;
cv::Mat frame;
int x, y, xy;
}  // namespace decode_opencv

inline VideoProperties *analysis_video(std::string _video, int _x, int _y) {
    using namespace decode_opencv;
    video = _video;
    x = _x;
    y = _y;
    xy = x * y;

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

inline int ready_to_read() {
    // using namespace decode_opencv;
    return 0;
}

inline int read_a_frame(B *f) {
    using namespace decode_opencv;
    capture >> frame;
    if (frame.empty()) {
        return 1;
    }
    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    cv::resize(frame, frame, cv::Size(x, y), 0, 0, cv::INTER_CUBIC);
    // (x, y) (frame.cols, frame.rows) (72, 54)
    memcpy(f, frame.data, xy);
    return 0;
}

inline void cls() {
    // using namespace decode_opencv;
    return;
}
