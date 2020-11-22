#pragma once
#include <vector>
#include "evidence.h"
#include "evidenceRepository.h"
#include <fstream>

class FileRepository : public EvidenceRepository
{
private:
	std::string fileName;
	int positionIteratorInFile;

public:
	FileRepository(std::string fileName);

	// add a new element
	void addElement(const Evidence& newElement) override;

	// update an existing element
	void updateElement(int position, const Evidence& newElement) override;

	// remove an existing element
	void removeElement(std::string id, int position) override;

	// return the list of all evidences storred in the database, as a dynamic vector
	std::vector<Evidence> getEvidenceDatabase() override;

	// check if the evidence having the given id was alredy added; return -1 if not
	int isInDatabase(std::string id) override;

	// return the evidence having the given id; return empty evidence if not found
	Evidence getEvidenceById(std::string id) override;

	// read all the data from the file and return it in a vector
	std::vector<Evidence> readFromFile();

	// write the given vector containing data to the file
	void writeToFile(std::vector<Evidence> dataToWrite);

	// ================= Iterator ==============================

	// return an iterator for the repository
	void iterator() override;

	// return the current evidence from the iterator
	Evidence getCurrent() override;

	// move to the next evidence in file
	void next() override;

};

