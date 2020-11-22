#pragma once
#include "myListEvidences.h"

class CSVmyList : public MyListEvidences
{
public:
	CSVmyList(const std::string& fileName) : MyListEvidences{ fileName } {};

	// add an evidence to the CSV file
	void addEvidence(const Evidence& evidence) override;

	// return a vector containing all the saved evidences in the CSV file
	void displayUserEvidences() override;

};

