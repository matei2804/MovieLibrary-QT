#pragma once
#include <vector>
#include "Domain.h"


class Repository {
	
private:
	std::vector<Movie> dynamicArray;
	std::string movie_Filename;

public:
	
	Repository(std::vector<Movie>& dynamicArray, std::string& movie_Filename);
	~Repository();

	void load_Movie_from_file();
	void write_Movie_to_file();
	void initialize_Movie_Repository();

	std::vector<Movie>& get_all_Repo();

	int get_size_Repo();

	int find_movie_by_title_Repo(std::string);

	void add_movie_Repo(const Movie&);
	void delete_movie_Repo(int);
	void update_movie_Repo(int, const Movie&);
	void increment_likes_Repo(std::string title);
	void decrement_likes_Repo(std::string title);
};
