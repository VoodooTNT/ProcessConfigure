#pragma once
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QObject>

class CustomArrow;

class CustomGraphicsItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	enum { Type = UserType + 2 };

	CustomGraphicsItem(QGraphicsItem *parent = nullptr);
	CustomGraphicsItem(QRectF rect, QGraphicsItem *parent = nullptr);
	CustomGraphicsItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
	~CustomGraphicsItem();

	int type() const override { return Type; }
	void setText(QString text);
	QString text();
	void removeArrow(CustomArrow *arrow);
	void removeArrows();
	void addArrow(CustomArrow *arrow);

private:
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	void initItem(qreal x, qreal y, qreal w, qreal h);
	void setItemTip(QString text);

private:
	QGraphicsTextItem *data = nullptr;
	QList<CustomArrow *> arrowsList;

signals:
	void sigCurrentDoubleClickItem(QGraphicsItem *item);
};

