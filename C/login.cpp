#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    mybox=new QMessageBox(this);
}

login::~login()
{
    delete ui;
}

void login::on_start_clicked()
{
    QString cur_code= ui->code->currentText();
    QString cur_pwd=ui->passwd->text();
    if(ui->code->currentText()==NULL){
        mybox->show();
        mybox->setText("请输入编号!");
    }
    else if(ui->passwd->text()==NULL){
        mybox->show();
        mybox->setText("请输入密码!");
    }
    else if(ui->su->isChecked()==1){
         if(cur_code=="111"&&cur_pwd=="111"){
                 su=new su_oper(this);
                 su->show();
         }
         else{
             mybox->show();
             mybox->setText("输入有误!");
         }
    }
    else{
            oper=new op_interface(this);
            this->hide();
            oper->show();
    }
}

void login::on_exit_clicked()
{
    this->close();
}


