#pragma once
#include "myListEvidences.h"
#include <vector>

class HTMLmyList: public MyListEvidences
{
private:
	std::vector<Evidence> savedEvidences;

public:
	HTMLmyList(const std::string& fileName) : MyListEvidences{ fileName } { };

	// add an evidence from the general database to user's list
	void addEvidence(const Evidence& evidence) override;

	// show all the evidences from user's list
	void displayUserEvidences() override;

};

