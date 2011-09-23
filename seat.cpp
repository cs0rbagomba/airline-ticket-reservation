#include "seat.h"

#include <QStyleOption>

Seat::Seat(AirPlaneWidget *airPlaneWidget,
           const bool taken) :
    m_airPlaneWidget(airPlaneWidget),
    m_taken(taken)
{
    setAcceptHoverEvents(true);
}

Seat::~Seat()
{

}

bool Seat::taken() const
{
    return m_taken;
}

void Seat::setTaken(const bool taken)
{
    m_taken = taken;
    setAcceptHoverEvents(!taken);
    update();
}

void Seat::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *w)
{
    Q_UNUSED(w);

    painter->setPen(Qt::NoPen);

    if (m_taken) {
        painter->setBrush(Qt::gray);
    } else {
        if (option->state & QStyle::State_MouseOver) {
            painter->setBrush(Qt::red);
        } else {
            painter->setBrush(Qt::blue);
        }
    }

    /// @todo draw a seat-like box
    painter->drawEllipse(-7, -7, 20, 20);
}

QRectF Seat::boundingRect() const
{

    /// @todo adjust after paint() is rewritten
    qreal adjust = 2;
    return QRectF(-10 - adjust, -10 - adjust,
                   23 + adjust, 23 + adjust);
}

void Seat::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    setTaken(!m_taken);
    emit clicked();
}
