#include "MovieValidator.h"

MovieException::MovieException(std::vector<std::string> _errors) : errors{ _errors }
{
}

std::vector<std::string> MovieException::getErrors() const
{
	return this->errors;
}

void MovieValidator::validate_title(const std::string& title)
{
	if (title.size() < 3)
		throw MovieException(std::vector<std::string>{ "The title name cannot be less than 3 characters!\n" });
}

void MovieValidator::validate_genre(const std::string& genre)
{
	if (genre.size() < 3)
		throw MovieException(std::vector<std::string>{ "The genre name cannot be less than 3 characters!\n" });
	if (genre.find_first_of("0123456789") != std::string::npos)
		throw MovieException(std::vector<std::string>{ "The genre name cannot contain numbers!\n" });
}

void MovieValidator::validate(const Movie& movie)
{
	std::vector<std::string> errors;

	if (movie.title_Getter().size() < 3)
		errors.push_back("The title name cannot be less than 3 characters!\n");
	if (movie.genre_Getter().size() < 3)
		errors.push_back("The genre name cannot be less than 3 characters!\n");
	if (movie.genre_Getter().find_first_of("0123456789") != std::string::npos)
		errors.push_back("The genre name cannot contain numbers!\n");
	if (movie.trailer_Getter().find("www.youtube.com") == std::string::npos)
		errors.push_back("The trailer link must be a YouTube link!\n");
	if (movie.number_of_likes_Getter() < 0)
		errors.push_back("The number of likes cannot be negative!\n");
	if (movie.year_of_release_Getter() < 1900)
		errors.push_back("The year of release cannot be less than 1900!\n");

	if (errors.size() > 0)
		throw MovieException(errors);
}

bool MovieValidator::checkForDigits(std::string stringToCheck)
{
	for (auto character : stringToCheck)
	{
		if (isdigit(character) == false)
			return 0;
	}
	return 1;
}

void MovieValidator::validate_year_of_release(const std::string& year_of_release)
{
	if (checkForDigits(year_of_release) == false)
		throw MovieException(std::vector<std::string>{ "The year of release must be a number!\n" });
	if (stoi(year_of_release) < 1900)
		throw MovieException(std::vector<std::string>{ "The year of release cannot be less than 1900!\n" });
}

void MovieValidator::validate_likes(const std::string& likes)
{
	if (checkForDigits(likes) == false)
		throw MovieException(std::vector<std::string>{ "The number of likes must be a number!\n" });
	if (stoi(likes) < 0)
		throw MovieException(std::vector<std::string>{ "The number of likes cannot be negative!\n" });
}