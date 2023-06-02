#include "a8.h"
#include <qmessagebox.h>
#include <string>
#include "RepositoryExceptions.h"
#include "UserRepository.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"
#include <memory>
#include <QLabel>

using namespace std;

a8::a8(Service& service, UserService& user_service, QWidget* parent) : service{ service }, user_service{user_service}, QMainWindow(parent)
{
	ui.setupUi(this);
	populateList();
	connectSignalsAndSlots();
	setFixedSize(900, 600);
	ui.stackedWidget->setCurrentIndex(0);

}

void a8::populateList()
{
	this->ui.moviesListWidget->clear();

	for (auto& movie : this->service.get_all_movies_Service())
	{
		QString itemInList = QString::fromStdString(movie.title_Getter() + " - " + movie.genre_Getter() + " - " + to_string(movie.year_of_release_Getter()) + " - " + to_string(movie.number_of_likes_Getter()) + " - " + movie.trailer_Getter());
		this->ui.moviesListWidget->addItem(itemInList);
	}
}

void a8::connectSignalsAndSlots()
{
	QObject::connect(this->ui.moviesListWidget, &QListWidget::clicked, [this]() {
		int selectedIndex = getSelectedIndex();

		if (selectedIndex == -1)
		{
			this->ui.titleLineEdit->clear();
			this->ui.genreLineEdit->clear();
			this->ui.yearLineEdit->clear();
			this->ui.likesLineEdit->clear();
			this->ui.trailerLineEdit->clear();
		}
		else
		{
			Movie movie = this->service.get_all_movies_Service()[selectedIndex];
			this->ui.titleLineEdit->setText(QString::fromStdString(movie.title_Getter()));
			this->ui.genreLineEdit->setText(QString::fromStdString(movie.genre_Getter()));
			this->ui.yearLineEdit->setText(QString::fromStdString(to_string(movie.year_of_release_Getter())));
			this->ui.likesLineEdit->setText(QString::fromStdString(to_string(movie.number_of_likes_Getter())));
			this->ui.trailerLineEdit->setText(QString::fromStdString(movie.trailer_Getter()));
		}
		});

	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &a8::addMovie);
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &a8::deleteMovie);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &a8::updateMovie);
	QObject::connect(this->ui.clearButton, &QPushButton::clicked, this, &a8::clearFields);

	QObject::connect(ui.actionAdminMode, &QAction::triggered, this, &a8::switchToAdminMode);
	QObject::connect(ui.actionUserMode, &QAction::triggered, this, &a8::switchToUserMode);

	QObject::connect(ui.showWatchListPushButton, &QPushButton::clicked, this, &a8::watchListButton);
	QObject::connect(ui.deleteWatchListPushButton, &QPushButton::clicked, this, &a8::deleteWatchList);
	QObject::connect(ui.searchPushButton, &QPushButton::clicked, this, &a8::searchMovies);
	QObject::connect(this->ui.watchListWidget, &QListWidget::clicked, [this]()
	{
		int selectedIndex = getSelectedIndexWatchList();
		if (selectedIndex == -1)
		{
			this->ui.deleteWatchListLineEdit->clear();
		}
		else
		{
			Movie movie = this->user_service.get_all_user_Service()[selectedIndex];
			this->ui.deleteWatchListLineEdit->setText(QString::fromStdString(movie.title_Getter()));
		}
	});
}

int a8::getSelectedIndex()
{
	QModelIndexList selectedIndexes = this->ui.moviesListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->ui.titleLineEdit->clear();
		this->ui.genreLineEdit->clear();
		this->ui.yearLineEdit->clear();
		this->ui.likesLineEdit->clear();
		this->ui.trailerLineEdit->clear();
		int selectedIndex = -1;
		return selectedIndex;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}


void a8::clearFields()
{
	this->ui.titleLineEdit->clear();
	this->ui.genreLineEdit->clear();
	this->ui.yearLineEdit->clear();
	this->ui.likesLineEdit->clear();
	this->ui.trailerLineEdit->clear();
	ui.moviesListWidget->clearSelection();
}

void a8::addMovie()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	string genre = this->ui.genreLineEdit->text().toStdString();
	string trailer = this->ui.trailerLineEdit->text().toStdString();
	string year_of_release_string = this->ui.yearLineEdit->text().toStdString();
	string number_of_likes_string = this->ui.likesLineEdit->text().toStdString();

	if (title.empty() || genre.empty() || trailer.empty() || year_of_release_string.empty() || number_of_likes_string.empty())
	{
		QMessageBox::warning(this, "Warning", "Please fill in all the fields!");
		return;
	}

	try {
		this->service.validate_year_of_release_Service(year_of_release_string);
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
		return;
	}

	try {
		this->service.validate_likes_Service(number_of_likes_string);
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
		return;
	}

	int year_of_release = stoi(this->ui.yearLineEdit->text().toStdString());
	int number_of_likes = stoi(this->ui.likesLineEdit->text().toStdString());

	try
	{
		this->service.add_movie_Service(title, genre, year_of_release, number_of_likes, trailer);
		this->populateList();
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
	}
	catch (RepositoryException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
	}

}

void a8::deleteMovie()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	int selectedIndex = getSelectedIndex();

	if (selectedIndex == -1 && title.empty())
	{
		QMessageBox::critical(this, "Error", "You have to select a movie or input a title!");
		return;
	}

	if (selectedIndex != -1 && selectedIndex < this->service.get_all_movies_Service().size())
	{
		title = this->service.get_all_movies_Service()[selectedIndex].title_Getter();
	}

	try
	{
		this->service.delete_movie_Service(title);
		this->populateList();
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
	}
	catch (RepositoryException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
	}
}


void a8::updateMovie()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	int selectedIndex = getSelectedIndex();

	if (selectedIndex == -1 && title.empty())
	{
		QMessageBox::critical(this, "Error", "You have to select a movie!");
		return;
	}

	string genre = this->ui.genreLineEdit->text().toStdString();
	string trailer = this->ui.trailerLineEdit->text().toStdString();
	string year_of_realease_string = this->ui.yearLineEdit->text().toStdString();
	string number_of_likes_string = this->ui.likesLineEdit->text().toStdString();

	try {
		this->service.validate_year_of_release_Service(year_of_realease_string);
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
		return;
	}

	try {
		this->service.validate_likes_Service(number_of_likes_string);
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
		return;
	}

	int year_of_release = stoi(this->ui.yearLineEdit->text().toStdString());
	int number_of_likes = stoi(this->ui.likesLineEdit->text().toStdString());

	if (selectedIndex < 0 || selectedIndex >= this->service.get_all_movies_Service().size())
	{
		QMessageBox::critical(this, "Error", "No movie was selected!");
		return;
	}

	try
	{
		this->service.update_movie_Service(title, genre, year_of_release, number_of_likes, trailer);
		this->populateList();
		selectedIndex = getSelectedIndex();
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
	}
	catch (RepositoryException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
	}
}

void a8::switchToAdminMode()
{
	ui.stackedWidget->setCurrentIndex(0);
}

void a8::switchToUserMode()
{

	if (repositoryType)
	{
		ui.stackedWidget->setCurrentIndex(1);
		return;
	}
	else 
	{
		QMessageBox msgBox;
		msgBox.setText("Choose a user repository format:");

		QAbstractButton* pButtonCsv = msgBox.addButton("CSV", QMessageBox::YesRole);
		QAbstractButton* pButtonHtml = msgBox.addButton("HTML", QMessageBox::NoRole);

		msgBox.exec();

		if (msgBox.clickedButton() == pButtonCsv) 
		{
			user_service.repository_Type("csv");
		}
		else if (msgBox.clickedButton() == pButtonHtml) 
		{
			user_service.repository_Type("html");
		}
		else 
		{
			return;
		}

		repositoryType = true;
		ui.stackedWidget->setCurrentIndex(1);
	}
}

void a8::watchListButton()
{
	std::string link = std::string("start \"\" \"") + this->user_service.get_Filename_Service() + "\"";
	system(link.c_str());
}

void a8::on_watchListButton_clicked() 
{
	watchListButton();
}

void a8::deleteWatchList()
{
	string title = this->ui.deleteWatchListLineEdit->text().toStdString();
	int selectedIndex = getSelectedIndexWatchList();
	bool deleted;

	if (selectedIndex == -1 && title.empty())
	{
		QMessageBox::critical(this, "Error", "You have to select a movie or input a title!");
		return;
	}

	if (selectedIndex != -1 && selectedIndex < this->user_service.get_all_user_Service().size())
	{
		title = this->user_service.get_all_user_Service()[selectedIndex].title_Getter();
	}

	try
	{
		deleted = this->user_service.delete_movie_user_Service(title);
		this->populateWatchList();
	}
	catch (MovieException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.getErrors()[0]));
	}
	catch (RepositoryException& e)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
	}

	if (deleted == true)
	{
		QMessageBox msgBox;
		string message = "Did you like the movie?\n" + title;
		msgBox.setText(QString::fromStdString(message));

		QAbstractButton* pButtonLike = msgBox.addButton("Like", QMessageBox::YesRole);
		QAbstractButton* pButtonDislike = msgBox.addButton("Dislike", QMessageBox::NoRole);

		msgBox.exec();

		if(msgBox.clickedButton() == pButtonLike)
		{
			this->service.increment_likes_Service(title);
			this->populateList();
			this->ui.deleteWatchListLineEdit->clear();
		}
		else if (msgBox.clickedButton() == pButtonDislike)
		{
			this->service.decrement_likes_Service(title);
			this->populateList();
			this->ui.deleteWatchListLineEdit->clear();
		}
		else
		{
			this->ui.deleteWatchListLineEdit->clear();
			return;
		}
	}
	else
	{
		QMessageBox::critical(this, "Error", "The movie is not in the watch list!");
	}
}

int a8::getSelectedIndexWatchList()
{
	QModelIndexList selectedIndexes = this->ui.watchListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->ui.deleteWatchListLineEdit->clear();
		int selectedIndex = -1;
		return selectedIndex;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void a8::populateWatchList()
{
	this->ui.watchListWidget->clear();

	for (auto& movie : this->user_service.get_all_user_Service())
	{
		QString itemInList = QString::fromStdString(movie.title_Getter() + " - " + movie.genre_Getter() + " - " + to_string(movie.year_of_release_Getter()) + " - " + to_string(movie.number_of_likes_Getter()) + " - " + movie.trailer_Getter());
		this->ui.watchListWidget->addItem(itemInList);
	}
}

void a8::searchMovies()
{
	std::string genre = ui.searchLineEdit->text().toStdString();

	if (genre.empty())
	{
		searchResults = service.get_all_movies_Service();
	}
	else
	{
		searchResults.clear();
		for (const Movie& movie : service.get_all_movies_Service())
		{
			if (movie.genre_Getter() == genre)
			{
				searchResults.push_back(movie);
			}
		}
	}

	currentMovieIndex = 0;

	if (!searchResults.empty())
	{
		showDialog();
	}
	else
	{
		QMessageBox::critical(this, "Error", "No movies found!");
	}
}


void a8::showMovieInfoDialog()
{
	if (currentMovieIndex >= 0 && currentMovieIndex < searchResults.size())
	{
		const Movie& movie = searchResults[currentMovieIndex];
		movieDialog.titleLabel->setText(QString::fromStdString(movie.title_Getter()));
		movieDialog.genreLabel->setText(QString::fromStdString(movie.genre_Getter()));
		movieDialog.yearLabel->setText(QString::fromStdString(to_string(movie.year_of_release_Getter())));
		movieDialog.likesLabel->setText(QString::fromStdString(to_string(movie.number_of_likes_Getter())));
		
		QString linkString = "<a href=\"" + QString::fromStdString(movie.trailer_Getter()) + "\">" + "Watch Trailer" + "</a>";
		movieDialog.yearLabel_2->setText(linkString);
		movieDialog.yearLabel_2->setTextFormat(Qt::RichText);
		movieDialog.yearLabel_2->setTextInteractionFlags(Qt::TextBrowserInteraction);
		movieDialog.yearLabel_2->setOpenExternalLinks(true);


		if (currentMovieIndex + 1 >= searchResults.size())
		{
			currentMovieIndex = -1;
			movieDialog.nextPushButton->setEnabled(true);
		}
		else
		{
			movieDialog.nextPushButton->setEnabled(true);
		}
	}
}

void a8::addWatchList()
{
	if (currentMovieIndex >= 0 && currentMovieIndex < searchResults.size())
	{
		Movie& currentMovie = searchResults[currentMovieIndex];
		for (auto& movie : user_service.get_all_user_Service())
		{
			if (movie.title_Getter() == currentMovie.title_Getter())
			{
				QMessageBox::critical(this, "Error", "Movie already in watch list!");
				return;
			}
		}
		user_service.add_movie_user_Service(currentMovie);
		populateWatchList();
	}
	nextMovieWatchList();
}

void a8::nextMovieWatchList()
{
	if (currentMovieIndex + 1 < searchResults.size())
	{
		currentMovieIndex++;
		showMovieInfoDialog();
	}
}

void a8::showDialog()
{
	movieDialogBox = new QDialog(this);
	movieDialog.setupUi(movieDialogBox);

	QObject::connect(movieDialog.addWatchListPushButton, &QPushButton::clicked, this, &a8::addWatchList);
	QObject::connect(movieDialog.nextPushButton, &QPushButton::clicked, this, &a8::nextMovieWatchList);
	QObject::connect(movieDialog.exitPushButton, &QPushButton::clicked, this, &a8::exitWatchList);

	showMovieInfoDialog();

	movieDialogBox->exec();
}

void a8::exitWatchList()
{
	movieDialogBox->close();
}
