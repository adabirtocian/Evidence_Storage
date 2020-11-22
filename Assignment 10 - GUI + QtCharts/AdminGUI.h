#pragma once
#include <qwidget.h>
#include "service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class AdminGUI : public QWidget
{
private:
	Service& service;
	QListWidget* evidencesListWidget;
	QLineEdit* idLineEdit, * measurementLineEdit, * imageClarityLevelLineEdit, * quantityLineEdit, * photoLinkLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton, *graphics, *exitButton;
	QWidget* graphicsWidget;

public:
	AdminGUI(Service& service);

private:
	void initializeAdminGUI();
	void populateList();
	void connectSignalsAndSlots();

	int getSelectedIndex() const;
	void addEvidence();
	void deleteEvidence();
	void updateEvidence();

	void showGraphics();
};

