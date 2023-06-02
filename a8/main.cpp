#include <QtWidgets/QApplication>
#include "Service.h"
#include "a8.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main(int argc, char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    QApplication app(argc, argv);

    std::vector<Movie> movieList;
    std::vector<Movie> watchList;
    std::string movieFilename = R"(D:\Semestru 2\Object oriented programming\a8\a8\movies.txt)";
    Repository repo(movieList, movieFilename);
    MovieValidator validator;
    Service service(repo, validator);
    UserService user_service(repo);
    repo.initialize_Movie_Repository();
    a8 gui(service, user_service);

    gui.show();
    return app.exec();
}
