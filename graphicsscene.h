#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>

class GraphicsScene : public QGraphicsScene
{
public:
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

    void ChangeColor(QColor a);

    void saveToFile(QString);

    void loadFromFile(QString);
private:
    QPointF m_startPos;
    QGraphicsRectItem *m_currentRect = nullptr;
    QColor cl = Qt::blue;
    QRectF rect;
    QVector<QRectF> rectv;
    QVector<QColor> colorv;
};

#endif // GRAPHICSSCENE_H
