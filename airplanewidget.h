#ifndef AIRPLANEWIDGET_H
#define AIRPLANEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "seat.h"
#include "database.h"

class Seat;

class AirPlaneWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit AirPlaneWidget(QWidget *parent = 0,
                            DataBase *db = 0);
    ~AirPlaneWidget();

protected:

    void drawBackground(QPainter *painter, const QRectF &rect);

public slots:

    void seatChanged(Seat *seat);
    void seatChanged(QString id);

signals:

    void  notification(const QString msg);

private:

    void drawAirPlane();
    QString idOfSeat(const Seat *seat) const;

    QGraphicsScene *m_scene;
    QMap<QString, Seat*> m_seats;
    DataBase *m_dataBase;

    static const QColor m_paperColor;
};

#endif // AIRPLANEWIDGET_H
