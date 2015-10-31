/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *staticTotalStatusAnalizer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *staticTotal;
    QLineEdit *lineEditTotal;
    QLabel *staticOk;
    QLineEdit *lineEditOk;
    QLabel *staticNok;
    QLineEdit *lineEditNok;
    QLabel *staticLogoValeo;
    QGridLayout *gridLayoutForStations;
    QGroupBox *groupBoxSt80;
    QGroupBox *groupBoxSt70;
    QGroupBox *groupBoxSt50;
    QGroupBox *groupBoxSt60;
    QGroupBox *groupBoxSt90;
    QGroupBox *groupBoxSt40;
    QGroupBox *groupBoxSt20;
    QGroupBox *groupBoxSt30;
    QGroupBox *groupBoxSt100;
    QGroupBox *groupBoxSt110;
    QGroupBox *groupBoxSt120;
    QGroupBox *groupBoxSt10;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *staticSt10Total;
    QLineEdit *lineEditSt10Total;
    QLabel *staticSt10Ok;
    QLineEdit *lineEditSt10Ok;
    QLabel *staticSt10Nok;
    QLineEdit *lineEditSt10Nok;
    QPlainTextEdit *plainTextEdit;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayoutSt10;
    QGroupBox *groupBoxSt10Status;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelSt10Status;
    QLabel *labelSt10Ico;
    QSpacerItem *horizontalSpacer_2;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1082, 935);
        MainWindow->setMinimumSize(QSize(1082, 935));
        MainWindow->setMaximumSize(QSize(1082, 935));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1025, 884));
        centralWidget->setMaximumSize(QSize(1082, 884));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        staticTotalStatusAnalizer = new QGroupBox(centralWidget);
        staticTotalStatusAnalizer->setObjectName(QStringLiteral("staticTotalStatusAnalizer"));
        staticTotalStatusAnalizer->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_2 = new QHBoxLayout(staticTotalStatusAnalizer);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 5, 5, 0);
        staticTotal = new QLabel(staticTotalStatusAnalizer);
        staticTotal->setObjectName(QStringLiteral("staticTotal"));

        horizontalLayout_2->addWidget(staticTotal);

        lineEditTotal = new QLineEdit(staticTotalStatusAnalizer);
        lineEditTotal->setObjectName(QStringLiteral("lineEditTotal"));
        lineEditTotal->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditTotal);

        staticOk = new QLabel(staticTotalStatusAnalizer);
        staticOk->setObjectName(QStringLiteral("staticOk"));

        horizontalLayout_2->addWidget(staticOk);

        lineEditOk = new QLineEdit(staticTotalStatusAnalizer);
        lineEditOk->setObjectName(QStringLiteral("lineEditOk"));
        lineEditOk->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditOk);

        staticNok = new QLabel(staticTotalStatusAnalizer);
        staticNok->setObjectName(QStringLiteral("staticNok"));

        horizontalLayout_2->addWidget(staticNok);

        lineEditNok = new QLineEdit(staticTotalStatusAnalizer);
        lineEditNok->setObjectName(QStringLiteral("lineEditNok"));
        lineEditNok->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditNok);


        horizontalLayout->addWidget(staticTotalStatusAnalizer);

        staticLogoValeo = new QLabel(centralWidget);
        staticLogoValeo->setObjectName(QStringLiteral("staticLogoValeo"));
        staticLogoValeo->setMinimumSize(QSize(200, 80));
        staticLogoValeo->setMaximumSize(QSize(200, 80));
        staticLogoValeo->setFrameShadow(QFrame::Plain);
        staticLogoValeo->setPixmap(QPixmap(QString::fromUtf8(":/ico/logovaleo.png")));

        horizontalLayout->addWidget(staticLogoValeo);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        gridLayoutForStations = new QGridLayout();
        gridLayoutForStations->setSpacing(0);
        gridLayoutForStations->setObjectName(QStringLiteral("gridLayoutForStations"));
        gridLayoutForStations->setSizeConstraint(QLayout::SetDefaultConstraint);
        groupBoxSt80 = new QGroupBox(centralWidget);
        groupBoxSt80->setObjectName(QStringLiteral("groupBoxSt80"));
        groupBoxSt80->setMinimumSize(QSize(360, 200));
        groupBoxSt80->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt80, 2, 2, 1, 1);

        groupBoxSt70 = new QGroupBox(centralWidget);
        groupBoxSt70->setObjectName(QStringLiteral("groupBoxSt70"));
        groupBoxSt70->setMinimumSize(QSize(360, 200));
        groupBoxSt70->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt70, 2, 1, 1, 1);

        groupBoxSt50 = new QGroupBox(centralWidget);
        groupBoxSt50->setObjectName(QStringLiteral("groupBoxSt50"));
        groupBoxSt50->setMinimumSize(QSize(360, 200));
        groupBoxSt50->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt50, 1, 1, 1, 1);

        groupBoxSt60 = new QGroupBox(centralWidget);
        groupBoxSt60->setObjectName(QStringLiteral("groupBoxSt60"));
        groupBoxSt60->setMinimumSize(QSize(360, 200));
        groupBoxSt60->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt60, 1, 3, 1, 1);

        groupBoxSt90 = new QGroupBox(centralWidget);
        groupBoxSt90->setObjectName(QStringLiteral("groupBoxSt90"));
        groupBoxSt90->setMinimumSize(QSize(360, 200));
        groupBoxSt90->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt90, 2, 3, 1, 1);

        groupBoxSt40 = new QGroupBox(centralWidget);
        groupBoxSt40->setObjectName(QStringLiteral("groupBoxSt40"));
        groupBoxSt40->setMinimumSize(QSize(360, 200));
        groupBoxSt40->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt40, 1, 2, 1, 1);

        groupBoxSt20 = new QGroupBox(centralWidget);
        groupBoxSt20->setObjectName(QStringLiteral("groupBoxSt20"));
        groupBoxSt20->setMinimumSize(QSize(360, 200));
        groupBoxSt20->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt20, 0, 2, 1, 1);

        groupBoxSt30 = new QGroupBox(centralWidget);
        groupBoxSt30->setObjectName(QStringLiteral("groupBoxSt30"));
        groupBoxSt30->setMinimumSize(QSize(360, 200));
        groupBoxSt30->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt30, 0, 3, 1, 1);

        groupBoxSt100 = new QGroupBox(centralWidget);
        groupBoxSt100->setObjectName(QStringLiteral("groupBoxSt100"));
        groupBoxSt100->setMinimumSize(QSize(360, 200));
        groupBoxSt100->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt100, 3, 1, 1, 1);

        groupBoxSt110 = new QGroupBox(centralWidget);
        groupBoxSt110->setObjectName(QStringLiteral("groupBoxSt110"));
        groupBoxSt110->setMinimumSize(QSize(360, 200));
        groupBoxSt110->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt110, 3, 2, 1, 1);

        groupBoxSt120 = new QGroupBox(centralWidget);
        groupBoxSt120->setObjectName(QStringLiteral("groupBoxSt120"));
        groupBoxSt120->setMinimumSize(QSize(360, 200));
        groupBoxSt120->setMaximumSize(QSize(360, 200));

        gridLayoutForStations->addWidget(groupBoxSt120, 3, 3, 1, 1);

        groupBoxSt10 = new QGroupBox(centralWidget);
        groupBoxSt10->setObjectName(QStringLiteral("groupBoxSt10"));
        groupBoxSt10->setMinimumSize(QSize(360, 200));
        groupBoxSt10->setMaximumSize(QSize(360, 200));
        groupBoxSt10->setFlat(false);
        gridLayout_2 = new QGridLayout(groupBoxSt10);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(groupBoxSt10);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFlat(true);
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(5, 0, 0, 0);
        staticSt10Total = new QLabel(groupBox);
        staticSt10Total->setObjectName(QStringLiteral("staticSt10Total"));

        horizontalLayout_6->addWidget(staticSt10Total);

        lineEditSt10Total = new QLineEdit(groupBox);
        lineEditSt10Total->setObjectName(QStringLiteral("lineEditSt10Total"));
        lineEditSt10Total->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditSt10Total);

        staticSt10Ok = new QLabel(groupBox);
        staticSt10Ok->setObjectName(QStringLiteral("staticSt10Ok"));

        horizontalLayout_6->addWidget(staticSt10Ok);

        lineEditSt10Ok = new QLineEdit(groupBox);
        lineEditSt10Ok->setObjectName(QStringLiteral("lineEditSt10Ok"));
        lineEditSt10Ok->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditSt10Ok);

        staticSt10Nok = new QLabel(groupBox);
        staticSt10Nok->setObjectName(QStringLiteral("staticSt10Nok"));

        horizontalLayout_6->addWidget(staticSt10Nok);

        lineEditSt10Nok = new QLineEdit(groupBox);
        lineEditSt10Nok->setObjectName(QStringLiteral("lineEditSt10Nok"));
        lineEditSt10Nok->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditSt10Nok);


        gridLayout_2->addWidget(groupBox, 2, 2, 1, 1);

        plainTextEdit = new QPlainTextEdit(groupBoxSt10);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout_2->addWidget(plainTextEdit, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayoutSt10 = new QGridLayout();
        gridLayoutSt10->setSpacing(0);
        gridLayoutSt10->setObjectName(QStringLiteral("gridLayoutSt10"));
        groupBoxSt10Status = new QGroupBox(groupBoxSt10);
        groupBoxSt10Status->setObjectName(QStringLiteral("groupBoxSt10Status"));
        groupBoxSt10Status->setFlat(true);
        horizontalLayout_3 = new QHBoxLayout(groupBoxSt10Status);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelSt10Status = new QLabel(groupBoxSt10Status);
        labelSt10Status->setObjectName(QStringLiteral("labelSt10Status"));

        horizontalLayout_3->addWidget(labelSt10Status);

        labelSt10Ico = new QLabel(groupBoxSt10Status);
        labelSt10Ico->setObjectName(QStringLiteral("labelSt10Ico"));
        labelSt10Ico->setMaximumSize(QSize(32, 32));

        horizontalLayout_3->addWidget(labelSt10Ico);


        gridLayoutSt10->addWidget(groupBoxSt10Status, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayoutSt10->addItem(horizontalSpacer_2, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayoutSt10, 0, 2, 2, 1);


        gridLayoutForStations->addWidget(groupBoxSt10, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayoutForStations, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1082, 26));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        staticTotalStatusAnalizer->setTitle(QApplication::translate("MainWindow", "Operations", 0));
        staticTotal->setText(QApplication::translate("MainWindow", "Total:", 0));
        staticOk->setText(QApplication::translate("MainWindow", "OK:", 0));
        staticNok->setText(QApplication::translate("MainWindow", "NOK:", 0));
        staticLogoValeo->setText(QString());
        groupBoxSt80->setTitle(QApplication::translate("MainWindow", "Station 80", 0));
        groupBoxSt70->setTitle(QApplication::translate("MainWindow", "Station 70", 0));
        groupBoxSt50->setTitle(QApplication::translate("MainWindow", "Station 40", 0));
        groupBoxSt60->setTitle(QApplication::translate("MainWindow", "Station 60", 0));
        groupBoxSt90->setTitle(QApplication::translate("MainWindow", "Station 90", 0));
        groupBoxSt40->setTitle(QApplication::translate("MainWindow", "Station 50", 0));
        groupBoxSt20->setTitle(QApplication::translate("MainWindow", "Station 20", 0));
        groupBoxSt30->setTitle(QApplication::translate("MainWindow", "Station 30", 0));
        groupBoxSt100->setTitle(QApplication::translate("MainWindow", "Station 100", 0));
        groupBoxSt110->setTitle(QApplication::translate("MainWindow", "Station 110", 0));
        groupBoxSt120->setTitle(QApplication::translate("MainWindow", "Station 120", 0));
        groupBoxSt10->setTitle(QApplication::translate("MainWindow", "Station 10", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Operations", 0));
        staticSt10Total->setText(QApplication::translate("MainWindow", "Total:", 0));
        staticSt10Ok->setText(QApplication::translate("MainWindow", "OK:", 0));
        staticSt10Nok->setText(QApplication::translate("MainWindow", "NOK:", 0));
        groupBoxSt10Status->setTitle(QApplication::translate("MainWindow", "Status", 0));
        labelSt10Status->setText(QApplication::translate("MainWindow", "connection status", 0));
        labelSt10Ico->setText(QApplication::translate("MainWindow", "ico", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
