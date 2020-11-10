#include "FrameProcessor.h"

FrameProcessor::FrameProcessor(QObject *parent) : QObject(parent) {

}

FrameProcessor::~FrameProcessor() {

}

void FrameProcessor::processFrame(const cv::Mat& frame) {
    queue(frame);
}

QImage FrameProcessor::getImage() {
    return image;
}

void FrameProcessor::timerEvent(QTimerEvent *e) {
    // if (e->timerId() != timer.timerId()) {
    //     return;
    // }

    Q_ASSERT(frame.type() == CV_8UC3);

    int w = frame.cols / 3.0, h = frame.rows / 3.0;

    if (image.size() != QSize{w,h}) {
        image = QImage(w, h, QImage::Format_RGB888);
    }

    cv::Mat mat(h, w, CV_8UC3, image.bits(), image.bytesPerLine());
    cv::resize(frame, mat, mat.size(), 0, 0, cv::INTER_AREA);
    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);

    emit imageReady(image);

    frame.release();
    timer.stop();
}

void FrameProcessor::queue(const cv::Mat& newFrame) {
    frame = newFrame;

    if (!timer.isActive()) {
        timer.start(0, this);
    }
}
