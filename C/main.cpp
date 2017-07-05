#include "login.h"
#include <QApplication>
#include"c_kernel.h"

op_info *head_oper;
Storage *head_all;
QString oper_file="D:\\Study-file\\C\\C\\op_info.txt";
QString stor_file="D:\\Study-file\\C\\C\\storage.txt";
QString cata_file="D:\\Study-file\\C\\C\\catalogue.txt";
QString reco_file="D:\\Study-file\\C\\C\\record.txt";
op_info   *cur_op_info;
Storage   *cur_stor;
Catalogue  * cur_cata;
Record   *cur_reco;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}
