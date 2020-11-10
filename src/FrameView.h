#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QLabel>
#include <QWidget>

class FrameView : public QWidget {
    Q_OBJECT

    public:
        FrameView(QWidget *parent = 0);

        ~FrameView();

        Q_SLOT void setImage(const QImage& image);

    protected:
        void paintEvent(QPaintEvent *e);

    private:
        // Q_PROPERTY(QImage image READ getImage WRITE setImage USER true)

        QImage image;

        QLabel *label;
};

#endif // FRAMEVIEW_H
