#include "Gui.h"
#include <QtWidgets/QApplication>
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    std::vector<Movie> movieList;
    std::string movieFilename = R"(D:\Semestru 2\Object oriented programming\a8\a8\movies.txt)";
    Repository repo(movieList, movieFilename);
    MovieValidator validator;
    Service service(repo, validator);
    //UserService user_service(repo);
    repo.initialize_Movie_Repository();
    Gui gui(service);

    gui.show();
    return app.exec();
}
