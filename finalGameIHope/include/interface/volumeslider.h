#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class VolumeSlider : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    VolumeSlider(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr);
    void setVolumeLevel(int level);


signals:
    void volumeChanged(int newVolume);

private:
    int volumeLevel = 50;
    QGraphicsRectItem* handle = nullptr;

    void updateHandlePosition();
    void updateVolume(qreal xPos);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};
