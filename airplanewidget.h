#ifndef AIRPLANEWIDGET_H
#define AIRPLANEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "seat.h"

class Seat;

class AirPlaneWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit AirPlaneWidget(QWidget *parent = 0);
    ~AirPlaneWidget();

protected:

    void drawBackground(QPainter *painter, const QRectF &rect);

public slots:

    void changed();

private:

    QGraphicsScene *m_scene;
    QList<Seat*> m_seats;

    static const QColor m_paperColor;
};

#endif // AIRPLANEWIDGET_H
