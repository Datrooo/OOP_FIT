#include <QApplication>
//#include "gameview.h"
#include "include/gamecontroller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameView * view = new GameView;
    GameController * gameController = new GameController(view);

    view->start();
    view->show();
    app.exec();
    delete view;
    delete gameController;
    return 0;
}
