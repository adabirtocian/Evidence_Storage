#pragma once
#include "evidenceRepository.h"
#include <iostream>
#include "evidence.h"
#include <vector>
#include "myListEvidences.h"
#include "CSVmyList.h"

class Service
{
private:
	EvidenceRepository& repository;
	MyListEvidences& userEvidences;

public:
	// constructor
	Service(EvidenceRepository& repository, MyListEvidences& userEvidences) : repository{ repository }, userEvidences{ userEvidences } {}

	// ================ REPOSITORY ==================

	// add a new evidence
	void addEvidence(const std::string& id, const std::string& measurement, double imageClarityLevel, double quantity, const std::string& photoLink);

	// update an existing evidence
	void updateEvidence(const std::string& id, const std::string& measurement, double imageClarityLevel, double quantity, const std::string& photoLink);

	// remove an existing evidence
	void removeEvidence(const std::string& id);

	// return the list of all evidences
	std::vector<Evidence> getAllEvidence() const;

	// return the whole repository
	EvidenceRepository& getRepository();

	// add all the evidences matching a given measurement and having at least a given quantity
	std::vector<Evidence> returnListByMeasurementQuantity(const std::string& measurement, double quantity);


	// ============ Iterator ============

	// initialize the iterator to the first evidence in the database
	void setIteratorListOfEvidences();

	// return the current evidence to by displayed
	Evidence getCurrentEvidence();

	// go to the next evidence from the local list displayed for the user in mode B
	void nextEvidenceMyList();

	// ================ My List ==================

	// display all the saved evidences 
	void getUserEvidences();

	// add an evidence from the general database to user's list 
	void addEvidenceToMyList(const std::string& id);

};