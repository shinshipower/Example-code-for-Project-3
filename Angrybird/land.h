#ifndef LAND_H
#define LAND_H

#include <gameitem.h>
#include <QGraphicsScene>

class Land : public GameItem
{
public:
    Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    //    QRectF boundingRect() const;
    //    void paint(QPainter *painter,
    //               const QStyleOptionGraphicsItem *option,
//                   QWidget *widget);
private:
    float ww;
    float hh;
};

#endif // LAND_H
