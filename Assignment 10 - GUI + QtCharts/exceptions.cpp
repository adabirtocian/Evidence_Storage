#include "exceptions.h"
#include <string>
using namespace std;

// =========== Validator ==============================

ValidatorException::ValidatorException(std::string message)
{
	this->message = this->message + message;
}

const char* ValidatorException::what() const noexcept
{
	return this->message.c_str();
}

// =============== Service ================================

ServiceException::ServiceException(std::string message)
{
	this->message = this->message + message;
}

const char* ServiceException::what() const noexcept
{
	return this->message.c_str();
}


// ===================File Repository ===========================

RepositoryException::RepositoryException(std::string message)
{
	this->message = this->message + message;
}

const char* RepositoryException::what() const noexcept
{
	return this->message.c_str();
}


// ================== My List =========================

MyListException::MyListException(std::string message)
{
	this->message = this->message + message;
}

const char* MyListException::what() const noexcept
{
	return this->message.c_str();
}
