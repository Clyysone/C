#include "su_oper.h"
#include "ui_su_oper.h"

su_oper::su_oper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::su_oper)
{
    ui->setupUi(this);
    box2=new QMessageBox(this);
    fresh_stor();
    fresh_oper();
    fresh_combox();
    connect(ui->stor_code,SIGNAL(currentIndexChanged(int)),this,SLOT(stor_display()));
}
su_oper::~su_oper()
{
    delete ui;
}
void su_oper::fresh_combox()
{
    ui->stor_code->clear();
    ui->stor_code_2->clear();
    ui->stor_code->addItem("——请选择——");
    ui->stor_code_2->addItem("——请选择——");
    ui->stor_code->addItem("点我进行添加");
    Storage *p;
    p=head_all;
    while(p){
        ui->stor_code->addItem(p->stor_code);
        ui->stor_code_2->addItem(p->stor_code);
        p=p->next_stor;
    }
    ui->stor_name->clear();
    ui->locate->clear();
    ui->phone_num->clear();
    ui->op_name->clear();
    ui->op_passwd->clear();
    ui->op_code->clear();
}

void su_oper::fresh_stor()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("仓库编号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("仓库名称")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("仓库位置")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("仓库电话")));
    ui->stor_table->setModel(model);
    Storage *p;
    int i=0;
    p=head_all;
    //遍历链表显示所有信息到表中
    while(p){
        model->setItem(i,0,new QStandardItem(p->stor_code));
        model->setItem(i,1,new QStandardItem(p->stor_name));
        model->setItem(i,2,new QStandardItem(p->stor_loc));
        model->setItem(i,3,new QStandardItem(p->stor_phon));
        p=p->next_stor;
        i++;
    }
}
void su_oper::fresh_oper()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("操作员编号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("操作员名字")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("操作员密码")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("所属仓库")));
    ui->oper_table->setModel(model);
    op_info *p;
    int i=0;
    p=head_oper;
    //遍历链表显示所有信息到表中
    while(p){
        model->setItem(i,0,new QStandardItem(p->oper_code));
        model->setItem(i,1,new QStandardItem(p->oper_name));
        model->setItem(i,2,new QStandardItem(p->oper_pwd));
        model->setItem(i,3,new QStandardItem(p->stor_code));
        p=p->next_oper;
        i++;
    }
}

void su_oper::stor_display()
{
    if(ui->stor_code->currentIndex()==1){
        ui->stor_code->setEditable(1);
        ui->stor_name->clear();
        ui->locate->clear();
        ui->phone_num->clear();
    }
    else{
        Storage *p;
        p=head_all;
        while(p){
            if(strcmp(p->stor_code,ui->stor_code->currentText().toLocal8Bit().data())==0){
                ui->stor_name->setText(p->stor_name);
                ui->locate->setText(p->stor_loc);
                ui->phone_num->setText(p->stor_phon);
                 break;
            }
            p=p->next_stor;
        }
    }
}

void su_oper::on_tabWidget_tabBarClicked(int index)
{
        if(index==1){
            filein_all();
            filein_oper();
            this->close();
        }
}
void su_oper::on_stor_add_clicked()
{
    Storage add_struc;
    std::string str;
    str=ui->stor_code->currentText().toStdString();
    strcpy(add_struc.stor_code,str.c_str());
    str=ui->stor_name->text().toStdString();
    strcpy(add_struc.stor_name,str.c_str());
    str=ui->locate->text().toStdString();
    strcpy(add_struc.stor_loc,str.c_str());
    str=ui->phone_num->text().toStdString();
    strcpy(add_struc.stor_phon,str.c_str());
    if(stor_add_node(add_struc)){
         box2->show();
         box2->setText("添加成功");
     }
     fresh_stor();
     fresh_oper();
     fresh_combox();
}
void su_oper::on_stor_dele_clicked()
{
    Storage dele_struc;
    std::string str;
    str=ui->stor_code->currentText().toStdString();
    strcpy(dele_struc.stor_code,str.c_str());
    str=ui->stor_name->text().toStdString();
    strcpy(dele_struc.stor_name,str.c_str());
    str=ui->locate->text().toStdString();
    strcpy(dele_struc.stor_loc,str.c_str());
    str=ui->phone_num->text().toStdString();
    strcpy(dele_struc.stor_phon,str.c_str());
    if(stor_dele_node(dele_struc)){
         box2->show();
         box2->setText("删除成功");
     }
     fresh_stor();
     fresh_oper();
     fresh_combox();
}
void su_oper::on_op_add_clicked()
{
    op_info add_struc;
    std::string str;
    str=ui->stor_code_2->currentText().toStdString();
    strcpy(add_struc.stor_code,str.c_str());
    str=ui->op_code->text().toStdString();
    strcpy(add_struc.oper_code,str.c_str());
    str= ui->op_name->text().toStdString();
    strcpy(add_struc.oper_name,str.c_str());
    str=ui->op_passwd->text().toStdString();
    strcpy(add_struc.oper_pwd,str.c_str());
    if(oper_add_node(add_struc)){
         box2->show();
         box2->setText("添加成功");
    }
    fresh_stor();
    fresh_oper();
    fresh_combox();
}
void su_oper::on_op_dele_clicked()
{
    op_info dele_struc;
    std::string str;
    str=ui->stor_code_2->currentText().toStdString();
    strcpy(dele_struc.stor_code,str.c_str());
    str=ui->op_code->text().toStdString();
    strcpy(dele_struc.oper_code,str.c_str());
    str= ui->op_name->text().toStdString();
    strcpy(dele_struc.oper_name,str.c_str());
    str=ui->op_passwd->text().toStdString();
    strcpy(dele_struc.oper_pwd,str.c_str());
    if(oper_dele_node(dele_struc)){
         box2->show();
         box2->setText("删除成功");
    }
    fresh_stor();
    fresh_oper();
    fresh_combox();
}
