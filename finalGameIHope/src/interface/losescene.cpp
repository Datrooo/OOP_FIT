#include "include/interface/losescene.h"

LoseScene::LoseScene() {
    //qDebug() << "NEW LOSE SCENE";
    setSceneRect(0, 0, 1072, 603);

    QImage backgroundImage(":/images/interface/background/lose.jpg");
    QPixmap backgroundPixmap = QPixmap::fromImage(backgroundImage);
    QPixmap scaledPixmap = backgroundPixmap.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    QBrush brush(scaledPixmap);

    setBackgroundBrush(brush);

    qreal buttonWidth = 200;
    qreal buttonHeight = 50;

    qreal centerX = width() / 2 - buttonWidth / 2;
    qreal centerY = height() / 2;

    addButtonToScene("Продолжить", centerX, centerY + 70, buttonWidth, buttonHeight, this, &buttons);
}

LoseScene::~LoseScene() {
    for (Button* button : buttons) {
        removeItem(button);
        delete button;
    }
    buttons.clear();
    clear();
    //qDebug() << "lose scene deleted";
}


QVector<Button *> LoseScene::getButtons() {
    return buttons;
}
