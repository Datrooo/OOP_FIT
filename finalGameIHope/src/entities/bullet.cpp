#include "include/entities/bullet.h"
#include <QBrush>
#include <QTimer>
#include <QGraphicsScene>
#include <QTransform>
#include "include/entities/hitable.h"




Bullet::Bullet(qreal x_, qreal y_, qreal width_, qreal height_, int xSpeed_, int ySpeed_, int damage,
               Direction direction, QGraphicsItem* shooter_, QPixmap image, QObject* parent)
    : QObject(parent), shooter(shooter_) {


    dmg = damage;
    setPos(x_, y_);

    ySpeed = ySpeed_;

    if (direction == Direction::LEFT){
        xSpeed = -xSpeed_;
        QTransform transform;
        transform.scale(-1.0, 1);
        transform.translate(-image.scaled(width_, height_).width(), 0);
        setPixmap(image.scaled(width_, height_).transformed(transform));
    } else if (direction == Direction::RIGHT){
        xSpeed = xSpeed_;
        setPixmap(image.scaled(width_, height_));
    } else{
        xSpeed = xSpeed_;
        setPixmap(image.scaled(width_, height_));
    }

    isUp = true;

}

Bullet::~Bullet(){
    // qDebug() << "bullet deleted";
}

void Bullet::checkCollisions() {
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (QGraphicsItem* item : collidingItems) {
        Hitable* hitableItem = dynamic_cast<Hitable*>(item);
        if (hitableItem && hitableItem != getShooter()) {
            if (getOwnerType() != hitableItem->getEntityType()){
                hitableItem->takeDamage(dmg);
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
    }
}

void Bullet::advance(int phase) {
    if (!phase){
        if (scene()) {
            QRectF sceneRect = scene()->sceneRect();
            if (!sceneRect.contains(x(), y())) {
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
        checkCollisions();
    }
    else{
        setPos(x() + xSpeed, y() + ySpeed);
    }
}


void Bullet::setPower(int power) {
    if (xSpeed >= 0){
        xSpeed += power / 10;
    }else{
        xSpeed -= power / 10;
    }
    if (ySpeed != 0){
        ySpeed += power / 10;
    }
    dmg += power / 10;

    setScale(1.0 + (power / 100.0));
}

EntityType Bullet::getOwnerType() const {
    return dynamic_cast<Hitable *>(shooter)->getEntityType();
}

QGraphicsItem * Bullet::getShooter() const {
    return shooter;
}
