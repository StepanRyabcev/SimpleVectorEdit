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
            QPointF position = event->scenePos();
            double a = position.x();
            double b = position.y();
            drawDiamond(a, b, 50.0, 50.0); // Размеры ромба по умолчанию: 50x50
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
        if (event->buttons() & Qt::LeftButton)
        {
            QPointF position = event->scenePos();
            drawDiamond(position.x(), position.y(), 50, 50); // Размеры ромба по умолчанию: 50x50
        }
    }
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (primit == 1)
    {
    if (m_currentRect && event->button() == Qt::LeftButton) {
        rectv_b.push(rectv);
        colorv_b.push(colorv);
        rectitmv.push_back(m_currentRect);
        rectv.push_back(rect);
        colorv.push_back(cl);
        m_currentRect = nullptr;
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
        file.close();
    }
}

void GraphicsScene::loadFromFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream >> rectv >> colorv;
        for (int i = 0; i < rectv.size(); i++)
        {
            m_currentRect = addRect(rectv[i]);
            m_currentRect->setBrush(colorv[i]);
            rectitmv.push_back(m_currentRect);
        }
        file.close();
    }
}

void GraphicsScene::undo()
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

void GraphicsScene::changePrimitive(int a)
{
    primit = a;
}
