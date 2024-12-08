#include "include/interface/volumeslider.h"

VolumeSlider::VolumeSlider(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent)
    : QGraphicsRectItem(x, y, width, height, parent) {
    setBrush(Qt::gray);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}
void VolumeSlider::setVolumeLevel(int level) {
    volumeLevel = level;
    updateHandlePosition();
}


void VolumeSlider::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    updateVolume(event->pos().x());
    QGraphicsRectItem::mousePressEvent(event);
}

void VolumeSlider::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    updateVolume(event->pos().x());
    QGraphicsRectItem::mouseMoveEvent(event);
}


void VolumeSlider::updateHandlePosition() {
    if (!handle) {
        handle = new QGraphicsRectItem(this);
        handle->setBrush(Qt::blue);
        handle->setRect(-5, -5, 10, 20);
    }
    qreal handleX = rect().left() + volumeLevel * rect().width() / 100;
    handle->setPos(handleX, rect().top());
}

void VolumeSlider::updateVolume(qreal xPos) {
    qreal normalized = qBound(0.0, xPos - rect().left(), rect().width());
    volumeLevel = static_cast<int>((normalized / rect().width()) * 100);
    updateHandlePosition();
    emit volumeChanged(volumeLevel);
}
