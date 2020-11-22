#pragma once

class TestService
{
public:
	void allTestsService();

private:

	void testAddEvidence_validElement_succes();
	void testAddEvidence_emptyId_exceptionThrown();
	void testAddEvidence_negativeQuantity_exceptionThrown();
	void testAddEvidence_negativeImageClarityLevel_exceptionThrown();
	void testAddEvidence_emptyPhotoLink_exceptionThrown();
	void testAddEvidence_emptyMeasurement_exceptionThrown();
	void testAddEvidence_duplicateId_exceptionThrown();


	void testUpdateEvidence_validElement_success();
	void testUpdateEvidence_negativeImageClarityLevel_exceptionThrown();
	void testUpdateEvidence_negativeQuantity_exceptionThrown();
	void testUpdateEvidence_emptyMeasurement_exceptionThrown();
	void testUpdateEvidence_inexistentId_exceptionThrown();

	void testRemoveEvidence_validElement_success();
	void testRemoveEvidence_inexistentElement_noRemove();
	void testRemoveEvidence_emptyId_exceptionThrown();

	void testAddEvidenceToMyList_validId_success();
	void testAddEvidenceToMyList_invalidId_noAdd();

	void testGetRepository_validInput_success();

	void testGetCurrentMyList_validInput_success();
	void testNextEvidenceMyList_validInput_success();
	void testReturnListByMeasurementQuantity_validInput_success();

	void testAddEvidenceToMyList_CSVfile_validInput_success();
	void testAddEvidenceToMyList_CSVfile_emptyId_exceptionThrown();
	void testAddEvidenceToMyList_CSVfile_invalidFileName_exceptionThrown();

	void testAddEvidenceToMyList_HTMLfile_validInput_success();
	void testAddEvidenceToMyList_HTMLfile_emptyId_exceptionThrown();
	void testAddEvidenceToMyList_HTMLfile_invalidFileName_exceptionThrown();

	void testGetUserEvidences_CSVfile_validInput_success();
	void testGetUserEvidences_HTMLfile_validInput_success();

};