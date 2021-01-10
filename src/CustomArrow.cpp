#include "CustomArrow.h"

#include <qmath.h>
#include <QPen>
#include <QPainter>

CustomArrow::CustomArrow(CustomGraphicsItem *startItem, CustomGraphicsItem *endItem, QGraphicsItem *parent)
	: QGraphicsLineItem(parent)
{
	myStartItem = startItem;
	myEndItem = endItem;
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	myColor = Qt::black;
	setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF CustomArrow::boundingRect() const
{
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
		line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

QPainterPath CustomArrow::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(arrowHead);
	return path;
}

void CustomArrow::updatePosition()
{
	QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
	setLine(line);
}

void CustomArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
	QWidget *)
{
	if (myStartItem->collidesWithItem(myEndItem))
		return;

	QPen myPen = pen();
	myPen.setColor(myColor);
	qreal arrowSize = 20;
	painter->setPen(myPen);
	painter->setBrush(myColor);

	//不知道为什么pos()只能获得左上角坐标，并不像Qt范例diagramscene获得中心点坐标，所以只能计算中心点坐标
	QPointF startCenterPos = QPointF(myStartItem->pos().x() + myStartItem->rect().width() / 2, myStartItem->pos().y() + myStartItem->rect().height() / 2);
	QPointF endCenterPos = QPointF(myEndItem->pos().x() + myEndItem->rect().width() / 2, myEndItem->pos().y() + myEndItem->rect().height() / 2);

	QLineF centerLine(startCenterPos, endCenterPos);
	QRectF endPolygon = myEndItem->rect();
	std::vector<QPointF> rectPoints;
	rectPoints.push_back(endPolygon.topLeft());
	rectPoints.push_back(endPolygon.topRight());
	rectPoints.push_back(endPolygon.bottomRight());
	rectPoints.push_back(endPolygon.bottomLeft());
	rectPoints.push_back(endPolygon.topLeft());
	QPointF p1 = endPolygon.topLeft() + myEndItem->pos();
	QPointF p2;
	QPointF intersectPoint;
	QLineF polyLine;
	for (int i = 1; i < rectPoints.size(); ++i) {
		p2 = rectPoints[i] + myEndItem->pos();
		polyLine = QLineF(p1, p2);
		QLineF::IntersectType intersectType =
			polyLine.intersects(centerLine, &intersectPoint);
		if (intersectType == QLineF::BoundedIntersection)
			break;
		p1 = p2;
	}
	
	setLine(QLineF(intersectPoint, startCenterPos));

	double angle = std::atan2(-line().dy(), line().dx());

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
		cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
		cos(angle + M_PI - M_PI / 3) * arrowSize);

	arrowHead.clear();
	arrowHead << line().p1() << arrowP1 << arrowP2;

	painter->drawLine(line());
	painter->drawPolygon(arrowHead);
	if (isSelected()) {
		painter->setPen(QPen(myColor, 1, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0, -8.0);
		painter->drawLine(myLine);
	}
}