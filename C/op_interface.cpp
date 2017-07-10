#include "op_interface.h"
#include "ui_op_interface.h"
#include <QDebug>
op_interface::op_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::op_interface)
{
    ui->setupUi(this);
    QString style="QPushButton{background-color:white;color: black;   border-radius: 5px;  border: 2px groove gray;  border-style: outset;}"
                  "QPushButton:hover{background-color:black; color: white;}"
                 "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }";
    ui->exit->setStyleSheet("QPushButton{background-color:white;color: black;   border-radius: 5px;  border: 2px groove gray;  border-style: outset;}"
                            "QPushButton:hover{background-color:red; color: white;}"
                           "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }");
    ui->op_info_change->setStyleSheet(style);
    ui->op_passwd_change->setStyleSheet(style);
    ui->stor_alter->setStyleSheet(style);
    ui->goods_add->setStyleSheet(style);
    ui->goods_alter->setStyleSheet(style);
    ui->goods_delete->setStyleSheet(style);
    ui->record_add->setStyleSheet(style);
    ui->record_alter->setStyleSheet(style);
    ui->record_delete->setStyleSheet(style);
    box1=new QMessageBox(this);
    //取出操作员对应的仓库信息
    Storage *p;
    p=head_all;
    while(p){
        if(strcmp(p->stor_code,cur_oper->stor_code)==0){
            cur_stor=p; //全局变量 cur_stor赋值 一旦登录即不会变
        }
        p=p->next_stor;
    }
    box1->show();
    box1->setText("登录成功!当前仓库为："+QString(QLatin1String(cur_stor->stor_code)));
    //将基本信息显示出来
    refresh_baseinfo(); //基本信息刷新
    refresh_combox(); //商品下拉框刷新
    refresh_table_cata(); //商品表的加载
    refresh_table_count();  //统计表的加载
    connect(ui->goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(cata_display())); //商品文本框显示
    connect(ui->op_goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(record_select())); //记录流水号下拉菜单加载
    connect(ui->op_num,SIGNAL(currentIndexChanged(int)),this,SLOT(record_display())); //记录文本框显示
    connect(ui->stat_goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(count_display())); //查询统计文本显示
}

void op_interface::on_exit_clicked()
{
    filein_oper();
    filein_all();
    this->close();
    parentWidget()->show();
}
op_interface::~op_interface()
{
    delete ui;
}
//*******刷新操作*********
//操作员信息和仓库信息显示刷新*
void op_interface::refresh_baseinfo()
{
    ui->op_code->setText(cur_oper->oper_code);
    ui->op_name->setText(cur_oper->oper_name);
    ui->op_stor_code->setText(cur_oper->stor_code);
    ui->stor_name->setText(cur_stor->stor_name);
    ui->stor_code->setText(cur_stor->stor_code);
    ui->phone_num->setText(cur_stor->stor_phon);
    ui->locate_2->setText(cur_stor->stor_loc);
}
//商品下拉框的刷新*
void op_interface::refresh_combox()
{
    ui->goods_code->clear();
    ui->op_goods_code->clear();
    ui->stat_goods_code->clear();
    ui->goods_name->clear();
    ui->goods_type->clear();
    ui->num_units->clear();
    ui->factory->clear();
    ui->op_num->setCurrentIndex(0);
    ui->op_type->setCurrentIndex(0);
    ui->op_amount->clear();
    ui->date->clear();
    ui->stat_goods_name->clear();
    ui->stat_goods_type->clear();
    ui->stat_goods_amount->clear();
    ui->stat_num_units->clear();
    ui->goods_code->addItem("——请选择——");
    ui->op_goods_code->addItem("——请选择——");
    ui->stat_goods_code->addItem("——请选择——");
    ui->goods_code->addItem("点我进行添加");
    Catalogue *p;
    p=cur_stor->head_cata;
    while(p){
        ui->goods_code->addItem(p->cata_code);
        ui->op_goods_code->addItem(p->cata_code);
        ui->stat_goods_code->addItem(p->cata_code);
        p=p->next_cata;
    }
}
//商品表显示刷新*
void op_interface::refresh_table_cata()
{
    QStandardItemModel *cata_model=new QStandardItemModel();
    cata_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("商品编号")));
    cata_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品名称")));
    cata_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("商品类型")));
    cata_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("数量单位")));
    cata_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("厂商名称")));
    ui->info_goods->setModel(cata_model);
    Catalogue *p;
    int i=0;
    p=cur_stor->head_cata;
    //遍历链表显示所有信息到表中
    while(p){
        cata_model->setItem(i,0,new QStandardItem(p->cata_code));
        cata_model->setItem(i,1,new QStandardItem(p->cata_name));
        cata_model->setItem(i,2,new QStandardItem(p->cata_type));
        cata_model->setItem(i,3,new QStandardItem(p->cata_unit));
        cata_model->setItem(i,4,new QStandardItem(p->cata_comp));
        p=p->next_cata;
        i++;
    }
}
//查询统计表显示刷新*
void op_interface::refresh_table_count()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("商品编号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品名称")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("商品类型")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("当前库存")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("厂商名称")));
    ui->info_stat->setModel(model);
    Catalogue *p;
    int i=0;
    p=cur_stor->head_cata;
    while(p){
        model->setItem(i,0,new QStandardItem(p->cata_code));
        model->setItem(i,1,new QStandardItem(p->cata_name));
        model->setItem(i,2,new QStandardItem(p->cata_type));
        model->setItem(i,3,new QStandardItem(QString::number(cata_count(p))));
        model->setItem(i,4,new QStandardItem(p->cata_comp));
        p=p->next_cata;
        i++;
    }
}
//商品文本显示*
void op_interface::cata_display()
{
    if(ui->goods_code->currentIndex()==1){
        ui->goods_code->setEditable(1);
        ui->goods_name->clear();
        ui->goods_type->clear();
        ui->num_units->clear();
        ui->factory->clear();
    }
    else if(ui->goods_code->currentIndex()!=0){
        ui->goods_code->setEditable(0);
        Catalogue *p;
        p=cur_stor->head_cata;
        while(p){
            if(strcmp(p->cata_code,ui->goods_code->currentText().toLocal8Bit().data())==0){
                ui->goods_name->setText(p->cata_name);
                ui->goods_type->setText(p->cata_type);
                ui->num_units->setText(p->cata_unit);
                ui->factory->setText(p->cata_comp);
                break;
            }
            p=p->next_cata;
        }
    }
    else{
        ui->goods_name->clear();
        ui->goods_type->clear();
        ui->num_units->clear();
        ui->factory->clear();
    }
}
//记录下拉选择+记录表*
void op_interface::record_select()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("流水号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品编号")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("处理类型")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("处理数量")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("处理时间")));
    ui->info_record->setModel(model);
    ui->op_type->setCurrentIndex(0);
    ui->op_amount->clear();
    ui->date->clear();
    ui->op_num->clear();
    ui->op_num->addItem("——请选择——");
    ui->op_num->addItem("点我进行添加");
    Catalogue *p;
    Record *q;
    int i=0;
    p=cur_stor->head_cata;
    while(p){
         if(strcmp(p->cata_code,ui->op_goods_code->currentText().toLocal8Bit().data())==0){
             q=p->head_reco;
             while(q){
                 ui->op_num->addItem(q->reco_code);
                 model->setItem(i,0,new QStandardItem(q->reco_code));
                 model->setItem(i,1,new QStandardItem(q->cata_code));
                 QString str;
                 if(q->reco_type=='1') str="入库";
                 if(q->reco_type=='0') str="出库";
                 model->setItem(i,2,new QStandardItem(str));
                 model->setItem(i,3,new QStandardItem(QString::number(q->reco_sum)));
                 model->setItem(i,4,new QStandardItem(q->reco_date));
                 q=q->next_reco;
                 i++;
             }
             break;
         }
         p=p->next_cata;
    }
}
//记录显示*
void op_interface::record_display()
{
    if(ui->op_num->currentIndex()==1){
        ui->op_num->setEditable(1);
        ui->op_type->setCurrentIndex(0);
        ui->op_amount->clear();
        ui->date->clear();
    }
    else if(ui->op_num->currentIndex()!=0){
        ui->op_num->setEditable(0);
        Catalogue *q;
        Record *p;
        q=cur_stor->head_cata;
        while(q){
            if(strcmp(q->cata_code,ui->op_goods_code->currentText().toLocal8Bit().data())==0){
                p=q->head_reco;
                while(p){
                    if(strcmp(p->reco_code,ui->op_num->currentText().toLocal8Bit().data())==0){
                        if(p->reco_type=='1')
                            ui->op_type->setCurrentIndex(1);
                        if(p->reco_type=='0')
                            ui->op_type->setCurrentIndex(2);
                        ui->op_amount->setText(QString::number(p->reco_sum));
                        ui->date->setText(p->reco_date);
                        break;
                    }
                    p=p->next_reco;
                }
            }
            q=q->next_cata;
        }
    }
    else{
        ui->op_type->setCurrentIndex(0);
        ui->op_amount->clear();
        ui->date->clear();
    }
}
//查询统计显示*
void op_interface::count_display()
{
    Catalogue *p;
    int flag=0;
    p=cur_stor->head_cata;
    while(p){
        if(strcmp(p->cata_code,ui->stat_goods_code->currentText().toLocal8Bit().data())==0){
            flag=1;
            ui->stat_goods_name->setText(p->cata_name);
            ui->stat_goods_type->setText(p->cata_type);
            ui->stat_num_units->setText(p->cata_unit);
            ui->stat_goods_amount->setText(QString::number(cata_count(p)));
        }
         p=p->next_cata;
    }
    if(flag==0){
        ui->stat_goods_name->clear();
        ui->stat_goods_type->clear();
        ui->stat_num_units->clear();
        ui->stat_goods_amount->clear();
    }
}
//*******操作员修改信息**********
void op_interface::on_op_info_change_clicked()
{
    op_info alter_struc;
    std::string str;
    str=ui->op_name->text().toStdString();
    strcpy(alter_struc.oper_name,str.c_str());
    strcpy(alter_struc.oper_code,cur_oper->oper_code);
    strcpy(alter_struc.oper_pwd,cur_oper->oper_pwd);
    strcpy(alter_struc.stor_code,cur_oper->stor_code);
    if(oper_alter_node(alter_struc)){
        box1->show();
        box1->setText("修改成功!");
    }
    refresh_baseinfo();
}
void op_interface::on_op_passwd_change_clicked()
{
    if(strcmp(ui->cur_pwd->text().toLatin1().data(),cur_oper->oper_pwd)==0){
        if(ui->new_pwd->text()==ui->con_pwd->text()){
            op_info alter_struc;
            std::string str;
            str=ui->new_pwd->text().toStdString();
            strcpy(alter_struc.oper_pwd,str.c_str());
            strcpy(alter_struc.oper_code,cur_oper->oper_code);
            strcpy(alter_struc.oper_name,cur_oper->oper_pwd);
            strcpy(alter_struc.stor_code,cur_oper->stor_code);
            if(oper_alter_node(alter_struc)){
                box1->show();
                box1->setText("密码修改成功!");
            }
            refresh_baseinfo();
        }
        else {
            box1->show();
            box1->setText("两次输入密码不一致\n请重新输入");
        }
    }
    else{
        box1->show();
        box1->setText("密码验证错误\n请重新输入");
    }
}
//********仓库修改信息***********
void op_interface::on_stor_alter_clicked()
{
    Storage alter_struc;
    std::string str;
    str=ui->stor_name->text().toStdString();
    strcpy(alter_struc.stor_name,str.c_str());
    str=ui->locate_2->text().toStdString();
    strcpy(alter_struc.stor_loc,str.c_str());
    str=ui->phone_num->text().toStdString();
    strcpy(alter_struc.stor_phon,str.c_str());
    strcpy(alter_struc.stor_code,cur_stor->stor_code);
    if(stor_alter_node(alter_struc)){
        box1->show();
        box1->setText("修改成功!");
    }
    refresh_baseinfo();
}
//**********商品修改信息**********
void op_interface::on_goods_add_clicked()
{
    Catalogue add_struc;
    std::string str;
    //错误记录*****先将QString 转化为标准的stirng再将string转换为char*
    strcpy(add_struc.stor_code,cur_stor->stor_code);
    str=ui->goods_code->currentText().toStdString();
    strcpy(add_struc.cata_code,str.c_str());
    str=ui->goods_name->text().toStdString();
    strcpy(add_struc.cata_name,str.c_str());
    str=ui->goods_type->text().toStdString();
    strcpy(add_struc.cata_type,str.c_str());
    str=ui->num_units->text().toStdString();
    strcpy(add_struc.cata_unit,str.c_str());
    str=ui->factory->text().toStdString();
    strcpy(add_struc.cata_comp,str.c_str());
    if(cata_add_node(add_struc)){
        box1->show();
        box1->setText("添加成功!");
    }
    else{
        box1->show();
        box1->setText("添加失败!");
    }
    //刷新
    refresh_baseinfo();
    //refresh_combox();
    refresh_table_cata();
    refresh_table_count();
}
void op_interface::on_goods_delete_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "确认框", "确定要删除该商品?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        Catalogue dele_struc;
        std::string str;
        //错误记录*****先将QString 转化为标准的stirng再将string转换为char*
        strcpy(dele_struc.stor_code,cur_stor->stor_code);
        str=ui->goods_code->currentText().toStdString();
        strcpy(dele_struc.cata_code,str.c_str());
        str=ui->goods_name->text().toStdString();
        strcpy(dele_struc.cata_name,str.c_str());
        str=ui->goods_type->text().toStdString();
        strcpy(dele_struc.cata_type,str.c_str());
        str=ui->num_units->text().toStdString();
        strcpy(dele_struc.cata_unit,str.c_str());
        str=ui->factory->text().toStdString();
        strcpy(dele_struc.cata_comp,str.c_str());
        if(cata_dele_node(dele_struc)){
            box1->show();
            box1->setText("删除成功!");
        }
        //刷新
        refresh_baseinfo();
        refresh_combox();
        refresh_table_cata();
        refresh_table_count();
    }
}
void op_interface::on_goods_alter_clicked()
{
    Catalogue alter_struc;
    std::string str;
    //错误记录*****先将QString 转化为标准的stirng再将string转换为char*
    strcpy(alter_struc.stor_code,cur_stor->stor_code);
    str=ui->goods_code->currentText().toStdString();
    strcpy(alter_struc.cata_code,str.c_str());
    str=ui->goods_name->text().toStdString();
    strcpy(alter_struc.cata_name,str.c_str());
    str=ui->goods_type->text().toStdString();
    strcpy(alter_struc.cata_type,str.c_str());
    str=ui->num_units->text().toStdString();
    strcpy(alter_struc.cata_unit,str.c_str());
    str=ui->factory->text().toStdString();
    strcpy(alter_struc.cata_comp,str.c_str());
    if(cata_alter_node(alter_struc)){
        box1->show();
        box1->setText("修改成功!");
    }
    //刷新
    refresh_baseinfo();
    refresh_combox();
    refresh_table_cata();
    refresh_table_count();

}
//**********记录修改信息***********
void op_interface::on_record_add_clicked()
{
    Record add_struc;
    std::string str;
    //错误记录*****先将QString 转化为标准的stirng再将string转换为char*
    strcpy(add_struc.oper_code,cur_stor->stor_code);
    strcpy(add_struc.stor_code,cur_stor->stor_code);
    str=ui->op_goods_code->currentText().toStdString();
    strcpy(add_struc.cata_code,str.c_str());
    str=ui->op_num->currentText().toStdString();
    strcpy(add_struc.reco_code,str.c_str());
    if(ui->op_type->currentIndex()==1)
        add_struc.reco_type='1';
    if(ui->op_type->currentIndex()==2)
         add_struc.reco_type='0';
    add_struc.reco_sum=ui->op_amount->text().toInt();
    str=ui->date->text().toStdString();
    strcpy(add_struc.reco_date,str.c_str());
    if(reco_add_node(add_struc)){
        box1->show();
        box1->setText("添加成功!");
    }
    else{
        box1->show();
        box1->setText("添加失败!");
    }
    //刷新
    ui->op_goods_code->setCurrentIndex(0);
    refresh_baseinfo();
    //refresh_combox();
    refresh_table_cata();
    refresh_table_count();
}
void op_interface::on_record_delete_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "确认框", "确定要删除该记录?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes){
        Record dele_struc;
        std::string str;
        //错误记录*****先将QString 转化为标准的stirng再将string转换为char*
        strcpy(dele_struc.oper_code,cur_stor->stor_code);
        strcpy(dele_struc.stor_code,cur_stor->stor_code);
        str=ui->op_goods_code->currentText().toStdString();
        strcpy(dele_struc.cata_code,str.c_str());
        str=ui->op_num->currentText().toStdString();
        strcpy(dele_struc.reco_code,str.c_str());
        if(ui->op_type->currentIndex()==1)
            dele_struc.reco_type='1';
        if(ui->op_type->currentIndex()==2)
             dele_struc.reco_type='0';
        dele_struc.reco_sum=ui->op_amount->text().toInt();
        str=ui->date->text().toStdString();
        strcpy(dele_struc.reco_date,str.c_str());
        if(reco_dele_node(dele_struc)){
            box1->show();
            box1->setText("删除成功!");
        }
        //刷新
        ui->op_goods_code->setCurrentIndex(0);
        refresh_baseinfo();
        //refresh_combox();
        refresh_table_cata();
        refresh_table_count();
    }
}
void op_interface::on_record_alter_clicked()
{
    Record alter_struc;
    std::string str;
    //错误记录*****先将QString 转化为标准的stirng再将string转换为char*
    strcpy(alter_struc.oper_code,cur_stor->stor_code);
    strcpy(alter_struc.stor_code,cur_stor->stor_code);
    str=ui->op_goods_code->currentText().toStdString();
    strcpy(alter_struc.cata_code,str.c_str());
    str=ui->op_num->currentText().toStdString();
    strcpy(alter_struc.reco_code,str.c_str());
    if(ui->op_type->currentIndex()==1)
        alter_struc.reco_type='1';
    if(ui->op_type->currentIndex()==2)
         alter_struc.reco_type='0';
    alter_struc.reco_sum=ui->op_amount->text().toInt();
    str=ui->date->text().toStdString();
    strcpy(alter_struc.reco_date,str.c_str());
    if(reco_alter_node(alter_struc)){
        box1->show();
        box1->setText("修改成功!");
    }
    //刷新
    ui->op_goods_code->setCurrentIndex(0);
    refresh_baseinfo();
    //refresh_combox();
    refresh_table_cata();
    refresh_table_count();
}

