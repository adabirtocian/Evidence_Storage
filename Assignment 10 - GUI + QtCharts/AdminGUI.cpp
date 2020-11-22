#include "AdminGUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <vector>
#include <Qmessagebox.h>
#include "exceptions.h"
#include "DataRepresentation.h"
using namespace std;

AdminGUI::AdminGUI(Service& service) : service{ service }
{
	this->initializeAdminGUI();
	this->populateList();
	this->connectSignalsAndSlots();
}

void AdminGUI::initializeAdminGUI()
{
	this->evidencesListWidget = new QListWidget{};
	this->idLineEdit = new QLineEdit{};
	this->measurementLineEdit = new QLineEdit{};
	this->imageClarityLevelLineEdit = new QLineEdit{};;
	this->quantityLineEdit = new QLineEdit{};
	this->photoLinkLineEdit = new QLineEdit{};

	this->addButton = new QPushButton{"Add"};
	this->deleteButton = new QPushButton{"Delete"};
	this->updateButton = new QPushButton{"Update"};
	this->graphics = new QPushButton{ "Graphics" };
	this->exitButton = new QPushButton{ "Exit" };

	QVBoxLayout* mainLayout = new QVBoxLayout{ this };
	mainLayout->addWidget(this->evidencesListWidget);

	QFormLayout* evidencesDetailsLayout = new QFormLayout{};
	evidencesDetailsLayout->addRow("Id", this->idLineEdit);
	evidencesDetailsLayout->addRow("Measurement", this->measurementLineEdit);
	evidencesDetailsLayout->addRow("Image clarity level", this->imageClarityLevelLineEdit);
	evidencesDetailsLayout->addRow("Quantity", this->quantityLineEdit);
	evidencesDetailsLayout->addRow("Photo link", this->photoLinkLineEdit);
	
	mainLayout->addLayout(evidencesDetailsLayout);

	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 1);
	buttonsLayout->addWidget(this->updateButton, 0, 2);
	buttonsLayout->addWidget(this->graphics, 1, 1);
	buttonsLayout->addWidget(this->exitButton, 1, 2);

	mainLayout->addLayout(buttonsLayout);
}

void AdminGUI::populateList()
{
	this->evidencesListWidget->clear();
	vector<Evidence> allEvidences = this->service.getAllEvidence();

	for (auto evidence : allEvidences)
		this->evidencesListWidget->addItem(QString::fromStdString(evidence.getId() + " - " + 
			evidence.getMeasurement() + " - " + to_string(evidence.getImageClarityLevel()) + " - " + 
			to_string(evidence.getQuantity()) + " - " + evidence.getPhotoLink()));
}

void AdminGUI::connectSignalsAndSlots()
{
	QObject::connect(this->evidencesListWidget, &QListWidget::itemSelectionChanged, [this]() {
			int selectedIndex = this->getSelectedIndex();

			if (selectedIndex < 0)
				return;
			Evidence evidence = this->service.getAllEvidence()[selectedIndex];
			this->idLineEdit->setText(QString::fromStdString(evidence.getId()));
			this->measurementLineEdit->setText(QString::fromStdString(evidence.getMeasurement()));
			this->imageClarityLevelLineEdit->setText(QString::fromStdString(to_string(evidence.getImageClarityLevel())));
			this->quantityLineEdit->setText(QString::fromStdString(to_string(evidence.getQuantity())));
			this->photoLinkLineEdit->setText(QString::fromStdString(evidence.getPhotoLink()));
		});

	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addEvidence);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteEvidence);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateEvidence);
	QObject::connect(this->graphics, &QPushButton::clicked, this, &AdminGUI::showGraphics);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, [this]() {exit(1); });
}

int AdminGUI::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->evidencesListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->idLineEdit->clear();
		this->measurementLineEdit->clear();
		this->imageClarityLevelLineEdit->clear();
		this->quantityLineEdit->clear();
		this->photoLinkLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void AdminGUI::addEvidence()
{
	string id = this->idLineEdit->text().toStdString();
	string measurement = this->measurementLineEdit->text().toStdString();
	double imageClarityLevel = this->imageClarityLevelLineEdit->text().toDouble();
	double quantity = this->quantityLineEdit->text().toDouble();
	string photoLink = this->photoLinkLineEdit->text().toStdString();

	try {

		this->service.addEvidence(id, measurement, imageClarityLevel, quantity, photoLink);
		this->populateList();
		int lastAddedEvidence = this->service.getAllEvidence().size() - 1;
		this->evidencesListWidget->setCurrentRow(lastAddedEvidence);
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
}

void AdminGUI::deleteEvidence()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No selected evidence !");
		return;
	}

	Evidence evidence = this->service.getAllEvidence()[selectedIndex];

	try {
		
		this->service.removeEvidence(evidence.getId());
		this->populateList();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
}

void AdminGUI::updateEvidence()
{
	string id = this->idLineEdit->text().toStdString();
	string measurement = this->measurementLineEdit->text().toStdString();
	double imageClarityLevel = this->imageClarityLevelLineEdit->text().toDouble();
	double quantity = this->quantityLineEdit->text().toDouble();
	string photoLink = this->photoLinkLineEdit->text().toStdString();

	try {
		this->service.updateEvidence(id, measurement, imageClarityLevel, quantity, photoLink);
		this->populateList();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
}

void AdminGUI::showGraphics()
{
	this->graphicsWidget = new DataRepresentation{ this->service };
	this->graphicsWidget->show();
}
