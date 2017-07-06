#ifndef OP_INTERFACE_H
#define OP_INTERFACE_H

#include <QMainWindow>
#include<QMessageBox>
#include <QStandardItemModel>
#include "c_kernel.h"
extern op_info *head_oper;
extern Storage *head_all;
extern QString oper_file;
extern QString stor_file;
extern QString cata_file;
extern QString reco_file;
extern op_info   *cur_oper;
extern Storage   *cur_stor;

namespace Ui {
class op_interface;
}

class op_interface : public QMainWindow,public myclass
{
    Q_OBJECT

public:
    explicit op_interface(QWidget *parent = 0);
    void refresh_baseinfo();
    void refresh_combox();
    void refresh_table_cata();
    void refresh_table_count();
    ~op_interface();

private slots:
    void cata_display();
    void record_display();
    void record_select();
    void count_display();
    void on_op_info_change_clicked();

    void on_op_passwd_change_clicked();

    void on_stor_alter_clicked();

    void on_goods_add_clicked();

    void on_goods_delete_clicked();

    void on_goods_alter_clicked();

    void on_record_add_clicked();

    void on_record_delete_clicked();

    void on_record_alter_clicked();

    void on_exit_clicked();

private:
    Ui::op_interface *ui;
    QMessageBox *box1;
};

#endif // OP_INTERFACE_H
