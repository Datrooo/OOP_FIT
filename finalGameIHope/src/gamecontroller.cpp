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

void GameController::analiseKeyPressed(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        view->close();
    } else if (event->key() == Qt::Key_Left) {
        emit moveLeft();
    } else if (event->key() == Qt::Key_Right) {
        emit moveRight();
    } else if (event->key() == Qt::Key_Up) {
        emit jump();
    } else if (event->key() == Qt::Key_Down) {
        emit goDown();
    } else if (event->key() == Qt::Key_Q) {
        qDebug() << "Q pressed";
        emit startShoot();
    } else if (event->key() == Qt::Key_R) {
        emit changeShootingMode();
    }
}

void GameController::analiseKeyReleased(QKeyEvent* event) {
    if (event->key() == Qt::Key_Q) {
        emit shoot();
    } else if ((event->key() == Qt::Key_Left && gamescene->getPlayer()->getHorizontalSpeed() < 0) ||
               (event->key() == Qt::Key_Right && gamescene->getPlayer()->getHorizontalSpeed() > 0)) {
        emit stopMoving();
    }
}

void GameController::connectGameMenu(){
    soundController->playSound("qrc:/music/Kevin-MacLeod-Unholy-Knight.mpga.wav");
    QVector <Button *> buttons = mainwindowscene->getButtons();
    connect(buttons.at(0), &Button::clicked, this, &GameController::changeSceneToGame);
    connect(buttons.at(1), &Button::clicked, this, &GameController::changeSceneToSettings);
    connect(buttons.at(2), &Button::clicked, this, &GameController::exit);
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
    connect(view, &GameView::keyPressed, this, &GameController::analiseKeyPressed);
    connect(view, &GameView::keyReleased, this, &GameController::analiseKeyReleased);
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
    disconnect(view, &GameView::keyPressed, this, &GameController::analiseKeyPressed);
    disconnect(view, &GameView::keyReleased, this, &GameController::analiseKeyReleased);
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
    qDebug() << "connection lose";
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
        disconnectGameScene();
        qDebug() << "dfdfd";
        delete gamescene;
        qDebug() << "1111";
        gamescene = nullptr;
    }

    if (mainwindowscene != nullptr) {
        disconnectGameMenu();
        delete mainwindowscene;
        mainwindowscene = nullptr;
    }

    if (winscene != nullptr) {
        disconnectGameWin();
        delete winscene;
        winscene = nullptr;
    }
    if (losescene != nullptr) {
        disconnectGameLose();
        delete losescene;
        losescene = nullptr;
    }
    mainwindowscene = new MainWindowScene();
    view->changeScene(mainwindowscene);
    view->resetTransform();
    view->fitInView(mainwindowscene->sceneRect(), Qt::KeepAspectRatio);
    connectGameMenu();

}

void GameController::changeSceneToGame() {
    qDebug() << "gameScene";
    gamescene = new GameScene();

    //view->changeScene(gamescene);

    disconnectGameMenu();
    view->setScene(gamescene);
    if (mainwindowscene != nullptr) {
        //disconnectGameMenu();
        delete mainwindowscene;
        qDebug()  << "menu deleted";
        mainwindowscene = nullptr;
    }

    connectGameScene();


}

void GameController::changeSceneToWin(){

    winscene = new WinScene();
    //view->changeScene(winscene);
    view->setScene(winscene);
    // disconnectGameScene();
    // if (gamescene != nullptr) {
    //     //disconnectGameScene();
    //     qDebug() << "dfdfd";
    //     delete gamescene;
    //     qDebug() << "1111";
    //     gamescene = nullptr;
    // }
    connectGameWin();
}



void GameController::changeSceneToLose(){

    // if (losescene != nullptr) {
    //     delete losescene;
    //     losescene = nullptr;
    // }
    losescene = new LoseScene();
    //view->changeScene(losescene);
    view->setScene(losescene);
    // disconnectGameScene();
    // if (gamescene != nullptr) {
    //     disconnectGameScene();
    //     qDebug() << "dfdfd";
    //     delete gamescene;
    //     qDebug() << "1111";
    //     gamescene = nullptr;
    // }

    connectGameLose();
    qDebug() << "end";

}

void GameController::changeSceneToSettings(){
    settingsscene = new SettingsScene();
    view->changeScene(settingsscene);
    disconnectGameMenu();
    connectSettingsScene();
}

void GameController::exit(){
    view->close();
}







