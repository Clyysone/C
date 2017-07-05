#ifndef C_KERNEL_H
#define C_KERNEL_H
#include<QMainWindow>
//操作员信息结构体
 struct op_info{
    char oper_code[20];     //操作员编码
    char oper_passwd[20];       //操作员密码
    char oper_name[20];     //操作员姓名
    char stor_code[20];     //操作员所属仓库编号
    struct op_info *next_oper;
};
//仓库信息结构体
struct Storage{
    char stor_code[20];     //仓库编号
    char stor_name[20];     //仓库名称
    char stor_loc[20];      //仓库位置
    char stor_phon[20];      //仓库电话
    struct Storage *next_stor;
    struct Catalogue *head_cata;        //商品信息头指针
};

//商品信息结构体
 struct  Catalogue{
    char stor_code[20];     //所属仓库
    char cata_code[20];        //商品编码
    char cata_name[20];        //商品名称
    char cata_type[20];        //商品类型
    char  cata_unit[20];        //商品数量单位
    char cata_comp[20];       //商品厂商
    struct Catalogue *next_cata;        //指向下一个商品信息
    struct Record *head_reco;           //指向出入记录信息头
};

//商品出入记录结构体
struct Record{
    char stor_code[20];     //出入仓库编号
    char oper_code[20];     //出入库的操作员编号
    char cata_code[20];     //出入库商品编号
    char reco_code[20];     //流水号
    char reco_type[20];     //出入库类型
    char reoc_date[20];     //出入库时间
    int reco_sum;       //出入库数量
    struct Record *next_reco;       //指向下一个出入库记录
};

class myclass{

public:
    //**********文件和链表转换***********
    //取出操作员信息返回头指针
    op_info *fileout_oper(char *oper_filename)
    {

    }

    //取出所有信息返回三重链表头指针
    Storage *fileout_all(char *stor_filename,char *cata_filename,char *reco_filename)
    {

    }

    //将操作员信息写回文件
    bool *filein_oper(char *oper_filename)
    {

    }

    //将所有信息写回文件
    bool filein_all(char *stor_filename,char *cata_filename,char *reco_filename)
    {

    }

    //*******************操作员链表相关***************
    //添加操作员节点
    bool oper_add_node()
    {

    }

    //删除操作员节点
    bool oper_dele_node()
    {

    }

    //修改操作员节点
    bool oper_alter_node()
    {

    }

    //***************仓库链表相关******************
    //添加仓库节点
    bool stor_add_node()
    {

    }

    //删除仓库节点
    bool stor_dele_node()
    {

    }

    //修改仓库节点
    bool stor_alter_node()
    {

    }

    //***************商品链表相关***********
    //添加商品节点
    bool cata_add_node()
    {

    }

    //删除商品节点
    bool cata_dele_node()
    {

    }

    //修改商品节点
    bool cata_alter_node()
    {

    }

    //*******************记录链表相关*****************
    //添加记录节点
    bool reco_add_node()
    {

    }

    //删除记录节点
    bool reco_dele_node()
    {

    }

    //修改记录节点
    bool reco_alter_node()
    {

    }
    //统计
};


#endif // C_KERNEL_H
