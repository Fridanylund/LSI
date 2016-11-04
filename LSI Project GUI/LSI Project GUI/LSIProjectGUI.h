#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LSIProjectGUI.h"

class LSIProjectGUI : public QMainWindow
{
    Q_OBJECT

public:
    LSIProjectGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::LSIProjectGUIClass ui;

public slots: 
	void on_pushButton_clicked();
};
