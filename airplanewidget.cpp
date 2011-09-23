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

    // virsli
    Seat *seat = new Seat(this);
    m_scene->addItem(seat);
    seat->setPos(0,0);

    Seat *seat1 = new Seat(this);
    m_scene->addItem(seat1);
    seat1->setPos(40,0);

    Seat *seat2 = new Seat(this);
    m_scene->addItem(seat2);
    seat2->setPos(0,40);


}

AirPlaneWidget::~AirPlaneWidget()
{

}

void AirPlaneWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    painter->fillRect(m_scene->sceneRect(), AirPlaneWidget::m_paperColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(m_scene->sceneRect());
}
