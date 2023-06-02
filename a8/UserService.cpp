#include "UserService.h"
#include "CSVWatchList.h"
#include "RepositoryExceptions.h"
#include "HTMLWatchList.h"
#include <memory>

UserService::UserService(Repository& repo, UserRepository* user_repo) : repo{ repo }, user_repo{ nullptr }
{
	
}

UserService::UserService(Repository& repository) : repo{ repository }
{

}

UserService::~UserService()
{

}

std::vector<Movie>& UserService::get_all_user_Service()
{
	return this->user_repo->get_all_user_Repo();
}

int UserService::get_size_user_Service()
{
	return this->user_repo->get_size_user_Repo();
}

void UserService::add_movie_user_Service(Movie& new_movie)
{
	this->user_repo->add_movie_user_Repo(new_movie);
}

bool UserService::delete_movie_user_Service(std::string delete_title) {

	int array_length = this->get_size_user_Service();

	std::vector<Movie> movie_list = this->get_all_user_Service();

	for (auto& movie : movie_list)
	{
		if (movie.title_Getter() == delete_title)
		{
			int i = &movie - &movie_list[0];
			this->user_repo->delete_movie_user_Repo(i);
			return true;
		}
	}

	return false;
}

void UserService::repository_Type(const std::string& fileType)
{
	if (fileType == "csv") {
		std::vector<Movie> userVector;
		std::string userFile = R"(D:\Semestru 2\Object oriented programming\a8\a8\CSVWatchList.csv)";
		this->user_repo = std::make_unique<CSVWatchList>(userVector, userFile);
	}
	else if (fileType == "html") {
		std::vector<Movie> userVector;
		std::string userFile = R"(D:\Semestru 2\Object oriented programming\a8\a8\HTMLWatchlist.html)";
		this->user_repo = std::make_unique<HTMLWatchList>(userVector, userFile);
	}
	else {
		std::string error;
		error += std::string("The filename is invalid!");
		if (!error.empty())
			throw FileException(error);
	}
}


std::string UserService::get_Filename_Service()
{
	return this->user_repo->get_Filename();
}