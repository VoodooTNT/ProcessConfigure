#pragma once

#include <QGraphicsLineItem>

#include "CustomGraphicsItem.h"


//²Î¿¼Qt·¶Àý£ºdiagramscene
class CustomArrow : public QGraphicsLineItem
{
public:
	enum { Type = UserType + 4 };

	CustomArrow(CustomGraphicsItem *startItem, CustomGraphicsItem *endItem,
		QGraphicsItem *parent = 0);

	int type() const override { return Type; }
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void setColor(const QColor &color) { myColor = color; }
	CustomGraphicsItem *startItem() const { return myStartItem; }
	CustomGraphicsItem *endItem() const { return myEndItem; }

	void updatePosition();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
	CustomGraphicsItem *myStartItem;
	CustomGraphicsItem *myEndItem;
	QColor myColor;
	QPolygonF arrowHead;
};

