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

    /// @todo Do it in a loop
    Seat *seat = new Seat(this);
    m_scene->addItem(seat);
    seat->setPos(-20, -60);

    Seat *seat1 = new Seat(this, true);
    m_scene->addItem(seat1);
    seat1->setPos(-20, -20);

    Seat *seat2 = new Seat(this, true);
    m_scene->addItem(seat2);
    seat2->setPos(-20, 20);

    Seat *seat3 = new Seat(this);
    m_scene->addItem(seat3);
    seat3->setPos(-20, 60);

    Seat *seat4 = new Seat(this, true);
    m_scene->addItem(seat4);
    seat4->setPos(20, -60);

    Seat *seat5 = new Seat(this);
    m_scene->addItem(seat5);
    seat5->setPos(20, -20);

    Seat *seat6 = new Seat(this);
    m_scene->addItem(seat6);
    seat6->setPos(20, 20);

    Seat *seat7 = new Seat(this, true);
    m_scene->addItem(seat7);
    seat7->setPos(20, 60);
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
