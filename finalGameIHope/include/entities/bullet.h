#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsRectItem>
#include "direction.h"
#include <QGraphicsPixmapItem>
#include "entitytype.h"


class Bullet: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(qreal x_, qreal y_, qreal width_, qreal height_, int xSpeed_, int ySpeed_, int damage,
           Direction direction, QGraphicsItem * shooter, QPixmap image, QObject* parent = nullptr);
    ~Bullet();
    QGraphicsItem * getShooter() const;
    void setPower(int power);


private:
    QGraphicsItem * shooter;
    void checkCollisions();
    bool isUp;
    int xSpeed;
    int ySpeed;

    int dmg;

    EntityType getOwnerType() const;

    void advance(int phase) override;
};


#endif // BULLET_H
