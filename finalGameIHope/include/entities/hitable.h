#ifndef HITABLE_H
#define HITABLE_H

#include <QGraphicsPixmapItem>
#include "entitytype.h"

class Hitable : public QGraphicsPixmapItem {
public:

    virtual ~Hitable() {}
    virtual EntityType getEntityType() const = 0;
    virtual void takeDamage(int damage) = 0;

};

#endif // HITABLE_H
