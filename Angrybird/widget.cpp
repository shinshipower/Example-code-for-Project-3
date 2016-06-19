#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
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
    CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene);
    // Setting the Velocity
    //birdie->setLinearVelocity(b2Vec2(8,8));
    itemList.push_back(CurrentBird);
    //scene->addItem(birdie);


    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(&Re_gen,SIGNAL(timeout()),this,SLOT(regen()));

}
void Widget::shootBird(float x, float y, float vx, float vy, int birdType)
{
    QPixmap tmpBird = QPixmap("Normal_Bird_1.png").scaled(height()/10.0,height()/10.0);
    float Rad = 0.27;

    FlyingBird = new Bird(x,y,Rad,&timer,tmpBird,world,scene,false);
    FlyingBird->setLinearVelocity(b2Vec2(vx,vy));
    itemList.push_back(FlyingBird);

}




Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e){

    switch(e->key()){

        case Qt::Key_S:
            shootBird(startX,startY,8.0,8.0,1);
        break;
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
        if(!clicked){
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

        std::cout << "Release !" << std::endl ;

        Re_gen.start(3000);
        }

        clicked = false;
    }
    return false;
}

void Widget::regen()
{
    Re_gen.stop();
    CurrentBird = new Bird(startX,startY,0.27f,&timer,QPixmap("Yellow_Bird_1.png").scaled(height()/10.0,height()/10.0),world,scene);
    itemList.push_back(CurrentBird);
}

