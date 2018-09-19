#ifndef XYIMAGESHOWER_H
#define XYIMAGESHOWER_H

#include <QFrame>

class XYImageShower : public QFrame
{
    Q_OBJECT
public:
    explicit XYImageShower(QWidget *parent = 0);

public slots:
    void setBorder(bool border);
    void zoomOut();
    void zoomIn();
    void imageChanged(const QImage &image);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QImage m_image;

    float  m_ratio;
    bool   m_border;

};

#endif // XYIMAGESHOWER_H
