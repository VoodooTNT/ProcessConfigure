#pragma once

#include "CustomGraphicsItem.h"
#include "CustomArrow.h"

#include <QGraphicsScene>
#include <QMenu>
#include <QAction>

enum ToolMode 
{
	DEFAULT_MODE,
	LINE_MODE
};

class CustomGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	CustomGraphicsScene(QObject *parent = nullptr);
	~CustomGraphicsScene();

private:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
	QAction *addItemAction;
	QPointF rightMousePos;
	ToolMode currentMode = ToolMode::DEFAULT_MODE;
	QGraphicsLineItem *line = nullptr;
	std::map<CustomGraphicsItem*, CustomGraphicsItem*> itemAssociation;
	std::map<CustomGraphicsItem*, CustomGraphicsItem*> _itemAssociation;//记录一个逆序，方便删除时查找

public:
	void setToolMode(ToolMode mode);
	void flashAssociationMap(std::map<CustomGraphicsItem*, CustomGraphicsItem*> &destMap);

private:
	void removeSelectItem();

public slots:
	void slotAddItemAction();

signals:
	void sigCurrentDoubleClickItem(QGraphicsItem *item);
};

