#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>
#include <QStack>

class GraphicsScene : public QGraphicsScene
{
private:
    void drawDiamond(double x, double y, double width, double height)
    {
        QPolygonF diamond;
        diamond << QPointF(x + width / 2, y)
                << QPointF(x + width, y + height / 2)
                << QPointF(x + width / 2, y + height)
                << QPointF(x, y + height / 2);
        if (m_diamondItemv.size() < diam + 1)
        {
            QGraphicsPolygonItem* a = new QGraphicsPolygonItem(diamond);
            m_diamondItemv.push_back(a);
        }
        else
            m_diamondItemv[diam] = new QGraphicsPolygonItem(diamond);
        m_diamondItemv[diam]->setBrush(QBrush(cl));
        addItem(m_diamondItemv[diam]);
    }

public:
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

    void ChangeColor(QColor a);

    void saveToFile(QString);

    void loadFromFile(QString);

    void undo();

    void changePrimitive(int);

private:
    QPointF m_startPos;
    QGraphicsRectItem *m_currentRect = nullptr;
    QColor cl = Qt::blue;
    QRectF rect;
    QVector<QGraphicsRectItem*> rectitmv;
    QVector<QRectF> rectv;
    QVector<QColor> colorv;
    QStack<QVector<QRectF>> rectv_b;
    QStack<QVector<QColor>> colorv_b;
    int primit = 1; //1 - прямоугольник, 2 - ромб
    QVector<QGraphicsPolygonItem*> m_diamondItemv;
    QGraphicsPolygonItem*  m_diamondItem;
    bool m_drawing;
    int diam = -1;
};

#endif // GRAPHICSSCENE_H
