#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <QGraphicsScene>
#include "button.h"
#include "volumeslider.h"

class SettingsScene : public QGraphicsScene {
public:
    SettingsScene();
    ~SettingsScene();
    QVector<Button *> getButtons();
    VolumeSlider* getVolumeSlider();

private:
    VolumeSlider *slider;
    QVector<Button*> buttons;
};

#endif // SETTINGSSCENE_H
