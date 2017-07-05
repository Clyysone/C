#include "op_interface.h"
#include "ui_op_interface.h"

op_interface::op_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::op_interface)
{
    ui->setupUi(this);
}

op_interface::~op_interface()
{
    delete ui;
}
//*******刷新操作*********
void op_interface::refresh_table_count()
{
    /*
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("商品编号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品名称")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("商品类型")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("当前库存")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("厂商名称")));
    ui->info_stat->setModel(model);
    Catalogue *p;
    Record *q;
    int i=0;
    p=cur_stor.head_cata;
    while(p){
        model->setItem(i,0,new QStandardItem(p->goods_code));
        model->setItem(i,1,new QStandardItem(p->goods_name));
        model->setItem(i,2,new QStandardItem(p->goods_type));
        strcpy(cur_cata.stor_code,p->stor_code);
        strcpy(cur_cata.goods_code,p->goods_code);
        strcpy(cur_cata.goods_name,p->goods_name);
        strcpy(cur_cata.goods_type,p->goods_type);
        strcpy(cur_cata.num_units,p->num_units);
        strcpy(cur_cata.factory,p->factory);
        reco_fileout(reco_file.toLatin1().data());
        int cur_num=0;
        q=cur_cata.head_reco;
        while(q){
            if(q->flag=='1')
                cur_num+=q->op_amount;
            else cur_num-=q->op_amount;;
            q=q->next_reco;
        }
        model->setItem(i,3,new QStandardItem(QString::number(cur_num)));
        model->setItem(i,4,new QStandardItem(p->factory));
        p=p->next_cata;
        i++;
    }
    */
}

void op_interface::refresh_table_cata()
{
    /*
    QStandardItemModel *cata_model=new QStandardItemModel();
    cata_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("商品编号")));
    cata_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品名称")));
    cata_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("商品类型")));
    cata_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("数量单位")));
    cata_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("厂商名称")));
    ui->info_goods->setModel(cata_model);
    Catalogue *p;
    int i=0;
    p=cur_stor.head_cata;
    while(p){
        cata_model->setItem(i,0,new QStandardItem(p->goods_code));
        cata_model->setItem(i,1,new QStandardItem(p->goods_name));
        cata_model->setItem(i,2,new QStandardItem(p->goods_type));
        cata_model->setItem(i,3,new QStandardItem(p->num_units));
        cata_model->setItem(i,4,new QStandardItem(p->factory));
        p=p->next_cata;
        i++;
    }
    */
}

void op_interface::refresh_combox_cata()
{
    /*
    ui->goods_code->clear();
    ui->goods_code->addItem("——请选择——");
    ui->goods_code->addItem("点我进行添加");
    ui->op_goods_code->clear();
    ui->op_goods_code->addItem("——请选择——");
    ui->stat_goods_code->clear();
    ui->op_num->clear();
    Catalogue *p;
    cata_fileout(cata_file.toLatin1().data());
    p=cur_stor.head_cata;
    while(p){
        ui->goods_code->addItem(p->goods_code);
        ui->op_goods_code->addItem(p->goods_code);
        ui->stat_goods_code->addItem(p->goods_code);
        p=p->next_cata;
    }
    */
}

void op_interface::cata_display()
{
    /*
    if(ui->goods_code->currentIndex()==1){
        ui->goods_code->setEditable(1);
        ui->goods_name->clear();
        ui->goods_type->clear();
        ui->num_units->clear();
        ui->factory->clear();
    }
    else{
        ui->goods_code->setEditable(0);
        Catalogue *p;
        p=cur_stor.head_cata;
        while(p){
            if(strcmp(p->goods_code,ui->goods_code->currentText().toLatin1().data())==0){
                ui->goods_name->setText(p->goods_name);
                ui->goods_type->setText(p->goods_type);
                ui->num_units->setText(p->num_units);
                ui->factory->setText(p->factory);
                break;
            }
            p=p->next_cata;
        }
    }
    */
}

void op_interface::record_select()
{
    /*
    Catalogue *p;
    ui->op_type->setCurrentIndex(0);
    ui->op_amount->clear();
    ui->date->clear();
    p=cur_stor.head_cata;
    while(p){
        if(strcmp(p->goods_code,ui->op_goods_code->currentText().toLatin1().data())==0){
           strcpy(cur_cata.stor_code,p->stor_code);
           strcpy(cur_cata.goods_code,p->goods_code);
           strcpy(cur_cata.goods_name,p->goods_name);
           strcpy(cur_cata.goods_type,p->goods_type);
           strcpy(cur_cata.num_units,p->num_units);
           strcpy(cur_cata.factory,p->factory);
           break;
        }
        p=p->next_cata;
    }
    reco_fileout(reco_file.toLatin1().data());
    ui->op_num->clear();
    ui->op_num->addItem("——请选择——");
    ui->op_num->addItem("点我进行添加");
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("流水号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品编号")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("处理类型")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("处理数量")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("处理时间")));
    ui->info_record->setModel(model);
    Record *q;
    QString str;
    int i=0;
    q=cur_cata.head_reco;
    while(q){
        ui->op_num->addItem(q->reco_code);
        if(q->flag=='1')
            str="入库";
        else str="出库";
        model->setItem(i,0,new QStandardItem(q->reco_code));
        model->setItem(i,1,new QStandardItem(q->goods_code));
        model->setItem(i,2,new QStandardItem(str));
        model->setItem(i,3,new QStandardItem(QString::number(q->op_amount)));
        model->setItem(i,4,new QStandardItem(q->date));
        q=q->next_reco;
        i++;
    }
    */
}

void op_interface::record_display()
{
    /*
    if(ui->op_num->currentIndex()==1){
        ui->op_num->setEditable(1);
    }
    else{
        ui->op_num->setEditable(0);
        Record *p;
        p=cur_cata.head_reco;
        while(p){
            if(strcmp(p->reco_code,ui->op_num->currentText().toLatin1().data())==0){
                if(p->flag=='1')
                    ui->op_type->setCurrentIndex(1);
                else ui->op_type->setCurrentIndex(2);
                ui->op_amount->setText(QString::number(p->op_amount));
                ui->date->setText(p->date);
                break;
            }
            p=p->next_reco;
        }
    }
    */
}
//*******操作员修改信息**********
void op_interface::on_op_info_change_clicked()
{

}

void op_interface::on_op_passwd_change_clicked()
{

}

//********仓库修改信息***********
void op_interface::on_stor_alter_clicked()
{

}

//**********商品修改信息**********
void op_interface::on_goods_add_clicked()
{

}

void op_interface::on_goods_delete_clicked()
{

}

void op_interface::on_goods_alter_clicked()
{

}

//**********记录修改信息***********
void op_interface::on_record_add_clicked()
{

}

void op_interface::on_record_delete_clicked()
{

}

void op_interface::on_record_alter_clicked()
{

}

//*********查询*************
void op_interface::on_select_clicked()
{

}

void op_interface::on_exit_clicked()
{
    this->close();
    parentWidget()->show();
}
