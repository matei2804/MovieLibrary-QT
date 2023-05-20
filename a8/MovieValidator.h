#pragma once
#include "Domain.h"
#include <vector>

class MovieException : public std::exception
{
private:

	std::vector<std::string> errors;

public:

	MovieException(std::vector<std::string> _errors);
	std::vector<std::string> getErrors() const;

};

class MovieValidator
{
public:

	MovieValidator() {}
	~MovieValidator() {}
	static void validate(const Movie& movie);
	void validate_title(const std::string& title);
	void validate_genre(const std::string& genre);
	bool checkForDigits(std::string string);
	void validate_year_of_release(const std::string& year_of_release);
	void validate_likes(const std::string& likes);
	
};
