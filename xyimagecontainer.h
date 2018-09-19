#ifndef XYIMAGECONTAINER_H
#define XYIMAGECONTAINER_H

#include <QWidget>

class XYImageContainer : public QWidget
{
    Q_OBJECT
public:
    explicit XYImageContainer(QWidget *parent = 0);

    QString centerText() const;
    QColor  backColor() const;
    QColor  textColor() const;

public slots:
    void setType(int type);
    bool loadImage(const QString &path, int width, int height);

signals:
    void loadedImage(const QImage &image, const QString &path);
    void imagePath(const QString &iamge);

protected:
    void paintEvent(QPaintEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);

private:
    QImage::Format m_type;
    QByteArray     m_currentImageData;
    QString        m_currentImage;

};

#endif // XYIMAGECONTAINER_H
