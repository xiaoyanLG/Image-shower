#include "xyimagecontainer.h"
#include <QPainter>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

XYImageContainer::XYImageContainer(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
}

QString XYImageContainer::centerText() const
{
    return QStringLiteral("请把图片文件拖拽到此！");
}

QColor XYImageContainer::backColor() const
{
    return QColor("darkCyan");
}

QColor XYImageContainer::textColor() const
{
    return QColor("darkRed");
}

void XYImageContainer::setType(int type)
{
    m_type = (QImage::Format)type;
}

bool XYImageContainer::loadImage(const QString &path, int width, int height)
{
    m_currentImage = path;
    QFile file(m_currentImage);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray filedata = file.readAll();
        m_currentImageData.resize(width * height * 4);
        m_currentImageData.fill(0x00);
        memcpy(m_currentImageData.data(), filedata.data(),
               qMin(filedata.size(), m_currentImageData.size()));
        QImage image((uchar *)m_currentImageData.data(), width, height, m_type);
        if (!image.isNull())
        {
            emit imagePath(m_currentImage);
            emit loadedImage(image, m_currentImage);
            return true;
        }
    }

    return false;
}

void XYImageContainer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // 画背景色
    painter.setPen(backColor());
    painter.setBrush(backColor());
    painter.drawRect(rect());

    // 画中心文字
    QFont font = painter.font();
    font.setFamily(QStringLiteral("微软雅黑"));
    font.setPointSize(40);


    QFontMetrics metrics(font);

    while (metrics.width(centerText()) > width() - 10)
    {
        font.setPointSize(font.pointSize() - 2);
        metrics = QFontMetrics(font);
        if (font.pointSize() < 15)
        {
            break;
        }
    }

    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setColor(textColor());
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawText(rect(), centerText(), QTextOption(Qt::AlignCenter));
}

void XYImageContainer::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void XYImageContainer::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void XYImageContainer::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        foreach (QUrl url, event->mimeData()->urls())
        {
            m_currentImage = url.toLocalFile();
            emit imagePath(m_currentImage);
            break;
        }
    }
}
