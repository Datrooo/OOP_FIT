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
#include <unordered_map>
#include <functional>

// переместить удаление сразу

class GameController : public QObject {
    Q_OBJECT
public:
    GameController(GameView * view, QWidget* parent = nullptr);
    ~GameController();
    typedef std::function<void()> signalEmitter;





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


    void setupGameKeyHandlers();
    void clearHandlers();

private slots:
    void onKeyPressed(QKeyEvent* event);
    void onKeyReleased(QKeyEvent* event);
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

    std::unordered_map<int, signalEmitter> keyHandlers;
};

#endif // GAMECONTROLLER_H
