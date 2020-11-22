#include "testInMemoryRepository.h"
#include "testInMemoryRepository.h"
#include <assert.h>
#include "evidence.h"
#include "inMemoryRepository.h"
#include <vector>
using namespace std;

void TestInMemoryRepository::allTestsRepository()
{
	testAddElement_validElement_succes();

	testUpdateElement_validElement_success();

	testRemoveElement_validElement_success();

	testGetEvidenceDatabase();

}

void TestInMemoryRepository::testAddElement_validElement_succes()
{
	InMemoryRepository repository{};

	Evidence evidence1{ "2as", "12X3X4", 45, 5, "DSC345.jpg" };
	Evidence evidence2{ "m11", "1X3X4", 31, 2, "DSC45.jpg" };

	repository.addElement(evidence1);
	repository.addElement(evidence2);

	assert(repository.getEvidenceDatabase().size() == 2);
}


void TestInMemoryRepository::testUpdateElement_validElement_success()
{
	InMemoryRepository repository{};

	Evidence evidence1{ "2as", "12X3X4", 45, 5, "DSC345.jpg" };
	Evidence evidence2{ "2as", "1X3X4", 31, 2, "DSC45.jpg" };

	repository.addElement(evidence1);
	repository.updateElement(0, evidence2);

	assert(repository.getEvidenceDatabase()[0].getImageClarityLevel() == 31);
}


void TestInMemoryRepository::testRemoveElement_validElement_success()
{
	InMemoryRepository repository{};

	Evidence evidence1{ "2as", "12X3X4", 45, 5, "DSC345.jpg" };
	Evidence evidence2{ "pp", "1X3X4", 31, 2, "DSC45.jpg" };

	repository.addElement(evidence1);
	repository.addElement(evidence2);

	repository.removeElement("pp", 1);

	assert(repository.getEvidenceDatabase()[0].getImageClarityLevel() == 45);
	assert(repository.getEvidenceDatabase().size() == 1);
}

void TestInMemoryRepository::testGetEvidenceDatabase()
{
	InMemoryRepository repository{};

	Evidence evidence1{ "2as", "12X3X4", 45, 5, "DSC345.jpg" };
	Evidence evidence2{ "pp", "1X3X4", 31, 2, "DSC45.jpg" };

	repository.addElement(evidence1);
	repository.addElement(evidence2);

	assert(repository.getEvidenceDatabase().size() == 2);
}
