/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *cacheTable;
    QPushButton *pushButton;
    QLabel *cache_label;
    QCheckBox *checkBox;
    QLabel *label_2;
    QTextBrowser *textBrowser_2;
    QLabel *label_3;
    QTextBrowser *textBrowser_3;
    QLabel *label_4;
    QTextBrowser *textBrowser_4;
    QLabel *memory_label;
    QTableWidget *memoryTable;
    QTextEdit *inputMemory;
    QLabel *inputMemoryLabel;
    QLabel *inputValueLabel;
    QTextEdit *inputValue;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(100, 120, 501, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cacheTable = new QTableWidget(verticalLayoutWidget);
        cacheTable->setObjectName(QString::fromUtf8("cacheTable"));

        verticalLayout->addWidget(cacheTable);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(610, 690, 113, 32));
        pushButton->setAutoFillBackground(true);
        cache_label = new QLabel(centralwidget);
        cache_label->setObjectName(QString::fromUtf8("cache_label"));
        cache_label->setGeometry(QRect(100, 100, 91, 16));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(650, 70, 86, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 70, 71, 16));
        textBrowser_2 = new QTextBrowser(centralwidget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(200, 70, 51, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(260, 70, 91, 16));
        textBrowser_3 = new QTextBrowser(centralwidget);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(350, 70, 101, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(460, 70, 71, 16));
        textBrowser_4 = new QTextBrowser(centralwidget);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(530, 70, 111, 21));
        memory_label = new QLabel(centralwidget);
        memory_label->setObjectName(QString::fromUtf8("memory_label"));
        memory_label->setGeometry(QRect(620, 100, 91, 20));
        memoryTable = new QTableWidget(centralwidget);
        memoryTable->setObjectName(QString::fromUtf8("memoryTable"));
        memoryTable->setGeometry(QRect(620, 120, 151, 351));
        inputMemory = new QTextEdit(centralwidget);
        inputMemory->setObjectName(QString::fromUtf8("inputMemory"));
        inputMemory->setGeometry(QRect(150, 660, 104, 21));
        inputMemoryLabel = new QLabel(centralwidget);
        inputMemoryLabel->setObjectName(QString::fromUtf8("inputMemoryLabel"));
        inputMemoryLabel->setGeometry(QRect(90, 660, 59, 16));
        inputValueLabel = new QLabel(centralwidget);
        inputValueLabel->setObjectName(QString::fromUtf8("inputValueLabel"));
        inputValueLabel->setGeometry(QRect(90, 680, 59, 16));
        inputValue = new QTextEdit(centralwidget);
        inputValue->setObjectName(QString::fromUtf8("inputValue"));
        inputValue->setGeometry(QRect(150, 680, 104, 21));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 660, 113, 32));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(250, 680, 113, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "NextOrder", nullptr));
        cache_label->setText(QCoreApplication::translate("MainWindow", "cache view", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "L2 cache", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "time cycle", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Current order", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Next Order", nullptr));
        memory_label->setText(QCoreApplication::translate("MainWindow", "memory view", nullptr));
        inputMemoryLabel->setText(QCoreApplication::translate("MainWindow", "address", nullptr));
        inputValueLabel->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "read", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "write", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
