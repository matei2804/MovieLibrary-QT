#pragma once
#include "UserRepository.h"
#include "Repository.h"

class UserService
{
private:
	Repository& repo;
	UserRepository* user_repo;
public:

	UserService(Repository& repo, UserRepository* user_repo);

	explicit UserService(Repository& repository);

	~UserService();


	std::vector<Movie>& get_all_user_Service();

	int get_size_user_Service();

	void add_movie_user_Service(Movie&);
	int delete_movie_user_Service(std::string);
	void repository_Type(std::string& type);
	std::string get_Filename_Service();

};