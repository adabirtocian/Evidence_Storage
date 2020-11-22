#include "service.h"
#include "evidenceValidator.h"
#include "exceptions.h"
#include <assert.h>
using namespace std;

// ================ REPOSITORY ==================

void Service::addEvidence(const std::string& id, const std::string& measurement, double imageClarityLevel, double quantity, const std::string& photoLink)
{
	Evidence evidence{ id, measurement, imageClarityLevel, quantity, photoLink };
	EvidenceValidator validator{};
	validator.validateEvidence(evidence);

	if (this->repository.isInDatabase(id) != -1)
		throw ServiceException("Evidence already added\n");

	this->repository.addElement(evidence);
}

void Service::updateEvidence(const std::string& id, const std::string& measurement, double imageClarityLevel, double quantity, const std::string& photoLink)
{
	Evidence evidence{ id, measurement, imageClarityLevel, quantity, photoLink };
	EvidenceValidator validator{};
	validator.validateEvidence(evidence);

	int inDatabaseResult = this->repository.isInDatabase(id);
	if (inDatabaseResult == -1)
		throw ServiceException("Inexistent evidence\n");
	
	this->repository.updateElement(inDatabaseResult, evidence);
}

void Service::removeEvidence(const std::string& id)
{
	if (id == "")
		throw ValidatorException("Empty id field\n");

	int inDatabaseResult = this->repository.isInDatabase(id);
	if (inDatabaseResult == -1)
		throw ServiceException("Inexistent evidence\n");

	this->repository.removeElement(id, inDatabaseResult);
}

std::vector<Evidence> Service::getAllEvidence() const
{
	return this->repository.getEvidenceDatabase();
}

EvidenceRepository& Service::getRepository()
{
	return this->repository;
}

vector<Evidence> Service::returnListByMeasurementQuantity(const std::string& measurement, double quantity)
{
	vector<Evidence> listByMeasurementQuantity{};
	for (int i = 0; i < this->getAllEvidence().size(); i++)
		if (this->getAllEvidence()[i].getMeasurement() == measurement && this->getAllEvidence()[i].getQuantity() >= quantity)
			listByMeasurementQuantity.push_back(this->getAllEvidence()[i]);

	return listByMeasurementQuantity;
}

// ============ Iterator ============

void Service::setIteratorListOfEvidences()
{
	this->repository.iterator();
}

Evidence Service::getCurrentEvidence()
{
	return this->repository.getCurrent();
}

void Service::nextEvidenceMyList()
{
	this->repository.next();
}


void Service::addEvidenceToMyList(const std::string& id)
{
	Evidence evidence = this->repository.getEvidenceById(id);
	if (evidence.getId() == "")	throw ServiceException("Empty id field\n");
	
	this->userEvidences.addEvidence(evidence);
}

void Service::getUserEvidences()
{
	this->userEvidences.displayUserEvidences();
}



