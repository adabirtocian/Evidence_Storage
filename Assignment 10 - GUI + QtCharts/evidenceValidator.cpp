#include "evidenceValidator.h"
#include "exceptions.h"
#include <string>
using namespace std;

void EvidenceValidator::validateEvidence(const Evidence& evidence)
{
	string errors;
	if (evidence.getQuantity() <= 0)
		errors += string("Invalid quantity\n");

	if (evidence.getImageClarityLevel() <= 0)
		errors += string("Invalid image clarity level\n");

	if (evidence.getId() == "")
		errors += string("Empty id\n");

	if(evidence.getPhotoLink() == "")
		errors += string("Empty photo link\n");

	if(evidence.getMeasurement() == "")
		errors += string("Empty measurement\n");

	if (errors.size() > 0)
		throw ValidatorException(errors);
}
