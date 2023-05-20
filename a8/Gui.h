#pragma once
#include <QWidget>
#include "Service.h"
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include "Service.h"
#include "UserService.h"

class Gui : public QWidget
{
private:
	Service& service;
	QListWidget* moviesListWidget;
	QLineEdit* titleLineEdit;
	QLineEdit* genreLineEdit;
	QLineEdit* yearLineEdit;
	QLineEdit* likesLineEdit;
	QLineEdit* trailerLineEdit;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* clearButton;

	void initGui();
	void populateList();
	void connectSignalsAndSlots();
	int getSelectedIndex();
	void addMovie();
	void deleteMovie();
	void updateMovie();
	void clearFields();

public:
	Gui(Service& service);
	~Gui() {};
};