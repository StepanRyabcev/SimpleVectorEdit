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
        diamsv b;
        b.x = x;
        b.y = y;
        b.w = width;
        b.h = height;
        b.cll = cl;
        if (m_diamondItemv.size() < diam + 1)
        {
            QGraphicsPolygonItem* a = new QGraphicsPolygonItem(diamond);
            m_diamondItemv.push_back(a);
            diamitemsv.push_back(b);
        }
        else
        {
            m_diamondItemv[diam] = new QGraphicsPolygonItem(diamond);
            diamitemsv[diam] = b;
        }
        if (fillbgr)
            m_diamondItemv[diam]->setBrush(QBrush(cl));
        else
            m_diamondItemv[diam]->setPen(cl);
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

    void bgrf(bool);

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
    QStack<int> undotype;
    int primit = 1; //1 - прямоугольник, 2 - ромб
    QVector<QGraphicsPolygonItem*> m_diamondItemv;
    struct diamsv
    {
        double x, y, h, w;
        QColor cll;
    };
    QVector<diamsv> diamitemsv;
    bool m_drawing;
    int diam = -1;
    bool isDrawing;
    QPointF lastPoint;
    struct lineinfo
    {
        QPen pen;
        int x1, y1, x2, y2;
    };
    QVector<lineinfo> linesv;
    QStack<QGraphicsLineItem*> linep;
    QGraphicsEllipseItem *ellipseItem;
    QStack<QGraphicsEllipseItem*> pointers;
    struct ellipseinfo
    {
        int x, y;
        qreal h, w;
        QColor cll;
    };
    QVector<ellipseinfo> elsave;
    bool fillbgr = false;
};

#endif // GRAPHICSSCENE_H
