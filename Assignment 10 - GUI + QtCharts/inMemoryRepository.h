#pragma once
#include <vector>
#include "evidence.h"
#include "evidenceRepository.h"

class InMemoryRepository : public EvidenceRepository
{
private:
	std::vector<Evidence> evidenceDatabase;
	std::vector<Evidence>::iterator iteratorInMemory;

public:
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



	// return an iterator for the repository
	void iterator() override;

	Evidence getCurrent() override;

	void next() override;

};