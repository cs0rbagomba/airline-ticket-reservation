#include "seat.h"

Seat::Seat(AirPlaneWidget *airPlaneWidget) :
    m_airPlaneWidget(airPlaneWidget)
{

}

Seat::~Seat()
{

}

void Seat::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *w)
{
    Q_UNUSED(option);
    Q_UNUSED(w);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);

    painter->drawEllipse(-7, -7, 20, 20);
}
