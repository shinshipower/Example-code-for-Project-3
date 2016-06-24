#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{   current_type =1;
    clicked = false;
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    scene=new QGraphicsScene(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);


    world = new b2World(b2Vec2(0.0f, -9.8f));
    GameItem::setGlobalSize(QSizeF(32,18),size());
    //Land *myland=new Land(16,1.5,32,3,QPixmap("ground.png").scaled(width(),height()/6.0),world,scene);
itemList.push_back(new Land(16,1.5,32,3,QPixmap("./GROUND.png").scaled(width(),height()/6.0),world,scene));

itemList.push_back(new Y_wood(4,10,0,0,QPixmap("./YY.png").scaled(100,300),world,scene));
    //scene->addItem(myland);

    // Create bird (You can edit here)
    startX = 5.0;
    startY = 10.0;
    CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
    Fake = new Bird(0,0,0.0f,&timer,QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
    FlyingBird = Fake;
    // Setting the Velocity
    //birdie->setLinearVelocity(b2Vec2(8,8));
    itemList.push_back(CurrentBird);
    nobird = false;
    //scene->addItem(birdie);


    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(&Re_gen,SIGNAL(timeout()),this,SLOT(regen()));

}
void Widget::shootBird(float x, float y, float vx, float vy, int birdType)
{

    QPixmap tmpBird;
    switch(current_type){
        case 1:
        tmpBird= QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0);
        break;
        case 2:
        tmpBird= QPixmap("Yellow_Bird_1.png").scaled(height()/10.0,height()/10.0);
        break;
        case 3:
        tmpBird= QPixmap("White_Bird_1.png").scaled(height()/10.0,height()/10.0);
        break;
        case 4:
        tmpBird= QPixmap("Blue_Bird_1.png").scaled(height()/10.0,height()/10.0);
        break;
    default:
        break;
    }

    float Rad = 0.27;

    FlyingBird = new Bird(x,y,Rad,&timer,tmpBird,world,scene,current_type,false);
    FlyingBird->setLinearVelocity(b2Vec2(vx,vy));
    itemList.push_back(FlyingBird);

}




Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e){
b2Vec2 tmpv;
Bird* tmpb;
    switch(e->key()){

        case Qt::Key_S:
            shootBird(startX,startY,8.0,8.0,1);
        break;
        case Qt::Key_Space:
            switch(current_type)
            {
                case 2:
                tmpv = FlyingBird->speed;
                tmpv.Set(tmpv.x*1.5,tmpv.y*1.5);
                FlyingBird->setLinearVelocity(tmpv);
                break;
                case 3:
                tmpb =new Bird(FlyingBird->g_body->GetPosition().x,FlyingBird->g_body->GetPosition().y,0.15,&timer,QPixmap("./egg.png").scaled(height()/15.0,height()/15.0),world,scene,5,false);
                itemList.push_back(tmpb);
                break;
                case 4:
                tmpb =new Bird(FlyingBird->g_body->GetPosition().x,FlyingBird->g_body->GetPosition().y,0.27,&timer,QPixmap("./Blue_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,4,false);
                tmpv = FlyingBird->speed;
                                tmpv.Set(tmpv.x,tmpv.y*0.75);
                tmpb->setLinearVelocity(tmpv);
                itemList.push_back(tmpb);
                tmpb =new Bird(FlyingBird->g_body->GetPosition().x,FlyingBird->g_body->GetPosition().y,0.27,&timer,QPixmap("./Blue_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,4,false);
                tmpv = FlyingBird->speed;
                tmpv.Set(tmpv.x,tmpv.y*1.2);
                tmpb->setLinearVelocity(tmpv);
                itemList.push_back(tmpb);
                break;
            default:
                break;

            }

        default:
            break;
    }
}

void Widget::on_EXIT_released()
{
    close();
}

void Widget::on_START_released()
{
    ui->stackedWidget->setCurrentIndex(1);
    timer.start(100/6);
    qApp->installEventFilter(this);
}

void Widget::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void Widget::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void Widget::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

bool Widget::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
        if(!clicked&& !nobird){
            //startMouse=this->mapFromGlobal(QCursor::pos());

            startMouse = e->pos();
            trackingMouse = e->pos();
            clicked = true;
        }
        /* TODO : add your code here */
        std::cout << "Press !" << std::endl ;
        std::cout << "mouse start from "<<startMouse.x()<<" "<<startMouse.y()<<std::endl;
    }
    if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent *ee = static_cast<QMouseEvent *>(event);
        QPoint delta = trackingMouse-ee->pos();
        trackingMouse = ee->pos();
        //delta.setX(delta.x()/10);
        //delta.setY(delta.y()/10);

        if(clicked){
        CurrentBird->n_mappedPoint.setX(CurrentBird->n_mappedPoint.x()-delta.x());
        CurrentBird->n_mappedPoint.setY(CurrentBird->n_mappedPoint.y()-delta.y());
        delta.setX(0);
        delta.setY(0);
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
        //std::cout << "delta = " << delta.x()<<" "<<delta.y()<<std::endl;

        }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {

        QMouseEvent *eee = static_cast<QMouseEvent *>(event);

                QPoint delta2 = startMouse-eee->pos();
                b2Vec2 newstart;
                float vx,vy;
                vx = 12.0*delta2.x()/150;
                vy = -1*12.0*delta2.y()/150;
                //Bird* tmp = CurrentBird;
        if(clicked){
                clicked == false;
                newstart = CurrentBird->get_Position();
                CurrentBird->deleteLater();
                //CurrentBird->n_mappedPoint.setX(-1000);
                //CurrentBird->n_mappedPoint.setY(-1000);
                shootBird(newstart.x,newstart.y,vx,vy,1);
                CurrentBird = Fake;

        std::cout << "Release !" << std::endl ;
        nobird = true;
        Re_gen.start(5000);
        }

        clicked = false;
    }
    return false;
}

void Widget::regen()
{
    Re_gen.stop();
    switch (current_type)
    {
    case 1:
        current_type++;
        CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Yellow_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
        break;
    case 2:
        current_type++;
        CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("White_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
        break;
    case 3:
        current_type++;
        CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Blue_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
        break;
    case 4:
        current_type = 1;
        CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
        break;
    default:
        break;
    }

    //CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Yellow_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene);
    itemList.push_back(CurrentBird);
    nobird = false;
}




void Widget::on_pushButton_pressed()
{   qApp->removeEventFilter(this);
    timer.stop();
    nobird = true;
    ui->stackedWidget->setCurrentIndex(0);
                    CurrentBird->deleteLater();
    itemList.clear();
    current_type =1;
        clicked = false;
        //itemList.push_back(new Land(16,1.5,32,3,QPixmap("./GROUND.png").scaled(width(),height()/6.0),world,scene));

        //itemList.push_back(new Y_wood(4,10,0,0,QPixmap("./YY.png").scaled(100,300),world,scene));
        CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
        Fake = new Bird(0,0,0.0f,&timer,QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene,current_type);
        FlyingBird = Fake;
        // Setting the Velocity
        //birdie->setLinearVelocity(b2Vec2(8,8));
        itemList.push_back(CurrentBird);
        nobird = false;
}
