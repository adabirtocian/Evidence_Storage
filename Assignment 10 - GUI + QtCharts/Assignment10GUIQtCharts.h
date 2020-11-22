#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Assignment10GUIQtCharts.h"

class Assignment10GUIQtCharts : public QMainWindow
{
	Q_OBJECT

public:
	Assignment10GUIQtCharts(QWidget *parent = Q_NULLPTR);

private:
	Ui::Assignment10GUIQtChartsClass ui;
};
