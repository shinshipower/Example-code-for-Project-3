#include "gameitem.h"

#include <iostream>

GameItem::GameItem(b2World *world):
    g_body(NULL),g_world(world)
{
    dragable=false;

}

GameItem::~GameItem()
{
    g_world->DestroyBody(g_body);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::g_worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize)
{
    g_worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::paint()
{   b2Vec2 pos;

    if(!dragable){
    pos = g_body->GetPosition();
    //std::cout<< g_body->GetPosition().x<<" "<<g_body->GetPosition().y<<std::endl;
    //std::cout << g_body->GetAngle() << std::endl;
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
    }else{
    g_pixmap.setPos(n_mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));}
}

