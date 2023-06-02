#include "Service.h"


Service::Service(Repository& repo, MovieValidator validator) : repo{repo}, validator{validator}
{
}

Service::~Service()
{
}

std::vector<Movie>& Service::get_all_movies_Service() {

	return this->repo.get_all_Repo();
}

int Service::get_size_Service() {

	return this->repo.get_size_Repo();
}

void Service::add_movie_Service(std::string add_title, std::string add_genre, int add_year_of_release, int add_likes, std::string add_trailer)
{
	this->validator.validate(Movie(add_title, add_genre, add_year_of_release, add_likes, add_trailer));
	this->repo.add_movie_Repo(Movie(add_title, add_genre, add_year_of_release, add_likes, add_trailer));
}

void Service::delete_movie_Service(std::string delete_title) {

	int delete_index = this->repo.find_movie_by_title_Repo(delete_title);
	this->repo.delete_movie_Repo(delete_index);
}

void Service::update_movie_Service(std::string update_title, std::string update_genre, int update_year, int update_likes, std::string update_trailer) {

	this->validator.validate(Movie(update_title, update_genre, update_year, update_likes, update_trailer));
	int update_index = this->repo.find_movie_by_title_Repo(update_title);
	this->repo.update_movie_Repo(update_index, Movie(update_title, update_genre, update_year, update_likes, update_trailer));
}

void Service::validate_title_Service(std::string& title) {
	this->validator.validate_title(title);
}

void Service::validate_genre_Service(std::string& genre) {
	this->validator.validate_genre(genre);
}

void Service::validate_year_of_release_Service(std::string& year_of_release) {
	this->validator.validate_year_of_release(year_of_release);
}

void Service::validate_likes_Service(std::string& likes) {
	this->validator.validate_likes(likes);
}

void Service::increment_likes_Service(std::string title) 
{
	this->repo.increment_likes_Repo(title);
}

void Service::decrement_likes_Service(std::string title)
{
	this->repo.decrement_likes_Repo(title);
}