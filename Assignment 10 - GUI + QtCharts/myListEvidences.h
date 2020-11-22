#pragma once
#include <vector>
#include "evidence.h"

class MyListEvidences
{
protected:
	std::string fileName;
public:
	MyListEvidences(const std::string& fileName) : fileName{ fileName } {};

	// add an evidence from the general database to user's list 
	virtual void addEvidence(const Evidence& evidence) = 0;

	// show all the evidences from user's list
	virtual void displayUserEvidences() = 0;

};

