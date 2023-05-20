#include "UserRepository.h"


UserRepository::UserRepository(std::vector<Movie>& dynamicArray)
{
	this->dynamicArray = dynamicArray;
}

UserRepository::UserRepository()
{

}

UserRepository::~UserRepository()
{
}

std::vector<Movie>& UserRepository::get_all_user_Repo()
{
	return this->dynamicArray;
}
