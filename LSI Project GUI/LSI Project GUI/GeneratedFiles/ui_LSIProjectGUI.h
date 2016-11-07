/********************************************************************************
** Form generated from reading UI file 'LSIProjectGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LSIPROJECTGUI_H
#define UI_LSIPROJECTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LSIProjectGUIClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *im_show;
    QLabel *label_2;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *createROIButton;
    QPushButton *removeROIButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *patientComments;
    QLabel *commentsLabel;
    QLineEdit *patientName;
    QLineEdit *patientAge;
    QLineEdit *PatientGender;
    QLabel *nameLabel;
    QLabel *label;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LSIProjectGUIClass)
    {
        if (LSIProjectGUIClass->objectName().isEmpty())
            LSIProjectGUIClass->setObjectName(QStringLiteral("LSIProjectGUIClass"));
        LSIProjectGUIClass->resize(928, 557);
        centralWidget = new QWidget(LSIProjectGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(17, 132, 255);"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 20, 171, 71));
        im_show = new QLabel(centralWidget);
        im_show->setObjectName(QStringLiteral("im_show"));
        im_show->setEnabled(true);
        im_show->setGeometry(QRect(50, 100, 191, 171));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 270, 111, 61));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(410, 80, 141, 61));
        startButton->setStyleSheet(QLatin1String("font: 75 11pt \"Segoe UI Light\";\n"
"background-color: rgb(150, 223, 111);"));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(410, 150, 141, 61));
        stopButton->setStyleSheet(QLatin1String("background-color: rgb(255, 137, 58);\n"
"font: 75 11pt \"Segoe UI Light\";"));
        createROIButton = new QPushButton(centralWidget);
        createROIButton->setObjectName(QStringLiteral("createROIButton"));
        createROIButton->setGeometry(QRect(410, 220, 141, 61));
        createROIButton->setStyleSheet(QLatin1String("background-color: rgb(170, 85, 127);\n"
"font: 75 11pt \"Segoe UI Light\";"));
        removeROIButton = new QPushButton(centralWidget);
        removeROIButton->setObjectName(QStringLiteral("removeROIButton"));
        removeROIButton->setGeometry(QRect(410, 300, 141, 61));
        removeROIButton->setStyleSheet(QLatin1String("background-color: rgb(255, 170, 255);\n"
"font: 75 11pt \"Segoe UI Light\";"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(620, 200, 191, 161));
        scrollArea->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 189, 159));
        patientComments = new QPlainTextEdit(scrollAreaWidgetContents);
        patientComments->setObjectName(QStringLiteral("patientComments"));
        patientComments->setGeometry(QRect(10, 10, 171, 141));
        patientComments->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 255);"));
        scrollArea->setWidget(scrollAreaWidgetContents);
        commentsLabel = new QLabel(centralWidget);
        commentsLabel->setObjectName(QStringLiteral("commentsLabel"));
        commentsLabel->setGeometry(QRect(620, 180, 191, 16));
        commentsLabel->setStyleSheet(QStringLiteral("font: 75 13pt \"Segoe UI Light\";"));
        patientName = new QLineEdit(centralWidget);
        patientName->setObjectName(QStringLiteral("patientName"));
        patientName->setGeometry(QRect(700, 80, 113, 20));
        patientName->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 255);"));
        patientAge = new QLineEdit(centralWidget);
        patientAge->setObjectName(QStringLiteral("patientAge"));
        patientAge->setGeometry(QRect(700, 110, 113, 20));
        patientAge->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 255);"));
        PatientGender = new QLineEdit(centralWidget);
        PatientGender->setObjectName(QStringLiteral("PatientGender"));
        PatientGender->setGeometry(QRect(700, 140, 113, 20));
        PatientGender->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 255);"));
        nameLabel = new QLabel(centralWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(646, 80, 51, 20));
        nameLabel->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(660, 110, 31, 21));
        label->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(640, 140, 61, 20));
        label_3->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        LSIProjectGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LSIProjectGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 928, 21));
        LSIProjectGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LSIProjectGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LSIProjectGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LSIProjectGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LSIProjectGUIClass->setStatusBar(statusBar);

        retranslateUi(LSIProjectGUIClass);

        QMetaObject::connectSlotsByName(LSIProjectGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *LSIProjectGUIClass)
    {
        LSIProjectGUIClass->setWindowTitle(QApplication::translate("LSIProjectGUIClass", "LSIProjectGUI", 0));
        pushButton->setText(QApplication::translate("LSIProjectGUIClass", "Push Me!!", 0));
        im_show->setText(QApplication::translate("LSIProjectGUIClass", "Somthing might happen here!", 0));
        label_2->setText(QString());
        startButton->setText(QApplication::translate("LSIProjectGUIClass", "Start", 0));
        stopButton->setText(QApplication::translate("LSIProjectGUIClass", "Stop", 0));
        createROIButton->setText(QApplication::translate("LSIProjectGUIClass", "create ROI", 0));
        removeROIButton->setText(QApplication::translate("LSIProjectGUIClass", "remove ROI", 0));
        commentsLabel->setText(QApplication::translate("LSIProjectGUIClass", "Write patient comments:", 0));
        nameLabel->setText(QApplication::translate("LSIProjectGUIClass", "Name:", 0));
        label->setText(QApplication::translate("LSIProjectGUIClass", "Age:", 0));
        label_3->setText(QApplication::translate("LSIProjectGUIClass", "Gender:", 0));
    } // retranslateUi

};

namespace Ui {
    class LSIProjectGUIClass: public Ui_LSIProjectGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LSIPROJECTGUI_H
