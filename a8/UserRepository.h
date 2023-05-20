#pragma once
#include <vector>
#include "Domain.h"


class UserRepository
{
protected:
	std::vector<Movie> dynamicArray;
	std::string movie_Filename;

public:

	explicit UserRepository(std::vector<Movie>& dynamicArray);
	UserRepository();
	~UserRepository();

	virtual std::vector<Movie>& get_all_user_Repo() = 0;
	virtual void add_movie_user_Repo(Movie&) = 0;

	virtual int get_size_user_Repo() = 0;
	virtual void delete_movie_user_Repo(int) = 0;

	virtual void write_to_File() = 0;
	virtual std::string& get_Filename() = 0;

};