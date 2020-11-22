#include "inMemoryRepository.h"
#include "evidence.h"
using namespace std;

void InMemoryRepository::addElement(const Evidence& newElement)
{
	this->evidenceDatabase.push_back(newElement);
}

void InMemoryRepository::updateElement(int position, const Evidence& newElement)
{
	this->evidenceDatabase[position] = newElement;
}

void InMemoryRepository::removeElement(std::string id, int position)
{
	this->evidenceDatabase.erase(this->evidenceDatabase.begin() + position);
}

std::vector<Evidence> InMemoryRepository::getEvidenceDatabase()
{
	return this->evidenceDatabase;
}

int InMemoryRepository::isInDatabase(std::string id)
{
	int positionEvidence = 0;
	for (auto& evidence : this->evidenceDatabase)
	{
		if (evidence.getId() == id)
			return positionEvidence;
		positionEvidence++;
	}

	return -1;
}

Evidence InMemoryRepository::getEvidenceById(std::string id)
{
	vector<Evidence>::iterator iterator = find_if(this->evidenceDatabase.begin(), this->evidenceDatabase.end(), [id](Evidence evidence) { return evidence.getId() == id; });

	if (iterator != this->evidenceDatabase.end()) return *iterator;
	return Evidence{};
}

// ================= Iterator ==============================

void InMemoryRepository::iterator()
{
	this->iteratorInMemory = this->evidenceDatabase.begin();
}

Evidence InMemoryRepository::getCurrent()
{
	return *this->iteratorInMemory;
}

void InMemoryRepository::next()
{
	if (*this->iteratorInMemory == this->evidenceDatabase.back()) this->iterator();
	else ++this->iteratorInMemory;
}
