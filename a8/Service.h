#pragma once
#include "Repository.h"
#include "MovieValidator.h"

class Service {

private:
	Repository& repo;
	MovieValidator validator;

public:

	Service(Repository& repo, MovieValidator validator);
	~Service();

	std::vector<Movie>& get_all_movies_Service();

	int get_size_Service();

	void add_movie_Service(std::string, std::string, int, int, std::string);
	void delete_movie_Service(std::string);
	void update_movie_Service(std::string, std::string, int, int, std::string);

	void validate_title_Service(std::string& title);
	void validate_genre_Service(std::string& genre);

};
