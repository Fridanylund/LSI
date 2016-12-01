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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_LSIProjectGUIClass
{
public:
    QWidget *centralWidget;
    QLabel *button_test;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *createROIButton;
    QPushButton *removeROIButton;
    QLabel *videoLabel;
    QTabWidget *settings_patientInfo;
    QWidget *Calibration;
    QPushButton *CalibrateMoving_Button;
    QPushButton *CalibrateStill_Button;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QPushButton *Dark_Button;
    QPushButton *AmbL_Button;
    QWidget *settings;
    QSpinBox *LASCAarea;
    QLabel *LASCA_label;
    QLabel *exposure_label;
    QDoubleSpinBox *exposuretime;
    QLabel *error_LASCA_label;
    QLabel *label;
    QSpinBox *spinBox;
    QPushButton *Save_Im;
    QCheckBox *checkBox;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QWidget *patientinformation;
    QLabel *genderLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *patientComments;
    QLineEdit *PatientGender;
    QLineEdit *patientName;
    QLineEdit *patientAge;
    QLabel *nameLabel;
    QLabel *ageLabel;
    QLabel *commentsLabel;
    QCustomPlot *customPlot;
    QScrollBar *horizontalScrollBar;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QListWidget *listROI;
    QPushButton *laserButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LSIProjectGUIClass)
    {
        if (LSIProjectGUIClass->objectName().isEmpty())
            LSIProjectGUIClass->setObjectName(QStringLiteral("LSIProjectGUIClass"));
        LSIProjectGUIClass->resize(1246, 704);
        centralWidget = new QWidget(LSIProjectGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(17, 132, 255);"));
        button_test = new QLabel(centralWidget);
        button_test->setObjectName(QStringLiteral("button_test"));
        button_test->setGeometry(QRect(740, 20, 91, 31));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(720, 80, 141, 61));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI Light"));
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        startButton->setFont(font);
        startButton->setStyleSheet(QLatin1String("font: 75 11pt \"Segoe UI Light\";\n"
"background-color: rgb(150, 223, 111);"));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(720, 160, 141, 61));
        stopButton->setStyleSheet(QLatin1String("background-color: rgb(255, 137, 58);\n"
"font: 75 11pt \"Segoe UI Light\";"));
        createROIButton = new QPushButton(centralWidget);
        createROIButton->setObjectName(QStringLiteral("createROIButton"));
        createROIButton->setGeometry(QRect(720, 240, 141, 61));
        createROIButton->setStyleSheet(QLatin1String("background-color: rgb(170, 85, 127);\n"
"font: 75 11pt \"Segoe UI Light\";"));
        removeROIButton = new QPushButton(centralWidget);
        removeROIButton->setObjectName(QStringLiteral("removeROIButton"));
        removeROIButton->setGeometry(QRect(720, 320, 141, 61));
        removeROIButton->setStyleSheet(QLatin1String("background-color: rgb(255, 170, 255);\n"
"font: 75 11pt \"Segoe UI Light\";"));
        videoLabel = new QLabel(centralWidget);
        videoLabel->setObjectName(QStringLiteral("videoLabel"));
        videoLabel->setGeometry(QRect(40, 10, 640, 480));
        videoLabel->setStyleSheet(QStringLiteral("border-color: rgb(118, 111, 120);"));
        settings_patientInfo = new QTabWidget(centralWidget);
        settings_patientInfo->setObjectName(QStringLiteral("settings_patientInfo"));
        settings_patientInfo->setGeometry(QRect(900, 10, 341, 641));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI Light"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        settings_patientInfo->setFont(font1);
        settings_patientInfo->setStyleSheet(QLatin1String("background-color: rgb(112, 112, 112);\n"
"border-color: rgb(34, 34, 34);"));
        settings_patientInfo->setTabShape(QTabWidget::Rounded);
        settings_patientInfo->setIconSize(QSize(20, 20));
        settings_patientInfo->setMovable(true);
        Calibration = new QWidget();
        Calibration->setObjectName(QStringLiteral("Calibration"));
        CalibrateMoving_Button = new QPushButton(Calibration);
        CalibrateMoving_Button->setObjectName(QStringLiteral("CalibrateMoving_Button"));
        CalibrateMoving_Button->setGeometry(QRect(80, 210, 171, 41));
        CalibrateMoving_Button->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
"background-color: rgb(135, 68, 115);"));
        CalibrateStill_Button = new QPushButton(Calibration);
        CalibrateStill_Button->setObjectName(QStringLiteral("CalibrateStill_Button"));
        CalibrateStill_Button->setGeometry(QRect(80, 270, 171, 41));
        CalibrateStill_Button->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
"background-color: rgb(135, 68, 115);"));
        textBrowser = new QTextBrowser(Calibration);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 321, 191));
        textBrowser->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
""));
        pushButton = new QPushButton(Calibration);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 520, 171, 51));
        pushButton->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
"background-color: rgb(17, 61, 118);"));
        Dark_Button = new QPushButton(Calibration);
        Dark_Button->setObjectName(QStringLiteral("Dark_Button"));
        Dark_Button->setGeometry(QRect(70, 360, 201, 41));
        Dark_Button->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
"background-color: rgb(64, 140, 255);"));
        AmbL_Button = new QPushButton(Calibration);
        AmbL_Button->setObjectName(QStringLiteral("AmbL_Button"));
        AmbL_Button->setGeometry(QRect(70, 420, 201, 41));
        AmbL_Button->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
"background-color: rgb(64, 140, 255);"));
        settings_patientInfo->addTab(Calibration, QString());
        settings = new QWidget();
        settings->setObjectName(QStringLiteral("settings"));
        LASCAarea = new QSpinBox(settings);
        LASCAarea->setObjectName(QStringLiteral("LASCAarea"));
        LASCAarea->setGeometry(QRect(190, 40, 71, 51));
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI Light"));
        font2.setPointSize(13);
        font2.setBold(false);
        font2.setWeight(50);
        LASCAarea->setFont(font2);
        LASCAarea->setStyleSheet(QLatin1String("background-color: rgb(17, 132, 255);\n"
"border-color: rgb(56, 56, 56);"));
        LASCAarea->setSingleStep(2);
        LASCAarea->setValue(5);
        LASCA_label = new QLabel(settings);
        LASCA_label->setObjectName(QStringLiteral("LASCA_label"));
        LASCA_label->setGeometry(QRect(50, 60, 91, 21));
        LASCA_label->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        exposure_label = new QLabel(settings);
        exposure_label->setObjectName(QStringLiteral("exposure_label"));
        exposure_label->setGeometry(QRect(60, 230, 111, 21));
        exposure_label->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        exposuretime = new QDoubleSpinBox(settings);
        exposuretime->setObjectName(QStringLiteral("exposuretime"));
        exposuretime->setGeometry(QRect(190, 210, 71, 51));
        exposuretime->setFont(font2);
        exposuretime->setStyleSheet(QLatin1String("background-color: rgb(17, 132, 255);\n"
"border-color: rgb(56, 56, 56);"));
        exposuretime->setDecimals(0);
        exposuretime->setMinimum(1);
        exposuretime->setValue(5);
        error_LASCA_label = new QLabel(settings);
        error_LASCA_label->setObjectName(QStringLiteral("error_LASCA_label"));
        error_LASCA_label->setGeometry(QRect(50, 100, 231, 21));
        error_LASCA_label->setStyleSheet(QStringLiteral("color: rgb(186, 1, 35);"));
        label = new QLabel(settings);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 290, 121, 31));
        label->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        spinBox = new QSpinBox(settings);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(190, 280, 71, 51));
        QFont font3;
        font3.setFamily(QStringLiteral("Segoe UI Light"));
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        spinBox->setFont(font3);
        spinBox->setStyleSheet(QLatin1String("background-color: rgb(17, 132, 255);\n"
"border-color: rgb(56, 56, 56);"));
        spinBox->setMaximum(300);
        spinBox->setValue(20);
        Save_Im = new QPushButton(settings);
        Save_Im->setObjectName(QStringLiteral("Save_Im"));
        Save_Im->setGeometry(QRect(70, 530, 201, 41));
        Save_Im->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
"\n"
"background-color: rgb(64, 140, 255);"));
        checkBox = new QCheckBox(settings);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(50, 130, 231, 31));
        checkBox->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
""));
        checkBox->setChecked(true);
        label_2 = new QLabel(settings);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 370, 91, 21));
        label_2->setStyleSheet(QLatin1String("font: 75 12pt \"Segoe UI Light\";\n"
""));
        spinBox_2 = new QSpinBox(settings);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(190, 350, 71, 51));
        spinBox_2->setStyleSheet(QLatin1String("background-color: rgb(17, 132, 255);\n"
"font: 75 12pt \"Segoe UI Light\";\n"
"border-color: rgb(56, 56, 56);"));
        settings_patientInfo->addTab(settings, QString());
        patientinformation = new QWidget();
        patientinformation->setObjectName(QStringLiteral("patientinformation"));
        genderLabel = new QLabel(patientinformation);
        genderLabel->setObjectName(QStringLiteral("genderLabel"));
        genderLabel->setGeometry(QRect(70, 180, 61, 20));
        genderLabel->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        scrollArea = new QScrollArea(patientinformation);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(70, 320, 231, 221));
        scrollArea->setStyleSheet(QStringLiteral("background-color: rgb(17, 132, 255);"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 229, 219));
        patientComments = new QPlainTextEdit(scrollAreaWidgetContents);
        patientComments->setObjectName(QStringLiteral("patientComments"));
        patientComments->setGeometry(QRect(10, 10, 211, 201));
        patientComments->setStyleSheet(QStringLiteral("background-color: rgb(241, 241, 241);"));
        scrollArea->setWidget(scrollAreaWidgetContents);
        PatientGender = new QLineEdit(patientinformation);
        PatientGender->setObjectName(QStringLiteral("PatientGender"));
        PatientGender->setGeometry(QRect(130, 180, 121, 20));
        PatientGender->setStyleSheet(QStringLiteral("background-color: rgb(241, 241, 241);"));
        patientName = new QLineEdit(patientinformation);
        patientName->setObjectName(QStringLiteral("patientName"));
        patientName->setGeometry(QRect(130, 99, 121, 21));
        patientName->setStyleSheet(QStringLiteral("background-color: rgb(241, 241, 241);"));
        patientAge = new QLineEdit(patientinformation);
        patientAge->setObjectName(QStringLiteral("patientAge"));
        patientAge->setGeometry(QRect(130, 140, 121, 20));
        patientAge->setStyleSheet(QStringLiteral("background-color: rgb(241, 241, 241);"));
        nameLabel = new QLabel(patientinformation);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(70, 100, 51, 20));
        nameLabel->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        ageLabel = new QLabel(patientinformation);
        ageLabel->setObjectName(QStringLiteral("ageLabel"));
        ageLabel->setGeometry(QRect(80, 140, 31, 21));
        ageLabel->setStyleSheet(QStringLiteral("font: 75 12pt \"Segoe UI Light\";"));
        commentsLabel = new QLabel(patientinformation);
        commentsLabel->setObjectName(QStringLiteral("commentsLabel"));
        commentsLabel->setGeometry(QRect(80, 280, 191, 31));
        commentsLabel->setStyleSheet(QStringLiteral("font: 75 13pt \"Segoe UI Light\";"));
        settings_patientInfo->addTab(patientinformation, QString());
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(120, 500, 431, 161));
        horizontalScrollBar = new QScrollBar(customPlot);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(0, 140, 431, 16));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(720, 420, 141, 121));
        scrollArea_2->setStyleSheet(QStringLiteral("background-color: rgb(71, 71, 71);"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 139, 119));
        listROI = new QListWidget(scrollAreaWidgetContents_2);
        listROI->setObjectName(QStringLiteral("listROI"));
        listROI->setGeometry(QRect(10, 10, 121, 101));
        QPalette palette;
        QBrush brush(QColor(197, 197, 197, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush1(QColor(189, 189, 189, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        QBrush brush2(QColor(51, 153, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush2);
        listROI->setPalette(palette);
        listROI->setStyleSheet(QStringLiteral("background-color: rgb(197, 197, 197);"));
        listROI->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        listROI->setAlternatingRowColors(true);
        listROI->setSelectionRectVisible(true);
        listROI->setSortingEnabled(false);
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        laserButton = new QPushButton(centralWidget);
        laserButton->setObjectName(QStringLiteral("laserButton"));
        laserButton->setGeometry(QRect(720, 560, 141, 41));
        laserButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 71, 15);"));
        LSIProjectGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LSIProjectGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1246, 21));
        LSIProjectGUIClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(LSIProjectGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LSIProjectGUIClass->setStatusBar(statusBar);

        retranslateUi(LSIProjectGUIClass);

        settings_patientInfo->setCurrentIndex(0);
        listROI->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(LSIProjectGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *LSIProjectGUIClass)
    {
        LSIProjectGUIClass->setWindowTitle(QApplication::translate("LSIProjectGUIClass", "LSIProjectGUI", 0));
        button_test->setText(QString());
        startButton->setText(QApplication::translate("LSIProjectGUIClass", "Start", 0));
        stopButton->setText(QApplication::translate("LSIProjectGUIClass", "Stop", 0));
        createROIButton->setText(QApplication::translate("LSIProjectGUIClass", "create ROI", 0));
        removeROIButton->setText(QApplication::translate("LSIProjectGUIClass", "remove ROI", 0));
        videoLabel->setText(QApplication::translate("LSIProjectGUIClass", "The video will soon be displayed...", 0));
        CalibrateMoving_Button->setText(QApplication::translate("LSIProjectGUIClass", "Take moving image", 0));
        CalibrateStill_Button->setText(QApplication::translate("LSIProjectGUIClass", "Take Still Image", 0));
        textBrowser->setHtml(QApplication::translate("LSIProjectGUIClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI Light'; font-size:12pt; font-weight:72; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Press the purple buttons to get new normalization values!</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Press the blue buttons if the dark image or the ambient light image needs to be updated!</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-i"
                        "ndent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The dark blue button will reset the calibration to the standard values!</p></body></html>", 0));
        pushButton->setText(QApplication::translate("LSIProjectGUIClass", "Reset ", 0));
        Dark_Button->setText(QApplication::translate("LSIProjectGUIClass", "Take Dark Images", 0));
        AmbL_Button->setText(QApplication::translate("LSIProjectGUIClass", "Take Ambient light Image", 0));
        settings_patientInfo->setTabText(settings_patientInfo->indexOf(Calibration), QApplication::translate("LSIProjectGUIClass", "Calibration", 0));
        LASCA_label->setText(QApplication::translate("LSIProjectGUIClass", "LASCA area:", 0));
        exposure_label->setText(QApplication::translate("LSIProjectGUIClass", "Exposure time:", 0));
        error_LASCA_label->setText(QString());
        label->setText(QApplication::translate("LSIProjectGUIClass", "New Base image:", 0));
        Save_Im->setText(QApplication::translate("LSIProjectGUIClass", "Save Image", 0));
        checkBox->setText(QApplication::translate("LSIProjectGUIClass", "Enhanced contrast calculations", 0));
        label_2->setText(QApplication::translate("LSIProjectGUIClass", "Skalfaktor: ", 0));
        settings_patientInfo->setTabText(settings_patientInfo->indexOf(settings), QApplication::translate("LSIProjectGUIClass", "Settings", 0));
        genderLabel->setText(QApplication::translate("LSIProjectGUIClass", "Gender:", 0));
        nameLabel->setText(QApplication::translate("LSIProjectGUIClass", "Name:", 0));
        ageLabel->setText(QApplication::translate("LSIProjectGUIClass", "Age:", 0));
        commentsLabel->setText(QApplication::translate("LSIProjectGUIClass", "Write patient comments:", 0));
        settings_patientInfo->setTabText(settings_patientInfo->indexOf(patientinformation), QApplication::translate("LSIProjectGUIClass", "Patient info", 0));
        laserButton->setText(QApplication::translate("LSIProjectGUIClass", "Turn on laser", 0));
    } // retranslateUi

};

namespace Ui {
    class LSIProjectGUIClass: public Ui_LSIProjectGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LSIPROJECTGUI_H
