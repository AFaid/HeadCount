#include "FrameView.h"

#include <QGridLayout>
#include <QPainter>
#include <QPixmap>

FrameView::FrameView(QWidget *parent) : QWidget(parent) {
    auto grid = new QGridLayout(this);

    label = new QLabel(this);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setScaledContents(true);

    grid->addWidget(label, 0, 0);
}

FrameView::~FrameView() {

}

void FrameView::setImage(const QImage& newImage) {
    image = newImage.copy();

    const auto imageSize = image.size();

    if (imageSize != size()) {
        setFixedSize(imageSize);
    }

    update();
}

void FrameView::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e)

    if (image.isNull()) {
        return;
    }

    label->setPixmap(QPixmap::fromImage(image));

    // setAttribute(Qt::WA_OpaquePaintEvent);

    // QPainter painter(this);
    // painter.drawImage(0, 0, image);
}
