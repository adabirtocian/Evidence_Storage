#pragma once
#include <iostream>

class Evidence
{
private:
	std::string id;
	std::string measurement;
	double imageClarityLevel;
	double quantity;
	std::string photoLink;

public:
	Evidence();

	Evidence(const std::string& id, const std::string& measurement, double imageClarityLevel, double quantity, const std::string& photoLink);


	std::string getId() const;
	std::string getMeasurement() const;
	double getImageClarityLevel() const;
	double getQuantity() const;
	std::string getPhotoLink() const;

	void setId(const std::string& id);
	void setMeasurement(std::string measurement);
	void setImageClarityLevel(double clarityLevel);
	void setQuantity(double quantity);
	void setPhotoLink(const std::string& photoLink);

	std::string toString();
	int operator==(Evidence evidence);

	friend std::istream& operator>>(std::istream& inputStream, Evidence& evidence);
	friend std::ostream& operator<<(std::ostream& outputStream, const Evidence& evidence);
};