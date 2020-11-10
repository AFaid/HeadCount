#include <QObject>
#include <QThread>

#include "FrameView.h"
#include "MainWindow.h"
#include "VideoSource.h"
#include "FrameProcessor.h"

Q_DECLARE_METATYPE(cv::Mat)

int main(int argc, char *argv[]) {
    qRegisterMetaType<cv::Mat>();

    QApplication app(argc, argv);

    VideoSource capture;
    QThread captureThread;

    capture.moveToThread(&captureThread);
    captureThread.start();

    FrameProcessor processor;
    QThread processorThread;

    processor.moveToThread(&processorThread);
    processorThread.start();

    QObject::connect(&capture, &VideoSource::frameReady, &processor, &FrameProcessor::processFrame);
    // QObject::connect(&processor, &VideoConverter::imageReady, &view, &FrameView::setImage);

    MainWindow window(&capture, &processor);
    window.resize(400, 300);
    window.setWindowTitle("Headcount");
    window.show();

    return app.exec();
}
