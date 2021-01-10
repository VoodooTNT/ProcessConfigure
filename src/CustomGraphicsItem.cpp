#include "CustomGraphicsItem.h"
#include "CustomArrow.h"

CustomGraphicsItem::CustomGraphicsItem(QGraphicsItem *parent) : QGraphicsRectItem(parent) 
{

}

CustomGraphicsItem::CustomGraphicsItem(QRectF rect, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	initItem(rect.x(), rect.y(), rect.width(), rect.height());
}

CustomGraphicsItem::CustomGraphicsItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	initItem(x, y, w, h);
}

CustomGraphicsItem::~CustomGraphicsItem()
{

}

void CustomGraphicsItem::initItem(qreal x, qreal y, qreal w, qreal h)
{
	setRect(0, 0, w, h);
	setPos(x - w / 2, y - h / 2);//不知道为什么这里设置了Pos，调用pos()获得的坐标还是左上角
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
	
	data = new QGraphicsTextItem(this);
	data->setTextWidth(w);
}

void CustomGraphicsItem::setText(QString text) 
{
	if (data != nullptr) 
	{
		data->setPlainText(text);
	}
}

QString CustomGraphicsItem::text() 
{
	return data->toPlainText();
}

void CustomGraphicsItem::setItemTip(QString text) 
{
	setToolTip(text);
}

void CustomGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	emit sigCurrentDoubleClickItem(this);
}

void CustomGraphicsItem::removeArrow(CustomArrow *arrow)
{
	int index = arrowsList.indexOf(arrow);

	if (index != -1)
		arrowsList.removeAt(index);
}

void CustomGraphicsItem::removeArrows()
{
	for (CustomArrow *arrow : qAsConst(arrowsList)) {
		arrow->startItem()->removeArrow(arrow);
		arrow->endItem()->removeArrow(arrow);
		this->scene()->removeItem(arrow);
		delete arrow;
	}
}

void CustomGraphicsItem::addArrow(CustomArrow *arrow)
{
	arrowsList.append(arrow);
}