#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum Direct{
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void addTop();
    void addDown();
    void addLeft();
    void addRight();
    //按键处理
    void keyPressEvent(QKeyEvent *event);
   void addNewReword();
    void deleteLast();
    bool checkContact();

private:
    Ui::Widget *ui;
    int moveFlag = DIR_UP;
    bool gameStart = false;

    QTimer *timer;
    int time = 100;
     //蛇
    QList <QRectF> snake;

    //奖品
    QRectF rewardNode;
    //小方块宽高
    int nodeWidth = 20;
    int nodeHeight = 20;
protected slots:
    void timeout();

};
#endif // WIDGET_H
