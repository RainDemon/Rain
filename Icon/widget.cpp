#include "widget.h"
#include "ui_widget.h"
#include<QAction>
#include<QMenu>
#include<QToolBar>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createActions()
  {
     //创建托盘项
     QAction * action_show = new QAction(this);
     QAction * action_quit = new QAction(this);
     QAction * action_login_home = new QAction(this);
     QAction * action_help = new QAction(this);
     QAction * action_about = new QAction(this);
     QAction * action_check_update = new QAction(this);
     QAction * action_setting = new QAction(this);

     //设置托盘项图标
     action_show->setIcon(QIcon("../icon/1.gif"));
     action_login_home->setIcon(QIcon(":/icon/home"));
     action_help->setIcon(QIcon(":/icon/help"));
     action_about->setIcon(QIcon(":/icon/about"));
     action_check_update->setIcon(QIcon(":/icon/update"));
     action_setting->setIcon(QIcon(":/icon/set"));
     action_quit->setIcon(QIcon(":/icon/quit"));

     //设置托盘想文本
         action_show->setText(QString("显示"));
         action_quit->setText(QString("退出"));
         action_login_home->setText(QString("登录网页"));
         action_help->setText(QString("帮助"));
         action_about->setText(QString("关于"));
         action_check_update->setText(QString("检查更新"));
         action_setting->setText(QString("设置"));

         //添加菜单项
         this->addAction(action_show);
         this->addAction(action_setting);
         this->addAction(action_login_home);
         //this->addSeparator();
         this->addAction(action_help);
         this->addAction(action_about);
         this->addAction(action_check_update);
         //this->addSeparator();
         this->addAction(action_quit);
         action_setting->setVisible(false);

}
