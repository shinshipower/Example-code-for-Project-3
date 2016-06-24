#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int btype ,bool dtype):GameItem(world)
{
    // Set pixmap
    Radius = radius;
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);
    dragable=dtype;
    birdtype= btype;
    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);

    b2Vec2 pos;
    pos.Set(x,y);
    n_mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
    n_mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
    b2Vec2 tmp = get_Position();
    std::cout<<tmp.x<<" "<<tmp.y<<std::endl;

    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
    speed = velocity;
}

//QRectF Bird::boundingRect() const
//{
//    return QRect(0,0,Radius*2,Radius*2);
//}

b2Vec2 Bird::get_Position()
{
    b2Vec2 tmpP;
    float xt = (n_mappedPoint.x()*g_worldsize.width()/g_windowsize.width())+g_size.width()/2;
    float yt =   (n_mappedPoint.y()/g_windowsize.height()-1.0)*(-1)*g_worldsize.height()-g_size.height()/2;
    tmpP.Set(xt,yt);


    return tmpP;
}
