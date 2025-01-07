#include "include/interface/button.h"
#include <QGraphicsScene>
#include <QVector>


Button::Button(const QString& text, qreal x, qreal y, qreal width, qreal height)
    : QObject(), QGraphicsPathItem() {
    QPainterPath path;
    path.addRoundedRect(0, 0, width, height, 15, 15);
    setPath(path);


    defaultBrush = QBrush(Qt::lightGray);
    hoverBrush = QBrush(Qt::yellow);
    setBrush(defaultBrush);
    setPen(QPen(Qt::black, 2));

    setPos(x, y);

    buttonText = new QGraphicsTextItem(text, this);
    QFont font("Arial", 14, QFont::Bold);
    buttonText->setFont(font);


    QRectF textRect = buttonText->boundingRect();
    buttonText->setPos((width - textRect.width()) / 2, (height - textRect.height()) / 2);

    setAcceptHoverEvents(true);
}

Button::~Button() {
    delete buttonText;
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    setBrush(hoverBrush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    setBrush(defaultBrush);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit clicked();
}

void addButtonToScene(const QString& text, qreal x, qreal y, qreal width, qreal height, QGraphicsScene * scene, QVector<Button *> *buttons) {
    Button* newButton = new Button(text, x, y, width, height);
    scene->addItem(newButton);
    buttons->append(newButton);
}
