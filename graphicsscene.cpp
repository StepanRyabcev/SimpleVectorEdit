#include "graphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>
#include <QFile>

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (primit == 1)
    {
    if (event->button() == Qt::LeftButton) {
        m_startPos = event->scenePos();
        m_currentRect = addRect(m_startPos.x(), m_startPos.y(), 0, 0);
        m_currentRect->setBrush(cl);
    }
    }
    if (primit == 2)
    {
        if (event->button() == Qt::LeftButton)
        {
            m_startPos = event->scenePos();
            m_drawing = true;
            diam++;
        }
    }
    if (primit == 3)
    {
        if (event->button() == Qt::LeftButton)
        {
            isDrawing = true;
            lastPoint = event->scenePos();
        }
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (primit == 1)
    {
    if (m_currentRect && event->buttons() & Qt::LeftButton) {
        qreal width = qAbs(event->scenePos().x() - m_startPos.x());
        qreal height = qAbs(event->scenePos().y() - m_startPos.y());

        // Ограничение по высоте сцены
        const qreal sceneHeight = this->height();
        height = qMin(height, sceneHeight);

        // Определяем новые координаты верхнего левого угла квадрата
        qreal x = std::min(m_startPos.x(), event->scenePos().x());
        qreal y = std::min(m_startPos.y(), event->scenePos().y());
        rect = QRectF(x, y, width, height);
        m_currentRect->setRect(rect);
    }
    }
    if (primit == 2)
    {
        if (m_drawing && event->buttons() & Qt::LeftButton)
        {
            QPointF currentPos = event->scenePos();
            qreal width = std::abs(currentPos.x() - m_startPos.x()) * 2;
            qreal height = std::abs(currentPos.y() - m_startPos.y()) * 2;
            if (!(m_diamondItemv.size() < diam + 1))
            {
                removeItem(m_diamondItemv[diam]);
                delete m_diamondItemv[diam];
            }
            drawDiamond(m_startPos.x(), m_startPos.y(), width, height);
    }
    }
    if (primit == 3)
    {
        if ((event->buttons() & Qt::LeftButton) && isDrawing)
        {
            QPen pen(cl, 2, Qt::SolidLine, Qt::RoundCap);
            addLine(lastPoint.x(), lastPoint.y(), event->scenePos().x(), event->scenePos().y(), pen);
            lastPoint = event->scenePos();
        }
    }
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (primit == 1)
    {
    if (m_currentRect && event->button() == Qt::LeftButton) {
        rectv_b.push(rectv);
        colorv_b.push(colorv);
        undotype.push(1);
        rectitmv.push_back(m_currentRect);
        rectv.push_back(rect);
        colorv.push_back(cl);
        m_currentRect = nullptr;
    }
    }
    if (primit == 2)
    {
        if (event->button() == Qt::LeftButton)
        {
            m_drawing = false;
            undotype.push(2 );
        }
    }
    if (primit == 3)
    {
        if (event->button() == Qt::LeftButton && isDrawing)
        {
            isDrawing = false;
        }
    }
}

void GraphicsScene::ChangeColor(QColor a)
{
    cl = a;
}

void GraphicsScene::saveToFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream << rectv << colorv;
        int n = diamitemsv.size();
        stream << n;
        qDebug() << n;
        for (int i = 0; i < diamitemsv.size(); i++)
            stream << diamitemsv[i].x << diamitemsv[i].y << diamitemsv[i].h << diamitemsv[i].w << diamitemsv[i].cll;
        file.close();
    }
}

void GraphicsScene::loadFromFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        int n;
        stream >> rectv >> colorv;
        for (int i = 0; i < rectv.size(); i++)
        {
            m_currentRect = addRect(rectv[i]);
            m_currentRect->setBrush(colorv[i]);
            rectitmv.push_back(m_currentRect);
        }
        stream >> n;
        qDebug() << n;
        for (int i = 0; i < n; i++)
        {
            diamsv b;
            stream >> b.x >> b.y >> b.h >> b.w >> b.cll ;
            diamitemsv.push_back(b);
            ChangeColor(b.cll);
            diam++;
            drawDiamond(b.x, b.y, b.h, b.w);
        }
        file.close();
    }
}

void GraphicsScene::undo()
{
    if (!(undotype.isEmpty()))
    {
        int fl = undotype.pop();
        if (fl == 1)
        {
    if (!rectv_b.isEmpty())
    {
    for (int i = 0; i < rectitmv.size(); i++)
    {
        removeItem(rectitmv[i]);
        delete rectitmv[i];
    }
    rectv.clear();
    colorv.clear();
    rectitmv.clear();
    rectv = rectv_b.pop();
    colorv = colorv_b.pop();
    for (int i = 0; i < rectv.size(); i++)
    {
        m_currentRect = addRect(rectv[i]);
        m_currentRect->setBrush(colorv[i]);
        rectitmv.push_back(m_currentRect);
    }
    }
        }
        if (fl == 2)
        {
            delete m_diamondItemv.last();
            m_diamondItemv.removeLast();
            diam--;
        }
    }
}

void GraphicsScene::changePrimitive(int a)
{
    primit = a;
}
