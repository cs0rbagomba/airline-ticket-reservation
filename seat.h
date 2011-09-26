#ifndef SEAT_H
#define SEAT_H

#include <QGraphicsItem>

#include "airplanewidget.h"

class AirPlaneWidget;

class Seat : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

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

    void mousePressEvent (QGraphicsSceneMouseEvent *event);

signals:

    void clicked(Seat*);

private:

    void cancelReservationDialog();

    AirPlaneWidget *m_airPlaneWidget;
    bool m_taken;
};

#endif // SEAT_H
