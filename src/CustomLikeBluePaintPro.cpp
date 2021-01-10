#include "CustomLikeBluePaintPro.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QColor>
#include <QToolButton>
#include <QPushButton>
#include <QApplication>
//#include <QDesktopWidget>
#include <QLineEdit>
#include <QPushButton>

CustomLikeBluePaintPro::CustomLikeBluePaintPro(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	/*QGraphicsScene *pScene = new QGraphicsScene();
	pScene->setSceneRect(0, 0, ui.graphicsView->width() - 2, ui.graphicsView->height() - 2);
	ui.graphicsView->setScene(pScene);

	QGraphicsRectItem *rectItem = new QGraphicsRectItem();
	rectItem->setRect(0, 0, 50, 50);
	rectItem->setPos(100,100);
	rectItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
	rectItem->setToolTip("aaaaaa");

	QGraphicsTextItem *text = new QGraphicsTextItem(rectItem);
	text->setPlainText("AAAAAAAAAA");
	text->setTextWidth(50);

	QRectF rect = text->boundingRect();
	text->setDefaultTextColor(QColor(0, 0, 0));
	text->setPos(QPointF(0, 0));

	QString data = text->toPlainText();

	QPen pen = rectItem->pen();
	pen.setWidth(2);
	pen.setColor(QColor(111, 111, 111));

	rectItem->setPen(pen);
	rectItem->setBrush(QColor(111, 111, 111, 100));
	pScene->addItem(rectItem);*/

	CustomGraphicsScene *pScene = new CustomGraphicsScene();
	pScene->setSceneRect(0, 0, ui.graphicsView->width() - 2, ui.graphicsView->height() - 2);
	ui.graphicsView->setScene(pScene);

	ui.lineToolButton->setCheckable(true);
	connect(ui.lineToolButton, &QToolButton::toggled, this, [=] (bool)
	{
		if (ui.lineToolButton->isChecked())
		{
			pScene->setToolMode(ToolMode::LINE_MODE);
		}
		else 
		{
			pScene->setToolMode(ToolMode::DEFAULT_MODE);
		}
	});

	connect(ui.flashButton, &QPushButton::clicked, this, [=] 
	{
		pScene->flashAssociationMap(itemAssociation);
	});

	connect(ui.calculateButton, &QPushButton::clicked, this, &CustomLikeBluePaintPro::slotCalculate);

	alterItemTextDia = new QDialog();
	alterItemTextDia->setGeometry(/*QApplication::desktop()->screen()->width()*/1920 / 2 - 125, /*QApplication::desktop()->screen()->height()*/1080 / 2 - 30, 250, 40);
	alterItemTextDia->setWindowFlags(Qt::WindowCloseButtonHint);
	lineEdit = new QLineEdit(alterItemTextDia);
	lineEdit->setGeometry(5, 5, 145, 30);
	pushButton = new QPushButton(alterItemTextDia);
	pushButton->setGeometry(155, 5, 90, 30);
	pushButton->setText(QStringLiteral("修改"));

	connect(pScene, &CustomGraphicsScene::sigCurrentDoubleClickItem, this, [=] (QGraphicsItem* item)
	{
		currentDoubleClickItem = qgraphicsitem_cast<CustomGraphicsItem *>(item);
		lineEdit -> setFocus();
		alterItemTextDia->show();
	});
	connect(pushButton, &QPushButton::clicked, this, [=]
	{
		if (lineEdit->text() != "") 
		{
			currentDoubleClickItem->setText(lineEdit->text());
			lineEdit->clear();
		}
		alterItemTextDia->close();
	});
}

void CustomLikeBluePaintPro::slotCalculate()
{
	int value = ui.inputEdit->text().toInt();

	//查找路径头节点
	std::map<CustomGraphicsItem*, CustomGraphicsItem*>::iterator p = findHead();
	if (p == itemAssociation.end())
	{
		return;
	}

	while (p != itemAssociation.end())
	{
		std::string sign = p->first->text().toStdString();
		char temp = sign[0];
		value = calculateObj.startCalculate(value, temp);
		std::map<CustomGraphicsItem*, CustomGraphicsItem*>::iterator temp_iter = p;
		p = itemAssociation.find(p->second);
		//当是最后一组关联的时候，查询second就到了map的end了，但是second这一项的处理没有执行
		//这里不知道更好的写法，暂时这么写
		if (p == itemAssociation.end())
		{
			std::string sign = temp_iter->second->text().toStdString();
			char temp = sign[0];
			value = calculateObj.startCalculate(value, temp);
		}
	}
	
	ui.outputEdit->setText(QString::number(value));
}

std::map<CustomGraphicsItem*, CustomGraphicsItem*>::iterator  CustomLikeBluePaintPro::findHead()
{
	std::map<CustomGraphicsItem*, CustomGraphicsItem*>::iterator it = itemAssociation.begin();
	std::map<CustomGraphicsItem*, CustomGraphicsItem*>::iterator temp = itemAssociation.begin();
	while (it!=itemAssociation.end())
	{
		while (temp != itemAssociation.end())
		{
			if (temp->second == it->first)
			{
				it++;
				break;
			}

			temp++;

			if (temp == itemAssociation.end())
			{
				return it;
			}
		}
	}
	return it;
}