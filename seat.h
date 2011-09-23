#ifndef SEAT_H
#define SEAT_H

#include <QGraphicsItem>

#include "airplanewidget.h"

class AirPlaneWidget;

class Seat : public QGraphicsItem
{
public:
    explicit Seat(AirPlaneWidget *airPlaneWidget = 0,
                  const bool taken = false);
    ~Seat();

    bool taken() const;
    void setTaken(const bool taken = true);

protected:

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

    void mousePressEvent (QGraphicsSceneMouseEvent * event);

private:
    AirPlaneWidget *m_airPlaneWidget;
    bool m_taken;
};

#endif // SEAT_H
