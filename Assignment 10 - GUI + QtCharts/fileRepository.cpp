#include "fileRepository.h"
#include "exceptions.h"
#include <fstream>
#include <algorithm>
using namespace std;


FileRepository::FileRepository(std::string fileName)
{
	this->fileName = fileName;
}

void FileRepository::addElement(const Evidence& newElement)
{
	ofstream file(this->fileName, ios::app);
	if (!file.is_open())
		throw RepositoryException("The file could not be opened!\n");
	file << newElement;
	file.close();
}

void FileRepository::updateElement(int position, const Evidence& newElement)
{
	vector<Evidence> buffer = this->readFromFile();
	vector<Evidence> dataToWrite;

	for (auto evidence : buffer)
		if (evidence.getId() == newElement.getId())	dataToWrite.push_back(newElement);
		else dataToWrite.push_back(evidence);

	this->writeToFile(dataToWrite);
}

void FileRepository::removeElement(std::string id, int position)
{
	vector<Evidence> buffer = this->readFromFile();
	vector<Evidence> dataToWrite;

	for (auto evidence : buffer)
		if (evidence.getId() != id) dataToWrite.push_back(evidence);

	this->writeToFile(dataToWrite);
}


std::vector<Evidence> FileRepository::getEvidenceDatabase()
{
	vector<Evidence> buffer = this->readFromFile();
	return buffer;
}

int FileRepository::isInDatabase(std::string id)
{
	vector<Evidence> buffer = this->readFromFile();
	vector<Evidence>::iterator iterator = find_if(buffer.begin(), buffer.end(), [id](Evidence evidence) { return evidence.getId() == id; });

	if (iterator != buffer.end()) return 1;
	return -1;
}

Evidence FileRepository::getEvidenceById(std::string id)
{
	vector<Evidence> buffer = this->readFromFile();
	vector<Evidence>::iterator iterator = find_if(buffer.begin(), buffer.end(), [id](Evidence evidence) { return evidence.getId() == id; });

	if (iterator != buffer.end()) return *iterator;
	return Evidence{};
}

std::vector<Evidence> FileRepository::readFromFile()
{
	ifstream file(this->fileName);
	if (!file.is_open())
		throw RepositoryException("The file could not be opened!\n");

	vector<Evidence> buffer;
	Evidence currentEvidence{};

	while (file >> currentEvidence)
		buffer.push_back(currentEvidence);

	file.close();

	return buffer;
}

void FileRepository::writeToFile(std::vector<Evidence> dataToWrite)
{
	ofstream file(this->fileName);
	if (!file.is_open())
		throw RepositoryException("The file could not be opened!\n");

	for (auto evidence : dataToWrite)
		file << evidence;

	file.close();
}

// ================= Iterator ==============================

void FileRepository::iterator()
{
	this->positionIteratorInFile = 1;
}

Evidence FileRepository::getCurrent()
{
	vector<Evidence> buffer = this->readFromFile();
	int currentPosition = 1;

	for (auto& evidence : buffer)
	{
		if (currentPosition == this->positionIteratorInFile) return evidence;
		currentPosition++;
	}
	return Evidence{};
}

void FileRepository::next()
{
	vector<Evidence> buffer = this->readFromFile();

	if (this->positionIteratorInFile == buffer.size()) this->iterator();
	else ++this->positionIteratorInFile;
}
