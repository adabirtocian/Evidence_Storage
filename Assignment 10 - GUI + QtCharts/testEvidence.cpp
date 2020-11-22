#include "testEvidence.h"
#include "evidence.h"
#include <assert.h>
#include <vector>

void TestEvidence::allTestsEvidence()
{
	testGetPhotoLink_validInput_success();

	testSetId_validInput_success();
	testSetMeasurement_validInput_success();
	testSetImageClarityLevel_validInput_success();
	testSetQuantity_validInput_success();
	testSetPhotoLink_validInput_success();

	testToString_validInput_success();
}

void TestEvidence::testGetPhotoLink_validInput_success()
{
	Evidence evidence{ "12e", "1X2X3", 23, 34, "DSC344.jpg" };
	assert(evidence.getPhotoLink() == "DSC344.jpg");
}

void TestEvidence::testSetId_validInput_success()
{
	Evidence evidence{ "12e", "1X2X3", 23, 34, "DSC344.jpg" };
	evidence.setId("rrr");
	assert(evidence.getId() == "rrr");
}

void TestEvidence::testSetMeasurement_validInput_success()
{
	Evidence evidence{ "12e", "1X2X3", 23, 34, "DSC344.jpg" };
	evidence.setMeasurement("6X65X5");
	assert(evidence.getMeasurement() == "6X65X5");
}

void TestEvidence::testSetImageClarityLevel_validInput_success()
{
	Evidence evidence{ "12e", "1X2X3", 23, 34, "DSC344.jpg" };
	evidence.setImageClarityLevel(100);
	assert(evidence.getImageClarityLevel() == 100);
}

void TestEvidence::testSetQuantity_validInput_success()
{
	Evidence evidence{ "12e", "1X2X3", 23, 34, "DSC344.jpg" };
	evidence.setQuantity(99);
	assert(evidence.getQuantity() == 99);
}

void TestEvidence::testSetPhotoLink_validInput_success()
{
	Evidence evidence{ "12e", "1X2X3", 23, 34, "DSC344.jpg" };
	evidence.setPhotoLink("sss");
	assert(evidence.getPhotoLink() == "sss");
}

void TestEvidence::testToString_validInput_success()
{
	Evidence evidence{ "12e", "1X2X3", 23, 34, "DSC344.jpg" };
	std::string string = "12e, 1X2X3, 23.000000, 34.000000, DSC344.jpg";

	assert(evidence.toString() == string);
}

