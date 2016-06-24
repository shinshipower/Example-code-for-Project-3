#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <Box2D/Box2D.h>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <iostream>
#include <y_wood.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <cstdlib>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void closeEvent(QCloseEvent *);
    void shootBird(float x, float y, float vx, float vy, int birdType);
    bool eventFilter(QObject *,QEvent *event);
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void on_EXIT_released();

    void on_START_released();

    void tick();
    // For debug slot
    void QUITSLOT();

    void regen();


    void on_pushButton_pressed();

protected:
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::Widget *ui;
    QTimer timer;
    QTimer Re_gen;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QGraphicsPixmapItem YY;
    float startX;
    float startY;
    QPoint startMouse;
    QPoint trackingMouse;
    bool clicked;
    Bird *CurrentBird;
    Bird *FlyingBird;
    Bird *Fake;
    int current_type;
    bool nobird;
};


#endif // WIDGET_H
