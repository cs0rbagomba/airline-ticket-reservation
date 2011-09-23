#ifndef SEAT_H
#define SEAT_H

#include <QGraphicsTextItem>

#include "airplanewidget.h"

class AirPlaneWidget;

class Seat : public QGraphicsTextItem
{
    Q_OBJECT

public:
    explicit Seat(AirPlaneWidget *airPlaneWidget = 0);
    ~Seat();

protected:

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    AirPlaneWidget *m_airPlaneWidget;
};

#endif // SEAT_H
