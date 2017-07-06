#ifndef SU_OPER_H
#define SU_OPER_H

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
class su_oper;
}

class su_oper : public QMainWindow,public myclass
{
    Q_OBJECT

public:
    explicit su_oper(QWidget *parent = 0);
    void fresh_stor();
    void fresh_oper();
    void fresh_combox();
    ~su_oper();

private slots:
    void on_tabWidget_tabBarClicked(int index);
    void stor_display();

    void on_stor_add_clicked();

    void on_stor_dele_clicked();

    void on_op_add_clicked();

    void on_op_dele_clicked();

private:
    Ui::su_oper *ui;
    QMessageBox *box2;
};

#endif // SU_OPER_H
