
#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>

#include "MainWindow.h"

MainWindow::MainWindow(VideoSource *capture, FrameProcessor *processor, QWidget *parent) : capture(capture), QMainWindow(parent) {
    frameView = new FrameView(this);
    connect(processor, &FrameProcessor::imageReady, frameView, &FrameView::setImage);

    connect(this, &MainWindow::openVideo, capture, static_cast<void (VideoSource::*)(QString)>(&VideoSource::start));

    // Add file menu to menu bar
    QMenu *fileMenu = menuBar()->addMenu("&File");

    // Add open action
    const auto openIcon = QIcon(":/resources/open.png");

    QAction *openAction = new QAction(openIcon, "&Open", this);
    fileMenu->addAction(openAction);

    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    // Add quit action
    QAction *quitAction = new QAction("&Quit", this);
    fileMenu->addAction(quitAction);

    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
}

void MainWindow::open() {
    QString filepath = QFileDialog::getOpenFileName(this, "Open Video File", QDir::currentPath(), "Video Files (*.mp4 *.avi)");

    if (!filepath.isNull()) {
        emit openVideo(filepath);
    }
}
