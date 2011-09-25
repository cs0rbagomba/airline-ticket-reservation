#include "airplanewidget.h"

const QColor AirPlaneWidget::m_paperColor(255,255,153);

AirPlaneWidget::AirPlaneWidget(QWidget *parent,
                               DataBase *db) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_dataBase(db)
{
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(-100, -350, 300, 550);
    setScene(m_scene);

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(400, 600);

    drawAirPlane();

    // signal from DB - data has been modified from outside
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

    QString msg = QString("Seat %1 has been ").arg(id);
    msg.append(seat->taken() ? "reserved" : "cancelled");
    emit notification(msg);

    if (!m_dataBase->writeData(id, seat->taken())) {
        // Couldn't reserve seat, reverse state
        seat->setTaken(!(seat->taken()));
    }
}

// signal from DB - data has been modified from outside
void AirPlaneWidget::seatChanged(QString id)
{
    QString msg = QString("Seat %1 has been changed - from DataBase").arg(id);
    emit notification(msg);

    bool taken;
    if (!(m_dataBase->readData(id,taken))) {
        // Database read error, leaving the seat as it is
    } else {
        m_seats[id]->setTaken(taken);
    }
}

void AirPlaneWidget::drawAirPlane()
{
    // print help text
    QGraphicsTextItem *helpText = new QGraphicsTextItem(0);
    m_scene->addItem(helpText);
    helpText->setDefaultTextColor(Qt::black);
    helpText->setPlainText("'Ctrl' + click to cancel reservation");
    helpText->setPos(-80, -330);

    for (int column = 0; column < 6; column++) {

        // print column letters: a,b,c d,e,f
        QGraphicsTextItem *columnLetter = new QGraphicsTextItem(0);
        m_scene->addItem(columnLetter);
        columnLetter->setDefaultTextColor(Qt::black);
        columnLetter->setPlainText(QString(QChar(column+97)));
        qreal x(-16 + column * 23);
        if (column > 2 ) {
            x += 28;
        }
        columnLetter->setPos(x, -280);

        for (int row = 0; row < 20; row++) {

            // print row numbers
            QGraphicsTextItem *rowNumber = new QGraphicsTextItem(0);
            m_scene->addItem(rowNumber);
            rowNumber->setDefaultTextColor(Qt::black);
            rowNumber->setPlainText(QString(" %1").arg(row+1,2));
            rowNumber->setPos(-50, -257 + row * 22);

            // draw seats
            Seat *seat = new Seat(this);
            m_scene->addItem(seat);

            QString id(QString("%1%2").arg(row+1).arg(QChar(97+column)));
            m_seats[id] = seat;

            qreal x(-10 + column * 22);
            if (column > 2 ) {
                x += 30;
            }
            qreal y(-250 + row * 22);
            seat->setPos(x,y);

            // read state from DB
            bool taken;
            if (!(m_dataBase->readData(id,taken))) {
                // Database read error
                m_seats[id]->setTaken(false);
            } else {
                m_seats[id]->setTaken(taken);
            }

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
