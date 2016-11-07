#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LSIProjectGUI.h"
#include "qcustomplot.h"

class LSIProjectGUI : public QMainWindow
{
    Q_OBJECT

public:
    LSIProjectGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::LSIProjectGUIClass ui;

public slots: 
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_createROIButton_clicked();
	void on_removeROIButton_clicked();

private slots:
void makePlot();

};
