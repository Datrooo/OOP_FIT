#include "include/gameview.h"
#include <QTimer>
#include <QCoreApplication>


GameView::GameView(QWidget* parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {
    setSceneRect(0, 0, 1072, 603);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setWindowFlags(Qt::FramelessWindowHint);
    showFullScreen();
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

GameView::~GameView() {
    delete scene;
}


void GameView::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    } else{
        emit keyPressed(event);
    }
}

void GameView::keyReleaseEvent(QKeyEvent* event) {
    emit keyReleased(event);
}

void GameView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void GameView::start() {
    emit startApp();
}

void GameView::changeScene(QGraphicsScene * newScene) {
    scene = newScene;
    setScene(scene);
    qDebug() << "scene changed";
}
