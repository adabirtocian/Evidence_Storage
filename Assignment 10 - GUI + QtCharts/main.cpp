#include "Assignment10GUIQtCharts.h"
#include <QtWidgets/QApplication>
#include "fileRepository.h" 
#include "service.h"
#include "AdminGUI.h"
#include <qmessagebox.h>
#include <qlayout.h>
#include <QLabel>
#include <qlineedit.h>
#include <qformlayout.h>
#include "HTMLmyList.h"
#include "MainGUI.h"
#include "DataRepresentation.h"
using namespace std;

string determineMyListType(string fileName)
{
	std::size_t positionFound = fileName.rfind(".");
	if (positionFound == std::string::npos)
		throw exception("Invalid file name\n");

	return fileName.substr(positionFound, std::string::npos);
}

int main(int argc, char *argv[])
{
	QApplication mainApplication(argc, argv);

	QMessageBox messageBox;
	messageBox.setText(QT_TR_NOOP("What type of file would you like to store your adoption list?"));
	QAbstractButton* CSVChoiceButton = messageBox.addButton(QT_TR_NOOP("CSV"), QMessageBox::YesRole);
	messageBox.addButton(QT_TR_NOOP("HTML"), QMessageBox::NoRole);
	messageBox.exec();

	MyListEvidences* myListRepository = nullptr;
	if (messageBox.clickedButton() == CSVChoiceButton)
		myListRepository = new CSVmyList{ "mylist.txt" };
	else myListRepository = new HTMLmyList{ "mylist.html" };
	FileRepository repository{ "evidences.txt" };
	Service service{ repository, *myListRepository };
	MainGUI gui{ service };
	gui.show();

	return mainApplication.exec();
}
