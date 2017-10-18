#include "myview.h"
#include "mybox.h"
#include <QIcon>
//inicial game speed
static const qreal INITSPEED = 500;

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
    initView();
}
//Initialize the game interface
void MyView::initView()
{
    //Using antialiasing rendering
    setRenderHint(QPainter::Antialiasing);
    //Setting cache background
    setCacheMode(CacheBackground);
    setWindowTitle(tr("BoxGame"));
    setWindowIcon(QIcon(":/images.icon.png"));
    setMinimumSize(810,510);
    setMaximumSize(810,510);
    //Set Scence
    QGraphicsScene * scene= new QGraphicsScene;
    scene->setSceneRect(5,5,800,500);
    scene->setBackgroundBrush(QPixmap(":/images/background.png"));
    setScene(scene);
    //The four movable lines of a square
    topLine = scene->addLine(197,47,403,47);
    bottomLine = scene->addLine(197,453,403,453);
    leftLine = scene->addLine(197,47,197,453);
    rightLine = scene->addLine(403,47,403,453);
    //Current block group and prompt box group
    boxGroup = new BoxGroup;
    connect(boxGroup,SIGNAL(needNewBox()),this,SLOT(clearFullRows()));
    connect(boxGroup,SIGNAL(gameFinished()),this,SLOT(gameOver()));
    scene->addItem(boxGroup);
    nextBoxGroup = new BoxGroup;
    scene->addItem(nextBoxGroup);


    startGame();
}


//star game
void MyView::startGame()
{
    initGame();
}

//initial game
void MyView::initGame()
{
    boxGroup->createBox(QPointF(300,70));
    boxGroup->setFocus();
    boxGroup->startTimer(INITSPEED);
    gameSpeed = INITSPEED;
    nextBoxGroup->createBox(QPointF(500,700));
}

void MyView::clearFullRows()
{
    //Gets the 1 small squares contained in a rectangle larger than a row of squares
    for(int y = 29;y>50;y-=20)
    {
        QList<QGraphicsItem * >list = scene()->items(100,y,202,2,
                                                     Qt::ContainsItemShape);
    //If the line is busy
        if(list.count()==10){
            foreach(QGraphicsItem * item,list){
                OneBox *box = (OneBox * ) item;
                box->deleteLater();
            }
            //Save full line position
            rows<<y;
        }
    }
    //if there is a full line,
    //Move down rows full of rows, and then new box groups appear
    //if it's not full,It goes straight to the new box
    if(rows.count()>0){
        moveBox();
    } else{
        boxGroup->createBox(QPointF(300,70),nextBoxGroup->getCurrentShape());
        //Empty and destroyed all the small box group
        nextBoxGroup->clearBoxGroup(true);
        nextBoxGroup->createBox(QPointF(500,70));
    }

}

//Move down all the small squares above the line
void MyView::moveBox()
{
    //Start from the full line of the position closest to the top
for(int i =rows.count();i>0;--i){
    int row = rows.at(i-1);
    foreach (QGraphicsItem * item ,scene()->items(199,49,202,row - 47,Qt::ContainsItemShape))
    {
        item->moveBy(0,20);
    }
}
    //Update the score
    updateScore(rows.count());
    //Empty the full row list to 0
    rows.clear();
    //After all rows are moved down, a new box group appears
    boxGroup->createBox(QPointF(300,70),nextBoxGroup->getCurrentShape());
    nextBoxGroup->clearBoxGroup(true);
    nextBoxGroup->createBox(QPointF(500,70));

}

void MyView::updateScore(const int fullRowNum)
{
    //update the score
}

void MyView::gameOver()
{
    //game over
}

