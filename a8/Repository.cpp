#include "Repository.h"
#include "RepositoryExceptions.h"
#include <fstream>


Repository::Repository(std::vector<Movie>& dynamicArray, std::string& movie_Filename)
{
	this->dynamicArray = dynamicArray;
	this->movie_Filename = movie_Filename;
}

Repository::~Repository()
{
}

void Repository::load_Movie_from_file()
{
	std::ifstream file(this->movie_Filename);

	if (!file.is_open()) {
		throw FileException("The file could not be opened!\n");
	}
	Movie movie_to_add;
	while (file >> movie_to_add) {
		this->dynamicArray.push_back(movie_to_add);
	}
	file.close();
}

void Repository::write_Movie_to_file()
{
	std::ofstream file(this->movie_Filename);
	if (!file.is_open()) {
		throw FileException("The file could not be opened!\n");
	}
	for (auto movie : this->dynamicArray) {
		file << movie;
	}
	file.close();
}

void Repository::initialize_Movie_Repository()
{
	this->load_Movie_from_file();
}

std::vector<Movie>& Repository::get_all_Repo()
{
	return this->dynamicArray;
}


int Repository::get_size_Repo()
{
	return this->dynamicArray.size();
}

void Repository::add_movie_Repo(const Movie& movie_to_add)
{
	int index = this->find_movie_by_title_Repo(movie_to_add.title_Getter());
	if (index != -1) {
		throw DuplicateMovieException();
	}
	else
	{
		this->dynamicArray.push_back(movie_to_add);
		this->write_Movie_to_file();
	}
}

void Repository::delete_movie_Repo(int delete_index)
{
	if (delete_index == -1) {
		std::string error;
		error += std::string("\nThe movie does not exist!\n");
		if (!error.empty())
			throw RepositoryException(error);
	}
	else
	{
		this->dynamicArray.erase(this->dynamicArray.begin() + delete_index);
		this->write_Movie_to_file();
	}
}

void Repository::update_movie_Repo(int update_index, const Movie& new_movie)
{
	if (update_index == -1) {
		std::string error;
		error += std::string("\nThe movie does not exist!\n");
		if (!error.empty())
			throw RepositoryException(error);
	}
	else
	{
		this->dynamicArray[update_index] = new_movie;
		this->write_Movie_to_file();
	}
}

int Repository::find_movie_by_title_Repo(std::string title_to_find) {
	int index = 0;
	for (auto movie : this->dynamicArray) {
		if (movie.title_Getter() == title_to_find) {
			return index;
		}
		index++;
	}
	return -1;
}

void Repository::increment_likes_Repo(std::string title)
{
	int index = this->find_movie_by_title_Repo(title);
	if (index == -1) {
		std::string error;
		error += std::string("\nThe movie does not exist!\n");
		if (!error.empty())
			throw RepositoryException(error);
	}
	else
	{
		this->dynamicArray[index].number_of_likes_Setter(this->dynamicArray[index].number_of_likes_Getter() + 1);
		this->write_Movie_to_file();
	}
}

void Repository::decrement_likes_Repo(std::string title)
{
	int index = this->find_movie_by_title_Repo(title);
	if (index == -1) {
		std::string error;
		error += std::string("\nThe movie does not exist!\n");
		if (!error.empty())
			throw RepositoryException(error);
	}
	else
	{
		this->dynamicArray[index].number_of_likes_Setter(this->dynamicArray[index].number_of_likes_Getter() - 1);
		this->write_Movie_to_file();
	}
}