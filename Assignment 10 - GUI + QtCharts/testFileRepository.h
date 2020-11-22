#pragma once
class TestFileRepository
{
public:
	void allTestsFileRepository();

private:
	void testAddElement_validInput_success();
	void testAddElement_invalidFileName_exceptionThrown();

	void testUpdateElement_validInput_success();
	void testUpdateElement_invalidFileName_exceptionThrown();

	void testRemoveElement_validInput_success();
	void testRemoveElement_invalidFileName_exceptionThrown();

	void testGetEvidenceDatabase_validInput_success();

	void testIsInDatabase_existentId_success();
	void testIsInDatabase_inexistentId_returnMinus1();

	void testGetEvidenceById_existentId_success();
	void testGetEvidenceById_inexistentId_returnEmptyEvidence();

	void testWriteToFile_invalidFileName_exceptionThrown();

	void testGetCurrent_validInput_success();
	void testNext_validInput_success();



};

