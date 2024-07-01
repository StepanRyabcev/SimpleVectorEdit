#include "graphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>
#include <QFile>

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_startPos = event->scenePos();
        m_currentRect = addRect(m_startPos.x(), m_startPos.y(), 0, 0);
        m_currentRect->setBrush(cl);
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
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

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_currentRect && event->button() == Qt::LeftButton) {
        rectv.push_back(rect);
        colorv.push_back(cl);
        m_currentRect = nullptr;
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
        for (int i = 0; i < rectv.size(); i++)
        {
            stream << rectv[i] << colorv[i];
        }
        file.close();
    }
}

void GraphicsScene::loadFromFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        while(!stream.atEnd())
        {
            QRectF rct;
            QColor cll;
            stream >> rct >> cll;
            m_currentRect = addRect(rct);
            m_currentRect->setBrush(cll);
            rectv.push_back(rct);
            colorv.push_back(cll);
        }
        file.close();
    }
}
