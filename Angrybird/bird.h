#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int btype,bool dtype=true);
    void setLinearVelocity(b2Vec2 velocity);
    b2Vec2 get_Position();
    //QRectF boundingRect() const;
    //void paint(QPainter *painter,
    //               const QStyleOptionGraphicsItem *option,
    //               QWidget *widget);
    //void SP();
            int birdtype;
            b2Vec2 speed;
public slots:
    void paint();
private:
        float Radius;
        bool shooted;



};

#endif // BIRD_H
