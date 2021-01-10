#include "CustomGraphicsScene.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QKeyEvent>

CustomGraphicsScene::CustomGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
	addItemAction = new QAction(QStringLiteral("添加对象"));
	connect(addItemAction, &QAction::triggered, this, &CustomGraphicsScene::slotAddItemAction);
}

CustomGraphicsScene::~CustomGraphicsScene() 
{

}

void CustomGraphicsScene::keyPressEvent(QKeyEvent *event) 
{
	QGraphicsScene::keyPressEvent(event);
}

void CustomGraphicsScene::keyReleaseEvent(QKeyEvent *event) 
{
	if (event->key() == Qt::Key_Delete)
	{
		removeSelectItem();
	}
	QGraphicsScene::keyReleaseEvent(event);
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) 
{
	if (event->button() != Qt::LeftButton)
		return;

	if (currentMode == ToolMode::LINE_MODE)
	{
		line = new QGraphicsLineItem(QLineF(event->scenePos(),
			event->scenePos()));
		line->setPen(QPen(QColor(0,0,0), 2));
		addItem(line);
	}

	QGraphicsScene::mousePressEvent(event);
}

void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);
	if (line != nullptr && currentMode == ToolMode::LINE_MODE) {
		QList<QGraphicsItem *> startItems = items(line->line().p1());
		if (startItems.count() && startItems.first() == line)
			startItems.removeFirst();
		QList<QGraphicsItem *> endItems = items(line->line().p2());
		if (endItems.count() && endItems.first() == line)
			endItems.removeFirst();

		removeItem(line);
		delete line;
	
		if (startItems.count() > 0 && endItems.count() > 0 &&
			startItems.first()->type() == CustomGraphicsItem::Type &&
			endItems.first()->type() == CustomGraphicsItem::Type &&
			startItems.first() != endItems.first()) {
			CustomGraphicsItem *startItem = qgraphicsitem_cast<CustomGraphicsItem *>(startItems.first());
			CustomGraphicsItem *endItem = qgraphicsitem_cast<CustomGraphicsItem *>(endItems.first());
			CustomArrow *arrow = new CustomArrow(startItem, endItem);
			arrow->setColor(QColor(0, 0, 0));
			startItem->addArrow(arrow);
			endItem->addArrow(arrow);
			arrow->setZValue(-1000.0);
			addItem(arrow);
			arrow->updatePosition();

			itemAssociation[startItem] = endItem;
			_itemAssociation[endItem] = startItem;
		}
	}
	else if (currentMode == ToolMode::DEFAULT_MODE)
	{
		if (!event->isAccepted())
		{
			if (event->button() == Qt::LeftButton)
			{
				rightMousePos = event->scenePos();
				slotAddItemAction();
			}
		}
	}

	line = nullptr;
}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) 
{
	if (currentMode == ToolMode::LINE_MODE && line != nullptr) {
		QLineF newLine(line->line().p1(), event->scenePos());
		line->setLine(newLine);
	}
	else if (currentMode == ToolMode::DEFAULT_MODE) {
		QGraphicsScene::mouseMoveEvent(event);
	}
}

void CustomGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) 
{
	rightMousePos = event->scenePos();

	QMenu *menu = new QMenu();
	menu->addAction(addItemAction);
	menu->exec(event->screenPos());
	delete menu;
}

void CustomGraphicsScene::slotAddItemAction()
{
	CustomGraphicsItem* item = new CustomGraphicsItem(rightMousePos.x(), rightMousePos.y(), 50, 50);
	item->setText("1");
	addItem(item);
	connect(item, SIGNAL(sigCurrentDoubleClickItem(QGraphicsItem*)), this, SIGNAL(sigCurrentDoubleClickItem(QGraphicsItem*)));
}
	
void CustomGraphicsScene::setToolMode(ToolMode mode) 
{
	currentMode = mode;
}

void CustomGraphicsScene::flashAssociationMap(std::map<CustomGraphicsItem*, CustomGraphicsItem*> &destMap)
{
	destMap.clear();
	destMap = itemAssociation;
}

void CustomGraphicsScene::removeSelectItem() 
{
	QList<QGraphicsItem *> selectedItems = this->selectedItems();
	for (QGraphicsItem *item : qAsConst(selectedItems)) {
		if (item->type() == CustomArrow::Type) {
			this->removeItem(item);
			CustomArrow *arrow = qgraphicsitem_cast<CustomArrow*>(item);
			arrow->startItem()->removeArrow(arrow);
			arrow->endItem()->removeArrow(arrow);

			//删除箭头之后清除itemAssociation关联项
			auto p = itemAssociation.find(arrow->startItem());
			itemAssociation.erase(p);
			auto q = _itemAssociation.find(arrow->endItem());
			_itemAssociation.erase(q);

			delete item;
		}
	}

	selectedItems = this->selectedItems();
	for (QGraphicsItem *item : qAsConst(selectedItems)) {
		if (item->type() == CustomGraphicsItem::Type) 
		{
			qgraphicsitem_cast<CustomGraphicsItem*>(item)->removeArrows();
			//删除箭头之后清除itemAssociation关联项
			auto p = itemAssociation.find(qgraphicsitem_cast<CustomGraphicsItem*>(item));
			if (p != itemAssociation.end())
			{
				auto s = _itemAssociation.find(p->second);
				if (s!=_itemAssociation.end())
				{
					_itemAssociation.erase(s);
				}
				auto t = _itemAssociation.find(qgraphicsitem_cast<CustomGraphicsItem*>(item));
				if (t!=_itemAssociation.end())
				{
					auto v = itemAssociation.find(t->second);
					if (v!=itemAssociation.end())
					{
						itemAssociation.erase(v);
					}
					_itemAssociation.erase(t);
				}
				itemAssociation.erase(p);
			}
		}
		this->removeItem(item);
		delete item;
	}

	/*while (!selectedItems().isEmpty())
	{
		removeItem(selectedItems().front());
	}*/
}