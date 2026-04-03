/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *panelAnimali;
    QVBoxLayout *vLayoutAnimali;
    QLabel *labelAnimali;
    QListWidget *listAnimali;
    QHBoxLayout *hLayoutBottoniAnimali;
    QPushButton *buttonAggiungiAnimale;
    QPushButton *buttonEliminaAnimale;
    QWidget *panelDettagli;
    QVBoxLayout *vLayoutDettagli;
    QLabel *labelDettagli;
    QLabel *labelNome;
    QLineEdit *lineEditNome;
    QLabel *labelSpecie;
    QLineEdit *lineEditSpecie;
    QLabel *labelRazza;
    QLineEdit *lineEditRazza;
    QLabel *labelNascita;
    QLineEdit *lineEditNascita;
    QLabel *labelPeso;
    QLineEdit *lineEditPeso;
    QSpacerItem *spacerDettagli;
    QHBoxLayout *hLayoutBottoniDettagli;
    QPushButton *buttonModificaAnimale;
    QWidget *panelEventi;
    QVBoxLayout *vLayoutEventi;
    QLabel *labelEventi;
    QListWidget *listEventi;
    QLabel *labelDettaglioEvento;
    QTextEdit *textDettaglioEvento;
    QHBoxLayout *hLayoutBottoniEventi;
    QPushButton *buttonAggiungiEvento;
    QPushButton *buttonModificaEvento;
    QPushButton *buttonEliminaEvento;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        panelAnimali = new QWidget(splitter);
        panelAnimali->setObjectName("panelAnimali");
        vLayoutAnimali = new QVBoxLayout(panelAnimali);
        vLayoutAnimali->setObjectName("vLayoutAnimali");
        vLayoutAnimali->setContentsMargins(0, 0, 0, 0);
        labelAnimali = new QLabel(panelAnimali);
        labelAnimali->setObjectName("labelAnimali");
        QFont font;
        font.setBold(true);
        labelAnimali->setFont(font);

        vLayoutAnimali->addWidget(labelAnimali);

        listAnimali = new QListWidget(panelAnimali);
        listAnimali->setObjectName("listAnimali");

        vLayoutAnimali->addWidget(listAnimali);

        hLayoutBottoniAnimali = new QHBoxLayout();
        hLayoutBottoniAnimali->setObjectName("hLayoutBottoniAnimali");
        buttonAggiungiAnimale = new QPushButton(panelAnimali);
        buttonAggiungiAnimale->setObjectName("buttonAggiungiAnimale");

        hLayoutBottoniAnimali->addWidget(buttonAggiungiAnimale);

        buttonEliminaAnimale = new QPushButton(panelAnimali);
        buttonEliminaAnimale->setObjectName("buttonEliminaAnimale");

        hLayoutBottoniAnimali->addWidget(buttonEliminaAnimale);


        vLayoutAnimali->addLayout(hLayoutBottoniAnimali);

        splitter->addWidget(panelAnimali);
        panelDettagli = new QWidget(splitter);
        panelDettagli->setObjectName("panelDettagli");
        vLayoutDettagli = new QVBoxLayout(panelDettagli);
        vLayoutDettagli->setObjectName("vLayoutDettagli");
        vLayoutDettagli->setContentsMargins(0, 0, 0, 0);
        labelDettagli = new QLabel(panelDettagli);
        labelDettagli->setObjectName("labelDettagli");
        labelDettagli->setFont(font);

        vLayoutDettagli->addWidget(labelDettagli);

        labelNome = new QLabel(panelDettagli);
        labelNome->setObjectName("labelNome");

        vLayoutDettagli->addWidget(labelNome);

        lineEditNome = new QLineEdit(panelDettagli);
        lineEditNome->setObjectName("lineEditNome");
        lineEditNome->setReadOnly(true);

        vLayoutDettagli->addWidget(lineEditNome);

        labelSpecie = new QLabel(panelDettagli);
        labelSpecie->setObjectName("labelSpecie");

        vLayoutDettagli->addWidget(labelSpecie);

        lineEditSpecie = new QLineEdit(panelDettagli);
        lineEditSpecie->setObjectName("lineEditSpecie");
        lineEditSpecie->setReadOnly(true);

        vLayoutDettagli->addWidget(lineEditSpecie);

        labelRazza = new QLabel(panelDettagli);
        labelRazza->setObjectName("labelRazza");

        vLayoutDettagli->addWidget(labelRazza);

        lineEditRazza = new QLineEdit(panelDettagli);
        lineEditRazza->setObjectName("lineEditRazza");
        lineEditRazza->setReadOnly(true);

        vLayoutDettagli->addWidget(lineEditRazza);

        labelNascita = new QLabel(panelDettagli);
        labelNascita->setObjectName("labelNascita");

        vLayoutDettagli->addWidget(labelNascita);

        lineEditNascita = new QLineEdit(panelDettagli);
        lineEditNascita->setObjectName("lineEditNascita");
        lineEditNascita->setReadOnly(true);

        vLayoutDettagli->addWidget(lineEditNascita);

        labelPeso = new QLabel(panelDettagli);
        labelPeso->setObjectName("labelPeso");

        vLayoutDettagli->addWidget(labelPeso);

        lineEditPeso = new QLineEdit(panelDettagli);
        lineEditPeso->setObjectName("lineEditPeso");
        lineEditPeso->setReadOnly(true);

        vLayoutDettagli->addWidget(lineEditPeso);

        spacerDettagli = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vLayoutDettagli->addItem(spacerDettagli);

        hLayoutBottoniDettagli = new QHBoxLayout();
        hLayoutBottoniDettagli->setObjectName("hLayoutBottoniDettagli");
        buttonModificaAnimale = new QPushButton(panelDettagli);
        buttonModificaAnimale->setObjectName("buttonModificaAnimale");

        hLayoutBottoniDettagli->addWidget(buttonModificaAnimale);


        vLayoutDettagli->addLayout(hLayoutBottoniDettagli);

        splitter->addWidget(panelDettagli);
        panelEventi = new QWidget(splitter);
        panelEventi->setObjectName("panelEventi");
        vLayoutEventi = new QVBoxLayout(panelEventi);
        vLayoutEventi->setObjectName("vLayoutEventi");
        vLayoutEventi->setContentsMargins(0, 0, 0, 0);
        labelEventi = new QLabel(panelEventi);
        labelEventi->setObjectName("labelEventi");
        labelEventi->setFont(font);

        vLayoutEventi->addWidget(labelEventi);

        listEventi = new QListWidget(panelEventi);
        listEventi->setObjectName("listEventi");

        vLayoutEventi->addWidget(listEventi);

        labelDettaglioEvento = new QLabel(panelEventi);
        labelDettaglioEvento->setObjectName("labelDettaglioEvento");
        labelDettaglioEvento->setFont(font);

        vLayoutEventi->addWidget(labelDettaglioEvento);

        textDettaglioEvento = new QTextEdit(panelEventi);
        textDettaglioEvento->setObjectName("textDettaglioEvento");
        textDettaglioEvento->setReadOnly(true);

        vLayoutEventi->addWidget(textDettaglioEvento);

        hLayoutBottoniEventi = new QHBoxLayout();
        hLayoutBottoniEventi->setObjectName("hLayoutBottoniEventi");
        buttonAggiungiEvento = new QPushButton(panelEventi);
        buttonAggiungiEvento->setObjectName("buttonAggiungiEvento");

        hLayoutBottoniEventi->addWidget(buttonAggiungiEvento);

        buttonModificaEvento = new QPushButton(panelEventi);
        buttonModificaEvento->setObjectName("buttonModificaEvento");

        hLayoutBottoniEventi->addWidget(buttonModificaEvento);

        buttonEliminaEvento = new QPushButton(panelEventi);
        buttonEliminaEvento->setObjectName("buttonEliminaEvento");

        hLayoutBottoniEventi->addWidget(buttonEliminaEvento);


        vLayoutEventi->addLayout(hLayoutBottoniEventi);

        splitter->addWidget(panelEventi);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Diario Animali Domestici", nullptr));
        labelAnimali->setText(QCoreApplication::translate("MainWindow", "Animali", nullptr));
        buttonAggiungiAnimale->setText(QCoreApplication::translate("MainWindow", "+ Aggiungi", nullptr));
        buttonEliminaAnimale->setText(QCoreApplication::translate("MainWindow", "Elimina", nullptr));
        labelDettagli->setText(QCoreApplication::translate("MainWindow", "Dettagli Animale", nullptr));
        labelNome->setText(QCoreApplication::translate("MainWindow", "Nome:", nullptr));
        labelSpecie->setText(QCoreApplication::translate("MainWindow", "Specie:", nullptr));
        labelRazza->setText(QCoreApplication::translate("MainWindow", "Razza:", nullptr));
        labelNascita->setText(QCoreApplication::translate("MainWindow", "Data di nascita:", nullptr));
        labelPeso->setText(QCoreApplication::translate("MainWindow", "Peso (kg):", nullptr));
        buttonModificaAnimale->setText(QCoreApplication::translate("MainWindow", "Modifica", nullptr));
        labelEventi->setText(QCoreApplication::translate("MainWindow", "Eventi", nullptr));
        labelDettaglioEvento->setText(QCoreApplication::translate("MainWindow", "Dettaglio evento", nullptr));
        buttonAggiungiEvento->setText(QCoreApplication::translate("MainWindow", "+ Aggiungi", nullptr));
        buttonModificaEvento->setText(QCoreApplication::translate("MainWindow", "Modifica", nullptr));
        buttonEliminaEvento->setText(QCoreApplication::translate("MainWindow", "Elimina", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
