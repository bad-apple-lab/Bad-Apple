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

inline void set_video(std::string _video, int _x, int _y) {
    using namespace decode_opencv;
    video = _video;
    x = _x;
    y = _y;
    xy = x * y;
}

inline VideoProperties *analysis_video() {
    using namespace decode_opencv;

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
    // capture.set(cv::CAP_PROP_FRAME_WIDTH, x);
    // capture.set(cv::CAP_PROP_FRAME_HEIGHT, y);
    return 0;
}

inline int read_a_frame() {
    using namespace decode_opencv;
    capture >> frame;
    return frame.empty();
}

inline void decode(char *buffer, Font *map, int contrast_enhancement) {
    using namespace decode_opencv;

    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    cv::resize(frame, frame, cv::Size(x, y), 0, 0, cv::INTER_CUBIC);

    int max_pixel = -1, min_pixel = 256;
    if (contrast_enhancement) {
        for (auto j = 0; j < frame.rows; j++) {
            for (auto k = 0; k < frame.cols; k++) {
                const B c = frame.at<uchar>(j, k);
                if (c > max_pixel) max_pixel = c;
                if (c < min_pixel) min_pixel = c;
            }
        }

        if (max_pixel ^ min_pixel) {
            for (auto j = 0; j < frame.rows; j++) {
                for (auto k = 0; k < frame.cols; k++) {
                    frame.at<uchar>(j, k) = (frame.at<uchar>(j, k) - min_pixel) * 0xff / (max_pixel - min_pixel);
                }
            }
        } else {
            const B c = max_pixel & 128 ? 0xff : 0x00;
            for (auto j = 0; j < frame.rows; j++) {
                for (auto k = 0; k < frame.cols; k++) {
                    frame.at<uchar>(j, k) = c;
                }
            }
        }
    }

    int buffer_tail = 0;
    for (auto j = 0; j < (frame.rows >> 1); j++) {
        for (auto k = 0; k < frame.cols; k++) {
            buffer[buffer_tail++] = map->get(frame.at<uchar>(j << 1, k), frame.at<uchar>(j << 1 | 1, k));
        }
        buffer[buffer_tail++] = 10;
    }
    buffer[buffer_tail++] = 10;
}

inline void cls() {
    // using namespace decode_opencv;
    return;
}