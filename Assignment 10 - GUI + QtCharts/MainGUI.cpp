#include "MainGUI.h"
#include <qformlayout.h>
#include <qlineedit.h>
#include "AdminGUI.h"

MainGUI::MainGUI(Service& service): service{service}
{
	this->initializeMainGUI();
	this->connectSignalsAndSlots();
}

void MainGUI::initializeMainGUI()
{
	this->setWindowTitle("Home window");

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QVBoxLayout* buttonsLayout = new QVBoxLayout();

	this->adminButton = new QPushButton("Admin mode");
	this->userButton = new QPushButton("User mode");
	buttonsLayout->addWidget(this->adminButton);
	buttonsLayout->addWidget(this->userButton);

	mainLayout->addLayout(buttonsLayout);
}

void MainGUI::connectSignalsAndSlots()
{
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &MainGUI::showAdminGUI);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &MainGUI::showUserGUI);
}

void MainGUI::showAdminGUI()
{
	this->adminGui = new AdminGUI{ this->service };
	this->adminGui->show();
}

void MainGUI::showUserGUI()
{

}
