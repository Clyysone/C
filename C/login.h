#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QMessageBox>
#include"op_interface.h"
#include"su_oper.h"
#include"c_kernel.h"
extern op_info *head_oper;
extern Storage *head_all;
extern QString oper_file;
extern QString stor_file;
extern QString cata_file;
extern QString reco_file;
extern op_info   *cur_oper;
extern Storage   *cur_stor;
extern Catalogue  * cur_cata;
extern Record   *cur_reco;

namespace Ui {
class login;
}

class login : public QMainWindow,public myclass
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_exit_clicked();
    void on_start_clicked();

private:
    Ui::login *ui;
    QMessageBox *mybox;
    su_oper *su;
     op_interface *oper;
};

#endif // LOGIN_H
