#ifndef WINSCENE_H
#define WINSCENE_H

#include <QGraphicsScene>
#include "button.h"

class WinScene : public QGraphicsScene {
public:
    WinScene();
    ~WinScene();
    QVector<Button *> getButtons();
private:
    QVector<Button *> buttons;
};

#endif // WINSCENE_H
