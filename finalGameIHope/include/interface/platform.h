#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsRectItem>

class Platform : public QGraphicsRectItem {
public:
    Platform(qreal x_, qreal y_, qreal width_, qreal height_, const QString& imagePath);

private:
    QPixmap m_image;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // PLATFORM_H
