#include "evidence.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

Evidence::Evidence() : id(""), measurement(""), imageClarityLevel{ 0 }, quantity{ 0 }, photoLink("") {}

Evidence::Evidence(const std::string& id, const std::string& measurement, double imageClarityLevel, double quantity, const std::string& photoLink)
{
	this->id = id;
	this->measurement = measurement;
	this->imageClarityLevel = imageClarityLevel;
	this->quantity = quantity;
	this->photoLink = photoLink;
}

std::string Evidence::getId() const
{
	return this->id;
}

std::string Evidence::getMeasurement() const
{
	return this->measurement;
}

double Evidence::getImageClarityLevel() const
{
	return this->imageClarityLevel;
}

double Evidence::getQuantity() const
{
	return this->quantity;
}

std::string Evidence::getPhotoLink() const
{
	return this->photoLink;
}

void Evidence::setId(const std::string& id)
{
	this->id = id;
}

void Evidence::setMeasurement(std::string measurement)
{
	this->measurement = measurement;
}

void Evidence::setImageClarityLevel(double clarityLevel)
{
	this->imageClarityLevel = clarityLevel;
}

void Evidence::setQuantity(double quantity)
{
	this->quantity = quantity;
}

void Evidence::setPhotoLink(const std::string& photoLink)
{
	this->photoLink = photoLink;
}

std::string Evidence::toString()
{
	return this->getId() + ", " + this->getMeasurement() + ", " + std::to_string(this->getImageClarityLevel()) + ", " + std::to_string(this->getQuantity()) + ", " + this->getPhotoLink();
}

int Evidence::operator==(Evidence evidence1)
{
	if (this->getId() == evidence1.getId())
		return 1;
	return 0;
}

vector<string> tokenize(string stringLine, char delimiter)
{
	vector <string> result;
	stringstream stringStream(stringLine);
	string token;
	while (getline(stringStream, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& inputStream, Evidence& evidence)
{
	string line;
	getline(inputStream, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 5)
		return inputStream;

	evidence.id = tokens[0];
	evidence.measurement = tokens[1];
	evidence.imageClarityLevel = stoi(tokens[2]);
	evidence.quantity = stoi(tokens[3]);
	evidence.photoLink = tokens[4];

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Evidence& evidence)
{
	outputStream << evidence.getId() << "," << evidence.getMeasurement() << "," << evidence.getImageClarityLevel() << "," << evidence.getQuantity() << "," << evidence.getPhotoLink() << "\n";
	return outputStream;
}
