#include "y_wood.h"

Y_wood::Y_wood(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{

    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.type=b2_staticBody;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    //b2PolygonShape bodyBox;
    //bodyBox.SetAsBox(w,h);
    //g_body->CreateFixture(&bodyBox,0);

    scene->addItem(&g_pixmap);
    paint();

}

