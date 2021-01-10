#pragma once

#include <QtWidgets/QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDialog>

#include "ui_CustomLikeBluePaintPro.h"
#include "CustomGraphicsScene.h"
#include "CustomGraphicsItem.h"
#include "buildCalculate.h"

class CustomLikeBluePaintPro : public QWidget
{
	Q_OBJECT

public:
	CustomLikeBluePaintPro(QWidget *parent = Q_NULLPTR);

private:
	Ui::CustomLikeBluePaintProClass ui;

	buildCalculate calculateObj;
	std::map<CustomGraphicsItem*, CustomGraphicsItem*> itemAssociation;

public slots:
	void slotCalculate();

private:
	QDialog *alterItemTextDia;
	QLineEdit *lineEdit;
	QPushButton *pushButton;
	CustomGraphicsItem *currentDoubleClickItem;

private:
	std::map<CustomGraphicsItem*, CustomGraphicsItem*>::iterator  findHead();//查找路径头节点，理论上应该定义一个头节点类，然后保存在一个List中直接读取，暂时先这么写
};
