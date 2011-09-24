#include "airplanewidget.h"

const QColor AirPlaneWidget::m_paperColor(255,255,153);

AirPlaneWidget::AirPlaneWidget(QWidget *parent,
                               DataBase *db) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_dataBase(db)
{
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(-200, -200, 400, 400);
    setScene(m_scene);

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(500, 500);

    drawAirPlane();

    connect(m_dataBase, SIGNAL(dataChanged(QString)),
            this, SLOT(seatChanged(QString)) );
}

AirPlaneWidget::~AirPlaneWidget()
{

}

void AirPlaneWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    /// @todo draw a real airplane

    painter->fillRect(m_scene->sceneRect(), AirPlaneWidget::m_paperColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(m_scene->sceneRect());
}

void AirPlaneWidget::seatChanged(Seat *seat)
{
    QString id(idOfSeat(seat));

    QString msg = QString("Seat %1 has been changed").arg(id);
    emit notification(msg);

    /// @todo handle seat reservation
    if (!m_dataBase->writeData(id, seat->taken())) {
        QString error = QString("Couldn't reserve seat %1 - DataBase error.").arg(id);
        emit notification(error);

        // reverse state
        seat->setTaken(!(seat->taken()));
    }
}

void AirPlaneWidget::seatChanged(QString id)
{
    QString msg = QString("Seat %1 has been changed - from DataBase").arg(id);
    emit notification(msg);

    m_seats[id]->setTaken(m_dataBase->readData(id));
}

void AirPlaneWidget::drawAirPlane()
{
    for (int column = 0; column < 4; column++) {
        for (int row = 0; row < 10; row++) {

            Seat *seat = new Seat(this);
            m_scene->addItem(seat);

            QString id(rowAndColumnToId(row,column));
            m_seats[id] = seat;
            seat->setPos(-40 + column * 22, -80 + row * 22);
            seat->setTaken(m_dataBase->readData(id));

            connect(seat, SIGNAL(clicked(Seat*)),
                    this, SLOT(seatChanged(Seat*)));
        }
    }
}

QString AirPlaneWidget::idOfSeat(const Seat *seat) const
{
    QMap<QString, Seat*>::const_iterator it;
    for (it = m_seats.begin(); it != m_seats.end(); it++) {
        if (it.value() == seat)
            return it.key();
    }

    // impossible
    return QString("Seat not found");
}

QString AirPlaneWidget::rowAndColumnToId(const int row, const int column) const
{
    // ASCII code of 'a' is 97
    QChar c(column+97);

    // the numbers of rows shall start from 1 not from 0
    return QString("%1%2").arg(row+1).arg(c);
}
