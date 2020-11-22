#pragma once
#include <qwidget.h>
#include "service.h"
#include <qpushbutton.h>
#include <qlineedit.h>

class MainGUI : public QWidget
{
private:
	Service& service;

	QPushButton* adminButton;
	QPushButton* userButton;

	QWidget* adminGui;
	QWidget* userGui;
public:
	MainGUI(Service& service);

private:
	void initializeMainGUI();
	void connectSignalsAndSlots();
	void showAdminGUI();
	void showUserGUI();

};

