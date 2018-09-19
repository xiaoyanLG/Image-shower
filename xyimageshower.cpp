#include "xyimageshower.h"
#include <QPainter>

XYImageShower::XYImageShower(QWidget *parent)
    : QFrame(parent)
{
    m_ratio = 1.0;
    m_border = true;
}

void XYImageShower::setBorder(bool border)
{
    m_border = border;
    update();
}

void XYImageShower::zoomOut()
{
    m_ratio -= 0.1;
    update();
}

void XYImageShower::zoomIn()
{
    m_ratio += 0.1;
    update();
}

void XYImageShower::imageChanged(const QImage &image)
{
    m_image = image;
    update();
}

void XYImageShower::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing);

    int w = m_image.width() * m_ratio;
    int h = m_image.height() * m_ratio;
    int x = (width() - w) / 2;
    int y = (height() - h) / 2;

    painter.drawImage(QRect(x, y, w, h), m_image);

    if (m_border)
    {
        painter.setPen(QColor("red"));
        painter.drawRect(QRect(x, y, w, h));
    }

}
