#include "include/interface/mainwindowscene.h"
#include "include/interface/button.h"

MainWindowScene::MainWindowScene() {
    //qDebug() << "new main window scene";
    setSceneRect(0, 0, 1072, 603);
    QImage backgroundImage(":/images/interface/background/mainwindow.png");
    QPixmap backgroundPixmap = QPixmap::fromImage(backgroundImage);

    QPixmap scaledPixmap = backgroundPixmap.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);

    QBrush brush(scaledPixmap);
    setBackgroundBrush(brush);
    //qDebug() << "back setted";


    qreal buttonWidth = 200;
    qreal buttonHeight = 50;

    qreal centerX = width() / 2 - buttonWidth / 2;
    qreal centerY = height() / 2;

    addButtonToScene("Играть", centerX, centerY - 70, buttonWidth, buttonHeight, this, &buttons);
    addButtonToScene("Настройки", centerX, centerY, buttonWidth, buttonHeight, this, &buttons);
    addButtonToScene("Выход", centerX, centerY + 70, buttonWidth, buttonHeight, this, &buttons);
    //qDebug() << "buttons added";
}

MainWindowScene::~MainWindowScene() {
    //qDebug() << "start delere main window";
    for (Button* button : buttons) {
        if (button) {
            removeItem(button);
            //qDebug() << "removed";
            delete button;
            //qDebug() << "deleted";
        }
    }
    buttons.clear();
    //qDebug() << "buttons cleared";
    clear();
    //qDebug() << "scene cleared";
}

QVector<Button *> MainWindowScene::getButtons() {
    return buttons;
}
