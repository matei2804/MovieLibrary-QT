#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_a8.h"
#include "Service.h"
#include "UserService.h"
#include "ui_dialog.h"


class a8 : public QMainWindow
{
	Q_OBJECT

public:
	a8(Service& service, UserService& user_service, QWidget *parent = Q_NULLPTR);
	~a8() {};

private:

	Service& service;
	UserService& user_service;
	Ui::a8Class ui;
	Ui::movieDialog movieDialog;
	bool repositoryType = false;
	int currentMovieIndex = 0;
	std::vector<Movie> searchResults;
	QDialog* movieDialogBox = nullptr;

	void populateList();
	void connectSignalsAndSlots();
	int getSelectedIndex();
	void addMovie();
	void deleteMovie();
	void updateMovie();
	void clearFields();
	void switchToAdminMode();
	void switchToUserMode();
	void watchListButton();
	void deleteWatchList();
	int getSelectedIndexWatchList();
	void populateWatchList();
	void searchMovies();

	void addWatchList();
	void nextMovieWatchList();
	void exitWatchList();
	void showMovieInfoDialog();
	void showDialog();

public slots:
	void on_watchListButton_clicked();

};
