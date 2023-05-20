#pragma once
#include "UserRepository.h"

class HTMLWatchList : public UserRepository
{
public:
	HTMLWatchList(const std::vector<Movie>& watch_list, const std::string& user_Filename);

	~HTMLWatchList() {};

	std::vector<Movie>& get_all_user_Repo() override;
	int get_size_user_Repo() override;

	void add_movie_user_Repo(Movie& movie) override;

	void delete_movie_user_Repo(int) override;

	void write_to_File() override;

	std::string& get_Filename() override;
};
