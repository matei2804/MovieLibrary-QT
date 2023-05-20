/*#include <cassert>
#include <string>
#include "Domain.h"
#include "Repository.h"
#include "Service.h"
#include "UserRepository.h"
#include "UserService.h"
#include <iostream>


void test_Domain()
{
	Movie test_movie("test_title", "test_genre", 2000, 100, "https://www.youtube.com/watch?v=bK6ldnjE3Y0&ab_channel=UniversalPictures");

	assert(test_movie.title_Getter() == "test_title");
	assert(test_movie.genre_Getter() == "test_genre");
	assert(test_movie.year_of_release_Getter() == 2000);
	assert(test_movie.number_of_likes_Getter() == 100);
	assert(test_movie.trailer_Getter() == "https://www.youtube.com/watch?v=bK6ldnjE3Y0&ab_channel=UniversalPictures");

    auto str_year_of_release_Test = std::to_string(test_movie.year_of_release_Getter());
    auto str_number_of_likes_Test = std::to_string(test_movie.number_of_likes_Getter());

    std::string str_output_test = test_movie.to_String();

	assert(str_output_test == "Movie title: test_title\nGenre: test_genre\nYear of release: 2000\nNumber of likes: 100\nTrailer: https://www.youtube.com/watch?v=bK6ldnjE3Y0&ab_channel=UniversalPictures\n");

    test_movie.number_of_likes_Setter(0);
    assert(test_movie.number_of_likes_Getter() == 0);

    test_movie.title_Setter("X");
    assert(test_movie.title_Getter() == "X");

    test_movie.genre_Setter("X");
    assert(test_movie.genre_Getter() == "X");

    test_movie.year_of_release_Setter(0);
    assert(test_movie.year_of_release_Getter() == 0);

    test_movie.trailer_Setter("X");
    assert(test_movie.trailer_Getter() == "X");

    Movie empty_movie;
    assert(empty_movie.title_Getter() == "empty");

}


void test_Repository() {

    Repository repo;

    repo.add_ten_entries_Repo();

    assert(repo.get_size_Repo() == 10);

    std::vector<Movie> array = repo.get_all_Repo();

    assert(array[0].title_Getter() == "Harry Potter 1");

    Movie movie11 = Movie("test_title", "test_genre", 2000, 100, "da");
    repo.add_movie_Repo(movie11);
    assert(repo.get_size_Repo() == 11);

    Movie movie12 = Movie("test_title", "test_genre", 2000, 100, "nu");
    repo.update_movie_Repo(10, movie12);
    assert(array[9].trailer_Getter() != "nu");

    repo.delete_movie_Repo(10);
    assert(repo.get_size_Repo() == 10);

}

void test_Service() {

    Repository repo;
    Service service;
    service.add_ten_entries_Service();
    
    int test_add = service.add_movie_Service("test", "test", 0, 0, "test");

    assert(service.get_size_Service() == 11);
    assert(test_add == 1);

    int test_update = service.update_movie_Service("test", "update", 1, 1, "update");

    std::vector<Movie> array = service.get_all_movies_Service();

    assert(array[1].title_Getter() == "Harry Potter 2");
    assert(test_update == 1);
    assert(array[10].genre_Getter() == "update");
    assert(array[10].number_of_likes_Getter() == 1);
    assert(array[10].year_of_release_Getter() == 1);
    assert(array[10].trailer_Getter() == "update");

    int test_delete = service.delete_movie_Service("test");
    assert(test_delete == 1);
    assert(service.get_size_Service() == 10);

    int add_service_fail = service.add_movie_Service("Harry Potter 1", "Fantasy", 2001, 1, "https://www.youtube.com/watch?v=fSPJGqjYRb0&ab_channel=BingeNation");
    assert(add_service_fail == -1);

    int update_service_fail = service.update_movie_Service("1", "1", 1, 1, "1");
    assert(update_service_fail == -1);

    int delete_service_fail = service.delete_movie_Service("delete_fail");
    assert(delete_service_fail == -1);

}

void test_user_Repository()
{
    UserRepository user_repo;

    assert(user_repo.get_size_user_Repo() == 0);

    Movie movie_test = Movie("test_title", "test_genre", 2000, 100, "da");
    user_repo.add_movie_user_Repo(movie_test);

    assert(user_repo.get_size_user_Repo() == 1);

    std::vector<Movie> array = user_repo.get_all_user_Repo();

    assert(array[0].title_Getter() == "test_title");

    user_repo.delete_movie_user_Repo(0);

    assert(user_repo.get_size_user_Repo() == 0);

}

void test_user_Service()
{
    UserRepository user_repo;
    Repository repo;
    UserService user_service;

    assert(user_service.get_size_user_Service() == 0);

    Movie movie_test1 = Movie("test_title", "test_genre", 2000, 100, "da");

    user_service.add_movie_user_Service(movie_test1);
    assert(user_service.get_size_user_Service() == 1);

    Movie movie_test2 = Movie("test_title", "test_genre", 2000, 100, "da");
    user_service.add_movie_user_Service(movie_test2);

    std::vector<Movie> array = user_service.get_all_user_Service();

    assert(user_service.get_size_user_Service() == 2);
    user_service.delete_movie_user_Service(array[1].title_Getter());

    assert(user_service.get_size_user_Service() == 1);

    assert(user_service.delete_movie_user_Service("title_does_not_exist") == -1);

}

void test_all()
{
    test_Domain();
    test_Service();
    test_Repository();
    test_user_Repository();
    test_user_Service();
}
*/