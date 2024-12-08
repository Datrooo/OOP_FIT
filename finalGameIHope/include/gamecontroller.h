#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "gameview.h"
#include "include/interface/mainwindowscene.h"
#include "include/interface/settingsscene.h"
#include "include/interface/gamescene.h"
#include "include/interface/winscene.h"
#include "include/interface/losescene.h"
#include "soundcontroller.h"

// переместить удаление сразу

class GameController : public QObject {
    Q_OBJECT
public:
    GameController(GameView * view, QWidget* parent = nullptr);
    ~GameController();


private:
    void disconnectGameScene();
    void disconnectGameLose();
    void disconnectGameWin();
    void disconnectGameMenu();
    void disconnectSettingsScene();

    void connectGameScene();
    void connectGameLose();
    void connectGameWin();
    void connectGameMenu();
    void connectSettingsScene();

private slots:
    void analiseKeyPressed(QKeyEvent* event);
    void analiseKeyReleased(QKeyEvent* event);
    void changeSceneToGame();
    void changeSceneToMenu();
    void changeSceneToWin();
    void changeSceneToLose();
    void changeSceneToSettings();
    void exit();

signals:
    void moveLeft();
    void moveRight();
    void jump();
    void changeShootingMode();
    void startShoot();
    void shoot();
    void stopMoving();
    void goDown();


private:
    GameView * view;
    GameScene * gamescene = nullptr;
    MainWindowScene * mainwindowscene = nullptr;
    SettingsScene * settingsscene = nullptr;
    WinScene * winscene = nullptr;
    LoseScene * losescene = nullptr;
    SoundController * soundController;
};

#endif // GAMECONTROLLER_H
