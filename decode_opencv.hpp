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

inline void set_video(std::string video, int x, int y) {
    decode_opencv::video = video;
    decode_opencv::x = x;
    decode_opencv::y = y;
    decode_opencv::xy = x * y;
}

inline VideoProperties *analysis_video() {
    cv::VideoCapture &cap = decode_opencv::capture;
    cap.open(decode_opencv::video);
    if (!cap.isOpened()) {
        throws("Failed to read video.");
        return nullptr;
    }

    VideoProperties *vp = new VideoProperties();

    vp->width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    vp->height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    vp->nb_frames = cap.get(cv::CAP_PROP_FRAME_COUNT);
    vp->rate = cap.get(cv::CAP_PROP_FPS);
    vp->duration = vp->nb_frames / vp->rate;

    return vp;
}

inline int ready_to_read() {
    // decode_opencv::capture.set(cv::CAP_PROP_FRAME_WIDTH, decode_opencv::x);
    // decode_opencv::capture.set(cv::CAP_PROP_FRAME_HEIGHT, decode_opencv::y);
    return 0;
}

inline int read_a_frame() {
    cv::Mat &frame = decode_opencv::frame;
    decode_opencv::capture >> frame;
    return frame.empty();
}

inline void decode(char *buffer, Font *map, int contrast_enhancement) {
    const int &x = decode_opencv::x;
    const int &y = decode_opencv::y;
    const int &xy = decode_opencv::xy;
    cv::Mat &frame = decode_opencv::frame;

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
    return;
}