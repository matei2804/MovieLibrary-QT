#include "RepositoryExceptions.h"

FileException::FileException(const std::string& message) : message(message)
{
}

const char* FileException::what()
{
	return message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{ "" }
{
}

RepositoryException::RepositoryException(const std::string& message) : message{ message }
{
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}

const char* DuplicateMovieException::what()
{
	return "There is another movie with the same title!\n";
}
