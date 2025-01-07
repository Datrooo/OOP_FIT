#include "include/gamecontroller.h"
#include "include/interface/button.h"

GameController::GameController(GameView * view, QWidget* parent) : view(view) {
    connect(view, &GameView::startApp, this, &GameController::changeSceneToMenu);
    soundController = new SoundController();
    soundController->setVolume(50);
    soundController->getMediaPlayer()->setLoops(QMediaPlayer::Infinite);
}

GameController::~GameController() {
    if (gamescene != nullptr) {
        disconnectGameScene();
    } else if (mainwindowscene != nullptr) {
        disconnectGameMenu();
    } else if (losescene != nullptr) {
        disconnectGameLose();
    } else if (winscene != nullptr) {
        disconnectGameWin();
    } else {
        disconnectSettingsScene();
    }

    delete view;
    delete gamescene;
    delete mainwindowscene;
    delete settingsscene;
    delete winscene;
    delete losescene;
    delete soundController;
}

void GameController::onKeyPressed(QKeyEvent* event) {
    auto it = keyHandlers.find(event->key());
    if (it != keyHandlers.end()) {
        it->second();
    }
}

void GameController::onKeyReleased(QKeyEvent* event) {
    if (event->key() == Qt::Key_Q) {
        emit shoot();
    } else if ((event->key() == Qt::Key_Left && gamescene->getPlayer()->getHorizontalSpeed() < 0) ||
               (event->key() == Qt::Key_Right && gamescene->getPlayer()->getHorizontalSpeed() > 0)) {
        emit stopMoving();
    }
}

void GameController::clearHandlers(){
    keyHandlers.clear();
}

void GameController::setupGameKeyHandlers() {
    clearHandlers();
    keyHandlers[Qt::Key_Escape] = [this]() { view->close(); };
    keyHandlers[Qt::Key_Left] = [this]() { emit moveLeft(); };
    keyHandlers[Qt::Key_Right] = [this]() { emit moveRight(); };
    keyHandlers[Qt::Key_Up] = [this]() { emit jump(); };
    keyHandlers[Qt::Key_Down] = [this]() { emit goDown(); };
    keyHandlers[Qt::Key_Q] = [this]() { emit startShoot(); };
    keyHandlers[Qt::Key_R] = [this]() { emit changeShootingMode(); };
}

void GameController::connectGameMenu(){
    //qDebug() << "connection game menu started";
    soundController->playSound("qrc:/music/Kevin-MacLeod-Unholy-Knight.mpga.wav");
    //qDebug() << "music!";
    QVector <Button *> buttons = mainwindowscene->getButtons();
    //qDebug() << "buttons got";
    connect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToGame);
    //qDebug() << "first";
    connect(buttons.at(1), &Button::clicked, this, &GameController::changeSceneToSettings);
    //qDebug() << "second";
    connect(buttons.at(2), &Button::clicked, this, &GameController::exit);
    //qDebug() << "third";
}

void GameController::disconnectGameMenu(){
    soundController->getMediaPlayer()->stop();
    QVector <Button *> buttons = mainwindowscene->getButtons();
    disconnect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToGame);
    disconnect(buttons.at(1), &Button::clicked, this, &GameController::changeSceneToSettings);
    disconnect(buttons.at(2), &Button::clicked, this, &GameController::exit);
}

void GameController::connectGameScene(){
    soundController->playSound("qrc:/music/game.mp3");
    setupGameKeyHandlers();
    connect(view, &GameView::keyPressed, this, &GameController::onKeyPressed);
    connect(view, &GameView::keyReleased, this, &GameController::onKeyReleased);
    connect(this, &GameController::moveLeft, gamescene->getPlayer(),&Player::moveLeft);
    connect(this,&GameController::moveRight, gamescene->getPlayer(), &Player::moveRight);
    connect(this,&GameController::jump, gamescene->getPlayer(), &Player::jump);
    connect(this, &GameController::goDown, gamescene->getPlayer(), &Player::goDown);
    connect(this,&GameController::startShoot, gamescene->getPlayer(), &Player::startShooting);
    connect(this,&GameController::changeShootingMode, gamescene->getPlayer(), &Player::changeShootingMode);
    connect(this,&GameController::shoot, gamescene->getPlayer(), &Player::shootBullet);
    connect(this,&GameController::stopMoving, gamescene->getPlayer(), &Player::stopMoving);
    connect(gamescene, &GameScene::levelCompleted, this, &GameController::changeSceneToWin);
    connect(gamescene, &GameScene::gameOver, this, &GameController::changeSceneToLose);
}

void GameController::disconnectGameScene(){
    soundController->getMediaPlayer()->stop();
    clearHandlers();
    disconnect(view, &GameView::keyPressed, this, &GameController::onKeyPressed);
    disconnect(view, &GameView::keyReleased, this, &GameController::onKeyReleased);
    disconnect(this, &GameController::moveLeft, gamescene->getPlayer(),&Player::moveLeft);
    disconnect(this,&GameController::moveRight, gamescene->getPlayer(), &Player::moveRight);
    disconnect(this,&GameController::jump, gamescene->getPlayer(), &Player::jump);
    disconnect(this, &GameController::goDown, gamescene->getPlayer(), &Player::goDown);
    disconnect(this,&GameController::startShoot, gamescene->getPlayer(), &Player::startShooting);
    disconnect(this,&GameController::changeShootingMode, gamescene->getPlayer(), &Player::changeShootingMode);
    disconnect(this,&GameController::shoot, gamescene->getPlayer(), &Player::shootBullet);
    disconnect(this,&GameController::stopMoving, gamescene->getPlayer(), &Player::stopMoving);
    disconnect(gamescene, &GameScene::levelCompleted, this, &GameController::changeSceneToWin);
    disconnect(gamescene, &GameScene::gameOver, this, &GameController::changeSceneToLose);
}



void GameController::connectGameWin(){
    soundController->playSound("qrc:/music/victory.mp3");
    QVector <Button *> buttons = winscene->getButtons();
    connect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToMenu);
}

void GameController::disconnectGameWin(){
    soundController->getMediaPlayer()->stop();
    QVector <Button *> buttons = winscene->getButtons();
    disconnect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToMenu);
}

void GameController::connectGameLose(){
    //qDebug() << "connection lose";
    soundController->playSound("qrc:/music/lose.mp3");
    QVector <Button *> buttons =losescene->getButtons();
    connect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToMenu);
}

void GameController::disconnectGameLose(){
    soundController->getMediaPlayer()->stop();
    QVector <Button *> buttons = losescene->getButtons();
    disconnect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToMenu);
}

void GameController::connectSettingsScene(){
    soundController->playSound("qrc:/music/Weary-Pines-Birth.mpga.wav");
    QVector <Button *> buttons =settingsscene->getButtons();
    connect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToMenu);
    connect(settingsscene->getVolumeSlider(), &VolumeSlider::volumeChanged, soundController, &SoundController::setVolume);
}

void GameController::disconnectSettingsScene(){
    soundController->getMediaPlayer()->stop();
    QVector <Button *> buttons =settingsscene->getButtons();
    disconnect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToMenu);
    disconnect(settingsscene->getVolumeSlider(), &VolumeSlider::volumeChanged, soundController, &SoundController::setVolume);
}

void GameController::changeSceneToMenu(){
    if (gamescene != nullptr) {
        //qDebug() << "gamescene start delete";
        disconnectGameScene();
        //qDebug() << "dfdfd";
        delete gamescene;
        //qDebug() << "1111";
        gamescene = nullptr;
    }
    if (settingsscene != nullptr) {
        //qDebug() << "settings scene start delete";
        disconnectSettingsScene();
        delete settingsscene;
        settingsscene = nullptr;
    }
    if (winscene != nullptr) {
        //qDebug() << "win scene start delete";
        disconnectGameWin();
        delete winscene;
        winscene = nullptr;
    }
    if (losescene != nullptr) {
        //qDebug() << "lose scene start delete";
        disconnectGameLose();
        delete losescene;
        losescene = nullptr;
    }
    mainwindowscene = new MainWindowScene();
    view->changeScene(mainwindowscene);
    //view->setScene(mainwindowscene);
    connectGameMenu();
    //qDebug() << "sucses";

}

void GameController::changeSceneToGame() {
    //qDebug() << "gameScene";
    gamescene = new GameScene();

    view->changeScene(gamescene);


    //view->setScene(gamescene);
    if (mainwindowscene) {
        disconnectGameMenu();
        delete mainwindowscene;
        qDebug()  << "menu deleted";
        mainwindowscene = nullptr;
    }

    //disconnectGameMenu();

    connectGameScene();


}

void GameController::changeSceneToWin(){

    // if (gamescene) {
    //     disconnectGameScene();
    //     qDebug() << "dfdfd";
    //     delete gamescene;
    //     qDebug() << "1111";
    //     gamescene = nullptr;
    // }
    winscene = new WinScene();
    view->changeScene(winscene);
    connectGameWin();
}



void GameController::changeSceneToLose(){
    // if (gamescene) {
    //     disconnectGameScene();
    //     qDebug() << "dfdfd";
    //     delete gamescene;
    //     qDebug() << "1111";
    //     gamescene = nullptr;
    // }
    if (!losescene && !winscene){
        losescene = new LoseScene();
        view->changeScene(losescene);
        connectGameLose();
        //qDebug() << "end";
    }
}

void GameController::changeSceneToSettings(){
    if (mainwindowscene) {
        qDebug() << "main window start delete";
        disconnectGameMenu();
        delete mainwindowscene;
        mainwindowscene = nullptr;
    }
    settingsscene = new SettingsScene();
    view->changeScene(settingsscene);
    //view->setScene(settingsscene);
    //disconnectGameMenu();
    connectSettingsScene();

}

void GameController::exit(){
    view->close();
}







