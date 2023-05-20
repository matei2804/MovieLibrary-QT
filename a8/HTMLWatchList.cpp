#include "HTMLWatchList.h"
#include <fstream>
#include "RepositoryExceptions.h"


HTMLWatchList::HTMLWatchList(const std::vector<Movie>& watch_list, const std::string& user_Filename)
{
	this->movie_Filename = user_Filename;
	this->dynamicArray = watch_list;
}

std::vector<Movie>& HTMLWatchList::get_all_user_Repo()
{
	return this->dynamicArray;
}

int HTMLWatchList::get_size_user_Repo()
{
	return this->dynamicArray.size();
}

void HTMLWatchList::add_movie_user_Repo(Movie& movie)
{
	this->dynamicArray.push_back(movie);
	this->write_to_File();
}

void HTMLWatchList::delete_movie_user_Repo(int delete_index)
{
	this->dynamicArray.erase(this->dynamicArray.begin() + delete_index);
	this->write_to_File();
}

void HTMLWatchList::write_to_File()
{
	std::ofstream file(this->movie_Filename);
	if (!file.is_open()) {
		throw FileException("The file could not be opened!\n");
	}
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>WatchList</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "<tr>\n";
	file << "<td>Title</td>\n";
	file << "<td>Genre</td>\n";
	file << "<td>Year</td>\n";
	file << "<td>Likes</td>\n";
	file << "<td>Trailer</td>\n";
	file << "</tr>\n";
	for (auto movie : this->dynamicArray) {
		file << "<tr>\n";
		file << "<td>" << movie.title_Getter() << "</td>\n";
		file << "<td>" << movie.genre_Getter() << "</td>\n";
		file << "<td>" << movie.year_of_release_Getter() << "</td>\n";
		file << "<td>" << movie.number_of_likes_Getter() << "</td>\n";
		file << "<td><a href =" << movie.trailer_Getter() << ">Link</a></td>\n";
		file << "</tr>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";
	file.close();
}

std::string& HTMLWatchList::get_Filename()
{
	return this->movie_Filename;
}
