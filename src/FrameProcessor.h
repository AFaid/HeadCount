#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <QImage>
#include <QObject>
#include <QBasicTimer>

#include <opencv2/opencv.hpp>

class FrameProcessor : public QObject {
    Q_OBJECT

    Q_PROPERTY(QImage image READ getImage NOTIFY imageReady USER true)

    public:
        FrameProcessor(QObject *parent = 0);

        ~FrameProcessor();

        Q_SLOT void processFrame(const cv::Mat& frame);

        Q_SIGNAL void imageReady(const QImage& image);

        QImage getImage();

    protected:
        void timerEvent(QTimerEvent *e);

    private:
        cv::Mat frame;

        QImage image;

        QBasicTimer timer;

        void queue(const cv::Mat& frame);
};

#endif // FRAMEPROCESSOR_H
