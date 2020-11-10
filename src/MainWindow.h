
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include "FrameProcessor.h"
#include "FrameView.h"
#include "VideoSource.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(VideoSource *capture, FrameProcessor *frame, QWidget *parent = 0);

        Q_SIGNAL void openVideo(const QString filepath);

        Q_SLOT void open();

    private:
        VideoSource *capture;

        FrameView *frameView;
};

#endif // MAINWINDOW_H
