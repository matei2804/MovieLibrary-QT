#include "Gui.h"
#include <qlayout.h>
#include <QFormLayout>
#include <string>
#include "RepositoryExceptions.h"
#include <QMessageBox>
#include <QPalette>
#include <QColor>
#include <QBrush>

using namespace std;

Gui::Gui(Service& service) : service{ service }
{
	this->initGui();
	this->populateList();
	this->connectSignalsAndSlots();

	this->setFixedSize(700, 500);
}

void Gui::initGui()
{
	QVBoxLayout* mainLayout = new QVBoxLayout{ this };

	moviesListWidget = new QListWidget{};

	titleLineEdit = new QLineEdit{};
	genreLineEdit = new QLineEdit{};
	yearLineEdit = new QLineEdit{};
	likesLineEdit = new QLineEdit{};
	trailerLineEdit = new QLineEdit{};

	addButton = new QPushButton{ "Add" };
	deleteButton = new QPushButton{ "Delete" };
	updateButton = new QPushButton{ "Update" };
	clearButton = new QPushButton{ "Clear" };
	
	mainLayout->addWidget(moviesListWidget);
	QFormLayout* formLayout = new QFormLayout{};

	formLayout->addRow("Title", titleLineEdit);
	formLayout->addRow("Genre", genreLineEdit);
	formLayout->addRow("Year of release", yearLineEdit);
	formLayout->addRow("Likes", likesLineEdit);
	formLayout->addRow("Trailer", trailerLineEdit);

	mainLayout->addLayout(formLayout);

	QHBoxLayout* buttonsLayout = new QHBoxLayout{};
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(updateButton);
	buttonsLayout->addWidget(deleteButton);
	buttonsLayout->addWidget(clearButton);

	mainLayout->addLayout(buttonsLayout);

}

void Gui::populateList()
{
	this->moviesListWidget->clear();

	for (auto& movie : this->service.get_all_movies_Service())
	{
		QString itemInList = QString::fromStdString(movie.title_Getter() + " - " + movie.genre_Getter() + " - " + to_string(movie.year_of_release_Getter()) + " - " + to_string(movie.number_of_likes_Getter()) + " - " + movie.trailer_Getter());
		this->moviesListWidget->addItem(itemInList);
	}
}

void Gui::connectSignalsAndSlots()
{
	QObject::connect(this->moviesListWidget, &QListWidget::clicked, [this]() {
		int selectedIndex = getSelectedIndex();

		if (selectedIndex == -1)
		{
			this->titleLineEdit->clear();
			this->genreLineEdit->clear();
			this->yearLineEdit->clear();
			this->likesLineEdit->clear();
			this->trailerLineEdit->clear();
		}
		else
		{
			Movie movie = this->service.get_all_movies_Service()[selectedIndex];
			this->titleLineEdit->setText(QString::fromStdString(movie.title_Getter()));
			this->genreLineEdit->setText(QString::fromStdString(movie.genre_Getter()));
			this->yearLineEdit->setText(QString::fromStdString(to_string(movie.year_of_release_Getter())));
			this->likesLineEdit->setText(QString::fromStdString(to_string(movie.number_of_likes_Getter())));
			this->trailerLineEdit->setText(QString::fromStdString(movie.trailer_Getter()));
		}
		});

	QObject::connect(this->addButton, &QPushButton::clicked, this, &Gui::addMovie);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &Gui::deleteMovie);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &Gui::updateMovie);
	QObject::connect(this->clearButton, &QPushButton::clicked, this, &Gui::clearFields);
}

int Gui::getSelectedIndex() 
{
	QModelIndexList selectedIndexes = this->moviesListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->titleLineEdit->clear();
		this->genreLineEdit->clear();
		this->yearLineEdit->clear();
		this->likesLineEdit->clear();
		this->trailerLineEdit->clear();
	    int selectedIndex = -1;
		return selectedIndex;
	}

    int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}


void Gui::clearFields()
{
	this->titleLineEdit->clear();
	this->genreLineEdit->clear();
	this->yearLineEdit->clear();
	this->likesLineEdit->clear();
	this->trailerLineEdit->clear();
}

void Gui::addMovie()
{	
	int selectedIndex = getSelectedIndex();

	string title = this->titleLineEdit->text().toStdString();
	string genre = this->genreLineEdit->text().toStdString();
	string trailer = this->trailerLineEdit->text().toStdString();
	string year_of_release_string = this->yearLineEdit->text().toStdString();
	string number_of_likes_string = this->likesLineEdit->text().toStdString();

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

	int year_of_release = stoi(this->yearLineEdit->text().toStdString());
	int number_of_likes = stoi(this->likesLineEdit->text().toStdString());
	
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

void Gui::deleteMovie()
{
	int selectedIndex = getSelectedIndex();
	if (selectedIndex == -1)
	{
		QMessageBox::critical(this, "Error", "You have to select a movie!");
		return;
	}

	string title = this->titleLineEdit->text().toStdString();
	string genre = this->genreLineEdit->text().toStdString();
	string trailer = this->trailerLineEdit->text().toStdString();
	string year_of_realease_string = this->yearLineEdit->text().toStdString();
	string number_of_likes_string = this->likesLineEdit->text().toStdString();

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

	int year_of_release = stoi(this->yearLineEdit->text().toStdString());
	int number_of_likes = stoi(this->likesLineEdit->text().toStdString());

	if (selectedIndex < 0 || selectedIndex >= this->service.get_all_movies_Service().size())
	{
		QMessageBox::critical(this, "Error", "No movie was selected!");
		return;
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


void Gui::updateMovie()
{
	int selectedIndex = getSelectedIndex();
	if (selectedIndex == -1)
	{
		QMessageBox::critical(this, "Error", "You have to select a movie!");
		return;
	}

	string title = this->titleLineEdit->text().toStdString();
	string genre = this->genreLineEdit->text().toStdString();
	string trailer = this->trailerLineEdit->text().toStdString();
	string year_of_realease_string = this->yearLineEdit->text().toStdString();
	string number_of_likes_string = this->likesLineEdit->text().toStdString();

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

	int year_of_release = stoi(this->yearLineEdit->text().toStdString());
	int number_of_likes = stoi(this->likesLineEdit->text().toStdString());

	if (selectedIndex < 0 || selectedIndex >= this->service.get_all_movies_Service().size())
	{
		QMessageBox::critical(this, "Error", "No movie was selected!");
		return;
	}

	try
	{
		this->service.update_movie_Service(title, genre, year_of_release, number_of_likes, trailer);
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
