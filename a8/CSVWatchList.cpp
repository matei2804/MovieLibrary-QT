#include "CSVWatchList.h"
#include <fstream>
#include "RepositoryExceptions.h"
#include <Windows.h>

CSVWatchList::CSVWatchList(const std::vector<Movie>& watch_list, const std::string& user_Filename)
{
	this->dynamicArray = watch_list;
	this->movie_Filename = user_Filename;
}

std::vector<Movie>& CSVWatchList::get_all_user_Repo()
{
	return this->dynamicArray;
}

int CSVWatchList::get_size_user_Repo()
{
	return this->dynamicArray.size();
}

void CSVWatchList::add_movie_user_Repo(Movie& movie)
{
	this->dynamicArray.push_back(movie);
	this->write_to_File();
}

void CSVWatchList::delete_movie_user_Repo(int delete_index)
{
	this->dynamicArray.erase(this->dynamicArray.begin() + delete_index);
	this->write_to_File();
}

void CSVWatchList::write_to_File()
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

std::string& CSVWatchList::get_Filename()
{
	return this->movie_Filename;
}
