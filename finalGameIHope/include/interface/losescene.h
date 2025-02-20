#ifndef LOSESCENE_H
#define LOSESCENE_H

#include <QGraphicsScene>
#include "button.h"

class LoseScene : public QGraphicsScene{
public:
    LoseScene();
    ~LoseScene();
    QVector<Button *> getButtons();

private:
    QVector<Button *> buttons;
};

#endif // LOSESCENE_H
