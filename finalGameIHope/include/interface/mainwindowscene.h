#ifndef MAINWINDOWSCENE_H
#define MAINWINDOWSCENE_H

#include <QGraphicsScene>
#include "button.h"


class MainWindowScene : public QGraphicsScene {
public:
    MainWindowScene();
    ~MainWindowScene();
    QVector<Button *> getButtons();

private:
    QVector<Button*> buttons;
};

#endif // MAINWINDOWSCENE_H
