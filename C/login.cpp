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
    if(fileout_oper()==0||fileout_all()==0){
        mybox->show();
        mybox->setText("error!open fail!");
    }
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
        op_info *p;
        int flag=0;
        p=head_oper;
        while(p){
            if(strcmp(p->oper_code,cur_code.toLatin1().data())==0&&strcmp(p->oper_pwd,cur_pwd.toLatin1().data())==0){
                cur_oper=p;     //cur_oper赋值为当前用户信息
                oper=new op_interface(this);
                this->hide();
                oper->show();
                flag=1;
            }
            p=p->next_oper;
        }
        if(flag==0){
            mybox->show();
            mybox->setText("登录失败,输入有误!");
        }
    }
}

void login::on_exit_clicked()
{
    this->close();
}


