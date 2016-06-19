#ifndef Y_WOOD_H
#define Y_WOOD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Y_wood : public GameItem
{

public:
    Y_wood(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // Y_WOOD_H
