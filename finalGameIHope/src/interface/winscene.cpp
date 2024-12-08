#include "include/interface/winscene.h"
#include "include/interface/button.h"

WinScene::WinScene() {
    setSceneRect(0, 0, 1072, 603);

    QImage backgroundImage(":/images/interface/background/win.png");
    QPixmap backgroundPixmap = QPixmap::fromImage(backgroundImage);
    QPixmap scaledPixmap = backgroundPixmap.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    QBrush brush(scaledPixmap);
    //QBrush brush(backgroundPixmap);
    setBackgroundBrush(brush);

    qreal buttonWidth = 200;
    qreal buttonHeight = 50;

    qreal centerX = width() / 2 - buttonWidth / 2;
    qreal centerY = height() / 2;

    addButtonToScene("Продолжить", centerX, centerY + 70, buttonWidth, buttonHeight, this, &buttons);
    qDebug() << "new scene up";
}


WinScene::~WinScene() {
    removeAllButtons(this, &buttons);
}

QVector<Button *> WinScene::getButtons() {
    return buttons;
}
