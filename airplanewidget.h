#ifndef AIRPLANEWIDGET_H
#define AIRPLANEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>

class AirPlaneWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit AirPlaneWidget(QWidget *parent = 0);
    ~AirPlaneWidget();

protected:

    void drawBackground(QPainter *painter, const QRectF &rect);

private:

    QGraphicsScene *m_scene;

    static const QColor m_paperColor;
};

#endif // AIRPLANEWIDGET_H
