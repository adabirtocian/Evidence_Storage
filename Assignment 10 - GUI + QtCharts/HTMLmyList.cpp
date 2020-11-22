#include "HTMLmyList.h"
#include "exceptions.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>
using namespace std;


void HTMLmyList::addEvidence(const Evidence& evidence)
{
	this->savedEvidences.push_back(evidence);

	ofstream openedFile(this->fileName);
	if(!openedFile.is_open())
		throw MyListException("The file could not be opened!\n");

	openedFile << "<!DOCTYPE html> \n" << "<html> \n";
	openedFile << "<head>\n" << " <title> My Evidences </title> \n" << "</head>\n";
	openedFile << "<body>\n" << "<table border=\"1\" bgcolor=\"#82E0AA\" align=\"center\">\n";
	openedFile << "<tr>\n <td>Id</td>\n" << "<td>Measurement</td>\n" << " <td>ImageClarityLevel</td>\n" << "<td>Quantity</td>\n" << "<td>PhotoLink</td>\n </tr>\n ";

	for (auto& evidence : this->savedEvidences)
	{
		openedFile << "<tr>\n";
		openedFile << "<td>" << evidence.getId() << "</td> \n";
		openedFile << "<td>" << evidence.getMeasurement() << "</td> \n";
		openedFile << "<td>" << evidence.getImageClarityLevel() << "</td> \n";
		openedFile << "<td>" << evidence.getQuantity() << "</td> \n";
		openedFile << "<td> <a href=" << evidence.getPhotoLink() << ">Link </a> </td> \n";
	}
	
	openedFile << "</table>\n";
	openedFile.close();
}

void HTMLmyList::displayUserEvidences()
{
	string HTMLfile = '"' + this->fileName + '"';
	ShellExecuteA(NULL, NULL, "chrome.exe", HTMLfile.c_str(), NULL, SW_SHOWMAXIMIZED);
}