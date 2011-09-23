#include "airplanewidget.h"

const QColor AirPlaneWidget::m_paperColor(255,255,153);

AirPlaneWidget::AirPlaneWidget(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this))
{
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(-200, -200, 400, 400);
    setScene(m_scene);

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(500, 500);

    for (int coloumn = 0; coloumn < 4; coloumn++) {
        for (int row = 0; row < 10; row++) {

            Seat *seat = new Seat(this);
            m_scene->addItem(seat);
            m_seats.append(seat);
            seat->setPos(-40 + coloumn * 22, -80 + row * 22);

            connect(seat, SIGNAL(clicked()), this, SLOT(changed()));
        }
    }

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

void AirPlaneWidget::changed()
{
    /// @todo pass the seat
    qDebug("one seat is changed");
}
