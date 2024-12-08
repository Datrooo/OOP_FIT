#include "include/interface/platform.h"
#include <QBrush>
#include <QPainter>

Platform::Platform(qreal x_, qreal y_, qreal width_, qreal height_, const QString& imagePath) : m_image(imagePath) {
    setRect(x_, y_, width_, height_);
}


void Platform::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->drawPixmap(rect(), m_image, QRectF(m_image.rect()));
}
