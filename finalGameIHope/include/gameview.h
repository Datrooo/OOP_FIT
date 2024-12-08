#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>



class GameView : public QGraphicsView {
    Q_OBJECT
public:
    GameView(QWidget* parent = nullptr);
    ~GameView();
    void start();
    void changeScene(QGraphicsScene * newScene);

signals:
    void startApp();
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);

private:
    QGraphicsScene* scene;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;


};

#endif // GAMEVIEW_H
