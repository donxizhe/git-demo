#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    定时器
    timer = new QTimer();
    //信号槽
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    resize(600,368);

    QRectF rect(300,180,nodeWidth,nodeHeight);
    snake.append(rect);
    addTop();
    addTop();

    addNewReword();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Up:
        if(moveFlag!=DIR_DOWN){
           moveFlag = DIR_UP;
        }
        break;
    case Qt::Key_Down:
        if(moveFlag != DIR_UP){
              moveFlag = DIR_DOWN;
        }
        break;
    case Qt::Key_Right:
        if(moveFlag!=DIR_LEFT){
         moveFlag = DIR_RIGHT;
        }
        break;
    case Qt::Key_Left:
        if(moveFlag != DIR_RIGHT){
            moveFlag = DIR_LEFT;
        }
        break;
    case Qt::Key_Space:
        if(gameStart ==false){
            gameStart=true;
            timer->start(time);
        }else{
            gameStart=false;
            timer->stop();
        }
        break;
        default:
        break;

    }
}
void Widget::timeout(){
    int count = 1;
    if(snake[0].intersects(rewardNode)){
        count++  ;
        addNewReword();
    }
    while(count--){
        switch(moveFlag){
        case DIR_UP:
        addTop();
        break;
        case DIR_DOWN:
       addDown();
            break;
        case DIR_LEFT:
            addLeft();
            break;
        case DIR_RIGHT:
            addRight();
            break;
        default:
            break;
        }
    }

    deleteLast();
    update();

}
void Widget::addTop(){

    QPointF leftTop;
    QPointF rightBotom;
    if(snake[0].y()-nodeHeight<0){
        leftTop = QPointF(snake[0].x(),this->height()-nodeHeight);
        rightBotom = QPointF(snake[0].x()+nodeWidth,this->height());
    }else{
        leftTop = QPointF(snake[0].x(),snake[0].y()-nodeHeight);
        rightBotom = snake[0].topRight();
    }

    snake.insert(0,QRectF(leftTop,rightBotom));
}
void Widget::addDown(){
    QPointF leftTop;
    QPointF rightBottom;
    if(snake[0].y()+nodeHeight*2>this->height())
    {
        leftTop = QPointF(snake[0].x(),0);
        rightBottom =  QPointF(snake[0].x()+nodeWidth,nodeHeight);
    }else{
        leftTop = snake[0].bottomLeft();
        rightBottom = snake[0].bottomRight()+QPointF(0,nodeHeight);
    }
    snake.insert(0,QRectF(leftTop,rightBottom));
}
void Widget::addLeft(){
    QPointF leftTop;
    QPointF rightBottom;

    if(snake[0].x()-nodeWidth<0)
    {
        leftTop = QPointF(this->width() - nodeWidth, snake[0].y());
    }else{
        leftTop = snake[0].topLeft()-QPointF(nodeWidth,0);
    }
    rightBottom = leftTop+QPointF(nodeWidth,nodeHeight);
     snake.insert(0,QRectF(leftTop,rightBottom));
}
void Widget::addRight(){
    QPointF leftTop;
    QPointF rightBottom;
   if(snake[0].x()+nodeWidth*2>this->width()){
       leftTop = QPointF(0,snake[0].y());
   }   else{
       leftTop = snake[0].topRight();
   }
   rightBottom = leftTop + QPointF(nodeWidth,nodeHeight);
     snake.insert(0,QRectF(leftTop,rightBottom));
}
void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    QPixmap pix;
    pix.load("C:/Users/23744/Pictures/1.JPG");
    painter.drawPixmap(0,0,600,368,pix);

    //画蛇
    pen.setColor(Qt::black);
    brush.setColor(Qt::darkMagenta);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    for(int i=0; i<snake.length();i++){
        painter.drawRect(snake[i]);
    }

    pen.setColor(Qt::red);
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
   // painter.drawRect(rewardNode);
    painter.drawEllipse(rewardNode);
    if(checkContact()){
      QFont font("方正舒体",30,QFont::ExtraLight,false);
      painter.setFont(font);
      painter.drawText((this->width()-300)/2,
                        (this->height()-30)/2,
                        QString("游戏结束"));
      timer->stop();
    }

    QWidget::paintEvent(event);

}
bool Widget::checkContact(){
    for(int i = 1;i<snake.length();i++){
        for(int j=i+1;j<snake.length();j++){
            if(snake[0]==snake[i]){
                return true;
            }
        }

    }
    return false;
}
void Widget::addNewReword(){
    rewardNode = QRectF(
                qrand()%(this->width()/20)*20,
                qrand()%(this->height()/20)*20,
                nodeWidth,
                nodeHeight
                );
}
void Widget::deleteLast()
{
    snake.removeLast();
}
