#include "op_interface.h"
#include "ui_op_interface.h"

op_interface::op_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::op_interface)
{
    ui->setupUi(this);
    box1=new QMessageBox(this);
    Storage *p;
    p=head_all;
    while(p){
        if(strcmp(p->stor_code,cur_oper->stor_code)==0){
            cur_stor=p;
        }
        p=p->next_stor;
    }
    box1->show();
    box1->setText("登录成功!当前仓库为："+QString(QLatin1String(cur_stor->stor_code)));
    ui->op_code->setText(cur_oper->oper_code);
    ui->op_name->setText(cur_oper->oper_name);
    ui->op_stor_code->setText(cur_oper->stor_code);
    ui->stor_name->setText(cur_stor->stor_name);
    ui->stor_code->setText(cur_stor->stor_code);
    ui->phone_num->setText(cur_stor->stor_phon);
    ui->locate_2->setText(cur_stor->stor_loc);
    refresh_combox_cata();  //商品下拉菜单加载，添加删除修改后调用
    refresh_table_cata(); //商品表的加载
    refresh_table_count();  //统计表的加载
    connect(ui->goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(cata_display())); //商品文本框显示
    connect(ui->op_goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(record_select())); //记录流水号下拉菜单加载
    connect(ui->op_num,SIGNAL(currentIndexChanged(int)),this,SLOT(record_display())); //记录文本框显示
    connect(ui->stat_goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(count_display()));
}

op_interface::~op_interface()
{
    delete ui;
}
//*******刷新操作*********
void op_interface::refresh_combox_cata()
{
    ui->goods_code->clear();
    ui->op_goods_code->clear();
    ui->stat_goods_code->clear();
    ui->op_num->clear();
    ui->goods_code->addItem("——请选择——");
    ui->goods_code->addItem("点我进行添加");
    ui->op_goods_code->addItem("——请选择——");
    ui->stat_goods_code->addItem("——请选择——");
    Catalogue *p;
    p=cur_stor->head_cata;
    while(p){
        ui->goods_code->addItem(p->cata_code);
        ui->op_goods_code->addItem(p->cata_code);
        ui->stat_goods_code->addItem(p->cata_code);
        p=p->next_cata;
    }
}
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

void op_interface::cata_display()
{
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
        p=cur_stor->head_cata;
        while(p){
            if(strcmp(p->cata_code,ui->goods_code->currentText().toLatin1().data())==0){
                ui->goods_name->setText(p->cata_name);
                ui->goods_type->setText(p->cata_type);
                ui->num_units->setText(p->cata_unit);
                ui->factory->setText(p->cata_comp);
                break;
            }
            p=p->next_cata;
        }
    }
}

void op_interface::record_select()
{
    Catalogue *p;
    ui->op_type->setCurrentIndex(0);
    ui->op_amount->clear();
    ui->date->clear();
    p=cur_stor->head_cata;
    while(p){
        if(strcmp(p->cata_code,ui->op_goods_code->currentText().toLatin1().data())==0){
           cur_cata=p;
           break;
        }
        p=p->next_cata;
    }
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("流水号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品编号")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("处理类型")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("处理数量")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("处理时间")));
    ui->info_record->setModel(model);
    Record *q;
    int i=0;
    q=cur_cata->head_reco;
    ui->op_num->clear();
    ui->op_num->addItem("——请选择——");
    ui->op_num->addItem("点我进行添加");
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
}

void op_interface::record_display()
{
    if(ui->op_num->currentIndex()==1){
        ui->op_num->setEditable(1);
    }
    else{
        ui->op_num->setEditable(0);
        Record *p;
        p=cur_cata->head_reco;
        while(p){
            if(strcmp(p->reco_code,ui->op_num->currentText().toLatin1().data())==0){
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
}

void op_interface::count_display()
{
    Catalogue *p;
    QString str=ui->stat_goods_code->currentText();
    p=cur_stor->head_cata;
    while(p){
        if(strcmp(p->cata_code,str.toLatin1().data())==0){
            ui->stat_goods_name->setText(p->cata_name);
            ui->stat_goods_type->setText(p->cata_type);
            ui->stat_num_units->setText(p->cata_unit);
            ui->stat_goods_amount->setText(QString::number(cata_count(p)));
        }
         p=p->next_cata;
    }
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
