#include "seat.h"

#include <QStyleOption>
#include <QMessageBox>
#include <QApplication>

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

    // taken seats are gray
    // free seats are blue
    // a free seat when the mouse is over it is red

    if (m_taken) {
        painter->setBrush(Qt::gray);
    } else {
        if (option->state & QStyle::State_MouseOver) {
            painter->setBrush(Qt::red);
        } else {
            painter->setBrush(Qt::blue);
        }
    }

    painter->drawRect(QRect(-7,-7,20,20));
}

QRectF Seat::boundingRect() const
{
    return QRectF(-7,-7,20,20);
}

void Seat::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (m_taken) {
        if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
            cancelReservationDialog();
        }
        return;
    }
    setTaken(true);
    emit clicked(this);
}

void Seat::cancelReservationDialog()
{
    QMessageBox dialog(m_airPlaneWidget);
    dialog.setText("Really cancel reservation?");
    dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dialog.setDefaultButton(QMessageBox::No);
    int ret = dialog.exec();
    switch (ret) {
        case QMessageBox::Yes:
            // Save was clicked
            setTaken(false);
            emit clicked(this);
            return;
        case QMessageBox::No:
            // Don't Save was clicked
            return;
        default:
            // should never be reached
            return;
     }
}
