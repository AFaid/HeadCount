#include "VideoSource.h"

VideoSource::VideoSource(QObject *parent) : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VideoSource::captureFrame);
}

VideoSource::~VideoSource() {

}

void VideoSource::start(const QString filepath) {
    capture.reset(new cv::VideoCapture(filepath.toStdString()));

    if (capture->isOpened()) {
        const int delay = 1000 / capture->get(cv::CAP_PROP_FPS);
        timer->start(delay);
    }
}

void VideoSource::start(const int index, const int fps) {
    capture.reset(new cv::VideoCapture(index));

    if (capture->isOpened()) {
        int delay = 0;

        if (fps > 0) {
            delay = 1000 / fps;
        }

        timer->start(delay);
    }
}

void VideoSource::stop() {
    timer->stop();
}

void VideoSource::captureFrame() {
    if (capture->read(frame)) {
        emit frameReady(frame);
    } else {
        stop();
    }
}
