#include "include/interface/settingsscene.h"


SettingsScene::SettingsScene() {    setSceneRect(0, 0, 1072, 603);

    QImage backgroundImage(":/images/interface/background/set.png");
    QPixmap backgroundPixmap = QPixmap::fromImage(backgroundImage);

    QPixmap scaledPixmap = backgroundPixmap.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);

    QBrush brush(scaledPixmap);
    setBackgroundBrush(brush);


    qreal buttonWidth = 200;
    qreal buttonHeight = 50;

    qreal centerX = width() / 2 - buttonWidth / 2;
    qreal centerY = height() / 2;

    addButtonToScene("Выход", centerX, centerY + 210, buttonWidth, buttonHeight, this, &buttons);

    QGraphicsTextItem* title = addText("Настройки");
    title->setFont(QFont("Arial", 24, QFont::Bold));
    title->setDefaultTextColor(Qt::white);
    title->setPos(width() / 2 - title->boundingRect().width() / 2, 20);

    QGraphicsTextItem* volumeText = addText("Громкость");
    volumeText->setFont(QFont("Arial", 20));
    volumeText->setDefaultTextColor(Qt::white);
    volumeText->setPos(width() / 2 - volumeText->boundingRect().width() / 2, 80);

    slider = new VolumeSlider(width()/ 2 - 150, 150, 300, 10);
    addItem(slider);
    slider->setVolumeLevel(50);

}

SettingsScene::~SettingsScene() {
    delete slider;
    removeAllButtons(this, &buttons);
}

QVector<Button *> SettingsScene::getButtons() {
    return buttons;
}

VolumeSlider *SettingsScene::getVolumeSlider() {
    return slider;
}
