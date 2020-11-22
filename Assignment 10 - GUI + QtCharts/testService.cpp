#include "testService.h"
#include "inMemoryRepository.h"
#include "service.h" 
#include <assert.h>
#include "exceptions.h"
#include "HTMLmyList.h"
using namespace std;

void TestService::allTestsService()
{
	testAddEvidence_validElement_succes();
	testAddEvidence_emptyId_exceptionThrown();
	testAddEvidence_negativeQuantity_exceptionThrown();
	testAddEvidence_negativeImageClarityLevel_exceptionThrown();
	testAddEvidence_emptyPhotoLink_exceptionThrown();
	testAddEvidence_emptyMeasurement_exceptionThrown();
	testAddEvidence_duplicateId_exceptionThrown();

	testUpdateEvidence_validElement_success();
	testUpdateEvidence_negativeImageClarityLevel_exceptionThrown();
	testUpdateEvidence_inexistentId_exceptionThrown();
	testUpdateEvidence_emptyMeasurement_exceptionThrown();
	testUpdateEvidence_negativeQuantity_exceptionThrown();

	testRemoveEvidence_validElement_success();
	testRemoveEvidence_inexistentElement_noRemove();
	testRemoveEvidence_emptyId_exceptionThrown();

	testAddEvidenceToMyList_validId_success();
	testAddEvidenceToMyList_invalidId_noAdd();

	testGetRepository_validInput_success();

	testGetCurrentMyList_validInput_success();
	testNextEvidenceMyList_validInput_success();
	testReturnListByMeasurementQuantity_validInput_success();

	testAddEvidenceToMyList_CSVfile_validInput_success();
	testAddEvidenceToMyList_CSVfile_emptyId_exceptionThrown();
	testAddEvidenceToMyList_CSVfile_invalidFileName_exceptionThrown();

	testAddEvidenceToMyList_HTMLfile_emptyId_exceptionThrown();
	testAddEvidenceToMyList_HTMLfile_invalidFileName_exceptionThrown();
	testAddEvidenceToMyList_HTMLfile_validInput_success();

	testGetUserEvidences_CSVfile_validInput_success();
	testGetUserEvidences_HTMLfile_validInput_success();
}

void TestService::testAddEvidence_validElement_succes()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "12X3X4", 45, 5, "DSC345.jpg");

	assert(service.getAllEvidence().size() == 1);
}

void TestService::testAddEvidence_emptyId_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	try { service.addEvidence("", "1X2X3", 45, 5, "DSC345.jpg"); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Empty id\n") == 0);
	}
}

void TestService::testAddEvidence_negativeQuantity_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	try { service.addEvidence("2as", "1X2X3", 45, -5, "DSC345.jpg"); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Negative quantity\n") == 0);
	}
}

void TestService::testAddEvidence_negativeImageClarityLevel_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	try { service.addEvidence("2as", "1X2X3", -45, 5, "DSC345.jpg"); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Negative image clarity level\n") == 0);
	}
}

void TestService::testAddEvidence_emptyPhotoLink_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	try { service.addEvidence("2as", "1X2X3", 45, 5, ""); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Empty photo link\n") == 0);
	}
}

void TestService::testAddEvidence_emptyMeasurement_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	try { service.addEvidence("2as", "", 45, 5, "DSC345.jpg"); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Empty measurement\n") == 0);
	}
}

void TestService::testAddEvidence_duplicateId_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "1X2X3", 45, 5, "DSC345.jpg");
	try { service.addEvidence("2as", "1X2X3", 45, 5, "DSC345.jpg"); }
	catch (ServiceException& serviceException)
	{
		assert(strcmp(serviceException.what(), "ServiceException: Evidence already added\n") == 0);
	}
}

void TestService::testUpdateEvidence_validElement_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");
	service.updateEvidence("2as", "10X11X4", 11, 11, "DCS444.jpg");

	assert(service.getAllEvidence()[0].getImageClarityLevel() == 11);
}

void TestService::testUpdateEvidence_negativeImageClarityLevel_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");

	try { service.updateEvidence("2as", "10X11X4", -555, 11, "DCS444.jpg"); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Negative image clarity level\n") == 0);
	}
}

void TestService::testUpdateEvidence_negativeQuantity_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");

	try { service.updateEvidence("2as", "10X11X4", 555, -11, "DCS444.jpg"); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Negative quantity\n") == 0);
	}
}

void TestService::testUpdateEvidence_emptyMeasurement_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");

	try { service.updateEvidence("2as", "", 555, 11, "DCS444.jpg"); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Empty measurement\n") == 0);
	}
}

void TestService::testUpdateEvidence_inexistentId_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");

	try { service.updateEvidence("t", "10X11X4", 555, 11, "DCS444.jpg"); }
	catch (ServiceException& serviceException)
	{
		assert(strcmp(serviceException.what(), "ServiceException: Inexistent evidence\n") == 0);
	}
}

void TestService::testRemoveEvidence_validElement_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");
	service.removeEvidence("2as");

	assert(service.getAllEvidence().size() == 0);
}

void TestService::testRemoveEvidence_inexistentElement_noRemove()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");

	try { service.removeEvidence("ll"); }
	catch (ServiceException& serviceException)
	{
		assert(strcmp(serviceException.what(), "ServiceException: Inexistent evidence\n") == 0);
	}
}

void TestService::testRemoveEvidence_emptyId_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");

	try { service.removeEvidence(""); }
	catch (ValidatorException& validatorException)
	{
		assert(strcmp(validatorException.what(), "ValidatorException: Empty id field\n") == 0);
	}
}

void TestService::testAddEvidenceToMyList_validId_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");
	service.addEvidence("t", "10X11X4", 555, 11, "DCS444.jpg");

	try {
		service.addEvidenceToMyList("t");
		assert(true);
	}
	catch (...) {}
}

void TestService::testAddEvidenceToMyList_invalidId_noAdd()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");
	service.addEvidence("t", "10X11X4", 555, 11, "DCS444.jpg");

	try { service.addEvidenceToMyList("");}
	catch (ServiceException& serviceException) {
		assert(strcmp(serviceException.what(), "ServiceException: Empty id field\n") == 0);
	}
}

void TestService::testGetRepository_validInput_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	assert(service.getRepository().getEvidenceDatabase().size() == repository.getEvidenceDatabase().size());
}

void TestService::testGetCurrentMyList_validInput_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	Evidence evidence = Evidence{ "2as", "3X4X22", 45, 5, "DSC345.jpg" };
	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");
	service.addEvidence("t", "10X11X4", 555, 11, "DCS444.jpg");
	service.setIteratorListOfEvidences();

	assert(evidence == service.getCurrentEvidence());
}

void TestService::testNextEvidenceMyList_validInput_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	Evidence evidence = Evidence{ "t", "10X11X4", 555, 11, "DCS444.jpg" };

	service.addEvidence("2as", "3X4X22", 45, 5, "DSC345.jpg");
	service.addEvidence("t", "10X11X4", 555, 11, "DCS444.jpg");
	service.setIteratorListOfEvidences();

	service.nextEvidenceMyList();

	assert(evidence == service.getCurrentEvidence());
}

void TestService::testReturnListByMeasurementQuantity_validInput_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");
	service.addEvidence("6tt", "13X24X3", 500, 22, "DSC4325.jpg");
	service.addEvidence("1234", "1X52X53", 1000, 34, "DSC675.jpg");

	std::vector<Evidence> returnedList = service.returnListByMeasurementQuantity("1X2X3", 2);
	assert(returnedList.size() == 1);
}

void TestService::testAddEvidenceToMyList_CSVfile_validInput_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");
	service.addEvidence("6tt", "13X24X3", 500, 22, "DSC4325.jpg");
	service.addEvidence("1234", "1X52X53", 1000, 34, "DSC675.jpg");

	try { service.addEvidenceToMyList("55g"); }
	catch (...) {}
}

void TestService::testAddEvidenceToMyList_CSVfile_emptyId_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");

	try { service.addEvidenceToMyList(""); }
	catch (ServiceException& serviceException) 
	{
		assert(strcmp(serviceException.what(), "ServiceException: Empty id field\n") == 0);
	}
}

void TestService::testAddEvidenceToMyList_CSVfile_invalidFileName_exceptionThrown()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");

	try { service.addEvidenceToMyList("12ee"); }
	catch (MyListException& myListException)
	{
		assert(strcmp(myListException.what(), "MyListException: The file could not be opened!\n") == 0);
	}
}

void TestService::testAddEvidenceToMyList_HTMLfile_validInput_success()
{
	InMemoryRepository repository{};
	HTMLmyList myListRepository{ "HTMLtests.html" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");
	service.addEvidence("6tt", "13X24X3", 500, 22, "DSC4325.jpg");
	service.addEvidence("1234", "1X52X53", 1000, 34, "DSC675.jpg");

	try { service.addEvidenceToMyList("55g"); }
	catch (...) {}
}

void TestService::testAddEvidenceToMyList_HTMLfile_emptyId_exceptionThrown()
{
	InMemoryRepository repository{};
	HTMLmyList myListRepository{ "HTMLtests.html" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");

	try { service.addEvidenceToMyList(""); }
	catch (ServiceException& serviceException)
	{
		assert(strcmp(serviceException.what(), "ServiceException: Empty id field\n") == 0);
	}
}

void TestService::testAddEvidenceToMyList_HTMLfile_invalidFileName_exceptionThrown()
{
	InMemoryRepository repository{};
	HTMLmyList myListRepository{ "" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");

	try { service.addEvidenceToMyList("12ee"); }
	catch (MyListException& myListException)
	{
		assert(strcmp(myListException.what(), "MyListException: The file could not be opened!\n") == 0);
	}
}

void TestService::testGetUserEvidences_CSVfile_validInput_success()
{
	InMemoryRepository repository{};
	CSVmyList myListRepository{ "CSVtests.csv" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");
	service.addEvidenceToMyList("12ee");

	try { service.getUserEvidences(); }
	catch (...) { assert(false); }
}

void TestService::testGetUserEvidences_HTMLfile_validInput_success()
{
	InMemoryRepository repository{};
	HTMLmyList myListRepository{ "HTMLtests.html" };
	Service service{ repository, myListRepository };

	service.addEvidence("12ee", "1X2X3", 454, 3, "DSC44.jpg");
	service.addEvidence("55g", "1X2X3", 3444, 1, "DSC132.jpg");
	service.addEvidenceToMyList("12ee");

	try { service.getUserEvidences(); }
	catch (...) { assert(false); }
}

