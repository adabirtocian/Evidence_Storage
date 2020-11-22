#pragma once
#include <vector>
#include "evidence.h"

class EvidenceRepository
{
public:
	// add a new element
	virtual void addElement(const Evidence& newElement) = 0;

	// update an existing element
	virtual void updateElement(int position, const Evidence& newElement) = 0;

	// remove an existing element
	virtual void removeElement(std::string id, int position) = 0;

	// return the list of all evidences storred in the database, as a dynamic vector
	virtual std::vector<Evidence> getEvidenceDatabase() = 0;

	// check if the evidence having the given id was alredy added; return -1 if not
	virtual int isInDatabase(std::string id) = 0;

	// return the evidence having the given id; return empty evidence if not found
	virtual Evidence getEvidenceById(std::string id) = 0;

	// ================= Iterator ==============================

	// return an iterator for the repository
	virtual void iterator() = 0;

	virtual Evidence getCurrent() = 0;

	virtual void next() = 0;

};

