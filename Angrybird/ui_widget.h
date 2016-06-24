/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *welcome;
    QLabel *BG;
    QPushButton *START;
    QPushButton *EXIT;
    QWidget *game;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1280, 720);
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1280, 720));
        stackedWidget->setLineWidth(0);
        welcome = new QWidget();
        welcome->setObjectName(QStringLiteral("welcome"));
        BG = new QLabel(welcome);
        BG->setObjectName(QStringLiteral("BG"));
        BG->setGeometry(QRect(0, 0, 1280, 720));
        BG->setPixmap(QPixmap(QString::fromUtf8("title.jpg")));
        BG->setScaledContents(true);
        START = new QPushButton(welcome);
        START->setObjectName(QStringLiteral("START"));
        START->setGeometry(QRect(230, 630, 221, 71));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font.setPointSize(24);
        START->setFont(font);
        EXIT = new QPushButton(welcome);
        EXIT->setObjectName(QStringLiteral("EXIT"));
        EXIT->setGeometry(QRect(870, 630, 221, 71));
        EXIT->setFont(font);
        stackedWidget->addWidget(welcome);
        game = new QWidget();
        game->setObjectName(QStringLiteral("game"));
        graphicsView = new QGraphicsView(game);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 1280, 720));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        graphicsView->setBackgroundBrush(brush);
        pushButton = new QPushButton(game);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 95, 31));
        stackedWidget->addWidget(game);

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        BG->setText(QString());
        START->setText(QApplication::translate("Widget", "Start", 0));
        EXIT->setText(QApplication::translate("Widget", "Exit", 0));
        pushButton->setText(QApplication::translate("Widget", "Return", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
