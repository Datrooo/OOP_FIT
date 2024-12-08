#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Button : public QObject, public QGraphicsPathItem {
    Q_OBJECT
public:
    Button(const QString& text, qreal x, qreal y, qreal width, qreal height);

signals:
    void clicked();

private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QGraphicsTextItem* buttonText;
    QBrush defaultBrush;
    QBrush hoverBrush;
};


void addButtonToScene(const QString& text, qreal x, qreal y, qreal width, qreal height, QGraphicsScene * scene, QVector<Button *> *buttons);
void removeAllButtons(QGraphicsScene * scene, QVector<Button *> *buttons);


#endif // BUTTON_H
