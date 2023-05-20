#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_a8.h"

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = nullptr);
    ~Gui();

private:
    Ui::a8Class ui;
};
