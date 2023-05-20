#include "Domain.h"
#include <Windows.h>
#include <shellapi.h>
#include <iostream>
#include <vector>
#include "Utils.h"

Movie::Movie()
{
	this->title = "empty";
	this->genre = "empty";
	this->year_of_release = 0;
	this->number_of_likes = 0;
	this->trailer = "empty";
}

Movie::Movie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer)
{
	this->title = title;
	this->genre = genre;
	this->year_of_release = year_of_release;
	this->number_of_likes = number_of_likes;
	this->trailer = trailer;

}

Movie::~Movie() = default;

std::string Movie::title_Getter() const{

	return this->title;
}

std::string Movie::genre_Getter() const{

	return this->genre;
}

int Movie::year_of_release_Getter() const{

	return this->year_of_release;
}

int Movie::number_of_likes_Getter() const{

	return this->number_of_likes;
}

std::string Movie::trailer_Getter() const{

	return this->trailer;
}

void Movie::title_Setter(std::string new_title) {

	this->title = new_title;
}

void Movie::genre_Setter(std::string new_genre){

	this->genre = new_genre;

}

void Movie::year_of_release_Setter(int new_year) {

	this->year_of_release = new_year;
}

void Movie::trailer_Setter(std::string new_trailer) {

	this->trailer = new_trailer;
}

void Movie::number_of_likes_Setter(int likes) {

	this->number_of_likes = likes;
}

std::string Movie::to_String(){

	std::string str_year_of_release = std::to_string(this->year_of_release);
	std::string str_number_of_likes = std::to_string(this->number_of_likes);

	return "Movie title: " + this->title + "\nGenre: " + this->genre + "\nYear of release: " + str_year_of_release + "\nNumber of likes: " + str_number_of_likes + "\nTrailer: " + this->trailer + "\n";
}

void Movie::play()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->trailer_Getter().c_str(), NULL, SW_SHOWMAXIMIZED);
}


std::istream& operator>>(std::istream& input_Stream, Movie& movie)
{
	std::string line;
	getline(input_Stream, line);

	std::vector<std::string> tokens = tokenize(line, ',');
	if (tokens.size() != 5) 
		return input_Stream;

	movie.title = tokens[0];
	movie.genre = tokens[1];
	movie.year_of_release = std::stoi(tokens[2]);
	movie.number_of_likes = std::stoi(tokens[3]);
	movie.trailer = tokens[4];

	return input_Stream;
}

std::ostream& operator<<(std::ostream& output_Stream, const Movie& movie)
{
	output_Stream << movie.title << "," << movie.genre << "," << movie.year_of_release << "," << movie.number_of_likes << "," << movie.trailer << "\n";
	return output_Stream;
}
