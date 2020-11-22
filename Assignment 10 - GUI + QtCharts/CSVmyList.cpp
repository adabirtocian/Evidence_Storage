#include "CSVmyList.h"
#include "exceptions.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>
using namespace std;

void CSVmyList::addEvidence(const Evidence& evidence)
{
	ofstream file(this->fileName, ios::app);
	if (!file.is_open())
		throw MyListException("The file could not be opened!\n");
	file << evidence;
	file.close();
}

void CSVmyList::displayUserEvidences()
{
	ShellExecuteA(NULL, NULL, "notepad.exe", this->fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
}
