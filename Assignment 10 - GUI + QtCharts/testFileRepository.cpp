#include "testFileRepository.h"
#include "evidence.h"
#include "fileRepository.h"
#include "exceptions.h"
#include <assert.h>

void TestFileRepository::allTestsFileRepository()
{
	testAddElement_validInput_success();
	testAddElement_invalidFileName_exceptionThrown();

	testUpdateElement_validInput_success();
	testUpdateElement_invalidFileName_exceptionThrown();

	testRemoveElement_validInput_success();
	testRemoveElement_invalidFileName_exceptionThrown();

	testGetEvidenceDatabase_validInput_success();

	testIsInDatabase_existentId_success();
	testIsInDatabase_inexistentId_returnMinus1();

	testGetEvidenceById_existentId_success();
	testGetEvidenceById_inexistentId_returnEmptyEvidence();

	testWriteToFile_invalidFileName_exceptionThrown();

	testGetCurrent_validInput_success();
	testNext_validInput_success();
}

void TestFileRepository::testAddElement_validInput_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });

	std::vector<Evidence> dataFromFile = fileRepository.readFromFile();
	assert(dataFromFile.size() == 2);
}

void TestFileRepository::testAddElement_invalidFileName_exceptionThrown()
{
	FileRepository fileRepository{ "" };
	try {
		fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });}
	catch (RepositoryException& repoException) {
		assert(strcmp(repoException.what(), "RepositoryException: The file could not be opened!\n") == 0);
	}
}

void TestFileRepository::testUpdateElement_validInput_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });
	fileRepository.updateElement(0, Evidence{ "w3", "10X10X10", 10, 10, "dd" });

	std::vector<Evidence> dataFromFile = fileRepository.readFromFile();
	assert(dataFromFile[0].getQuantity() == 10);
}

void TestFileRepository::testUpdateElement_invalidFileName_exceptionThrown()
{
	FileRepository fileRepository{ "" };
	try {
		fileRepository.updateElement(0, Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });}
	catch (RepositoryException& repoException) {
		assert(strcmp(repoException.what(), "RepositoryException: The file could not be opened!\n") == 0);
	}
}

void TestFileRepository::testRemoveElement_validInput_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });
	fileRepository.removeElement("ppp", 1);

	std::vector<Evidence> dataFromFile = fileRepository.readFromFile();
	assert(dataFromFile.size() == 1);
}

void TestFileRepository::testRemoveElement_invalidFileName_exceptionThrown()
{
	FileRepository fileRepository{ "" };
	try {
		fileRepository.removeElement("w3", 0); }
	catch (RepositoryException& repoException) {
		assert(strcmp(repoException.what(), "RepositoryException: The file could not be opened!\n") == 0);
	}
}

void TestFileRepository::testGetEvidenceDatabase_validInput_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });

	std::vector<Evidence> dataFromFile = fileRepository.getEvidenceDatabase();
	assert(dataFromFile.size() == 2);
}

void TestFileRepository::testIsInDatabase_existentId_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });

	assert(fileRepository.isInDatabase("w3") == 1);
}

void TestFileRepository::testIsInDatabase_inexistentId_returnMinus1()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });

	assert(fileRepository.isInDatabase("lll") == -1);
}

void TestFileRepository::testGetEvidenceById_existentId_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });
	Evidence evidence = Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" };

	assert(fileRepository.getEvidenceById("w3") == evidence);
}

void TestFileRepository::testGetEvidenceById_inexistentId_returnEmptyEvidence()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });

	assert(fileRepository.getEvidenceById("r") == Evidence{});
}

void TestFileRepository::testWriteToFile_invalidFileName_exceptionThrown()
{
	FileRepository fileRepository{ "" };
	try {
		fileRepository.writeToFile(std::vector<Evidence>{}); }
	catch (RepositoryException& repoException) {
		assert(strcmp(repoException.what(), "RepositoryException: The file could not be opened!\n") == 0);
	}
}

void TestFileRepository::testGetCurrent_validInput_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });
	Evidence evidence = Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" };

	fileRepository.iterator();
	assert(fileRepository.getCurrent() == evidence);
}

void TestFileRepository::testNext_validInput_success()
{
	FileRepository fileRepository{ "tests.txt" };
	fileRepository.writeToFile(std::vector<Evidence>{});

	fileRepository.addElement(Evidence{ "w3", "1X2X3", 3, 4, "DSC34.jpg" });
	fileRepository.addElement(Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" });
	Evidence evidence = Evidence{ "ppp", "1X2X3", 23, 4445, "DSC894.jpg" };

	fileRepository.iterator();
	fileRepository.next();
	assert(fileRepository.getCurrent() == evidence);
}
