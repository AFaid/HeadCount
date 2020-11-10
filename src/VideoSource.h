#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include <QScopedPointer>
#include <QTimer>

#include <opencv2/opencv.hpp>

///
class VideoSource : public QObject {
    Q_OBJECT

    public:
        VideoSource(QObject *parent = 0);

        ~VideoSource();

        /// Starts capturing frames from the video file at the given file path.
        /// \param filepath Path to the video file.
        Q_SLOT void start(const QString filepath);

        Q_SLOT void start(const int index, const int fps = 0);

        Q_SLOT void stop();

        Q_SIGNAL void started();

        Q_SIGNAL void stopped();

        Q_SIGNAL void frameReady(const cv::Mat& frame);

    private:
        /// The internal frame buffer used to store the most recently captured frame.
        cv::Mat frame;

        /// The timer used to schedule frame capturing.
        QTimer *timer;

        QScopedPointer<cv::VideoCapture> capture;

        void captureFrame();
};

#endif // VIDEOSOURCE_H
