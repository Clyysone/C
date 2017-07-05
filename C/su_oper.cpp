#include "su_oper.h"
#include "ui_su_oper.h"

su_oper::su_oper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::su_oper)
{
    ui->setupUi(this);
}

su_oper::~su_oper()
{
    delete ui;
}

void su_oper::on_tabWidget_tabBarClicked(int index)
{
        if(index==2){
            this->close();
        }
}

void su_oper::on_stor_add_clicked()
{

}

void su_oper::on_stor_dele_clicked()
{

}

void su_oper::on_op_add_clicked()
{

}

void su_oper::on_op_dele_clicked()
{

}
