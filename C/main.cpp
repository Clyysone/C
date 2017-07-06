#include "login.h"
#include <QApplication>
#include"c_kernel.h"

QString oper_file="D:\\Study-file\\C\\C\\op_info.txt"; //文件位置
QString stor_file="D:\\Study-file\\C\\C\\storage.txt";
QString cata_file="D:\\Study-file\\C\\C\\catalogue.txt";
QString reco_file="D:\\Study-file\\C\\C\\record.txt";
op_info *head_oper; //整个程序运行期间保持不变
Storage *head_all;
op_info   *cur_oper; //一旦登录即不会变
Storage   *cur_stor;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}
