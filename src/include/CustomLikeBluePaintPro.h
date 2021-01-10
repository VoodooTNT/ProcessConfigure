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
	std::map<CustomGraphicsItem*, CustomGraphicsItem*>::iterator  findHead();//����·��ͷ�ڵ㣬������Ӧ�ö���һ��ͷ�ڵ��࣬Ȼ�󱣴���һ��List��ֱ�Ӷ�ȡ����ʱ����ôд
};
