#ifndef C_KERNEL_H
#define C_KERNEL_H
#include<QMainWindow>
//操作员信息结构体
 struct op_info{
    char oper_code[20];     //操作员编码
    char oper_pwd[20];       //操作员密码
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
    char oper_code[20];     //出入库的操作员编号
    char stor_code[20];     //出入仓库编号
    char cata_code[20];     //出入库商品编号
    char reco_code[20];     //流水号
    char reco_type;     //出入库类型
    char reco_date[20];     //出入库时间
    int reco_sum;       //出入库数量
    struct Record *next_reco;       //指向下一个出入库记录
};

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

class myclass{

public:
    //**********文件和链表转换***********
    //取出操作员信息返回头指针
    bool  fileout_oper()
    {
        FILE *oper_f=fopen(oper_file.toLatin1().data(),"r");
        if(oper_f==NULL){
            printf("open fail:%s",oper_file.toLatin1().data());
            return 0;
        }
        head_oper=(op_info *)malloc(sizeof(op_info));
        op_info *p,*q;
        op_info cur;
        q=p=head_oper;
        while(fscanf(oper_f,"%s %s %s %s",cur.oper_code,cur.oper_pwd,cur.oper_name,cur.stor_code)!=EOF){
            strcpy(p->oper_code,cur.oper_code);
            strcpy(p->oper_pwd,cur.oper_pwd);
            strcpy(p->oper_name,cur.oper_name);
            strcpy(p->stor_code,cur.stor_code);
            q=p;
            p->next_oper=(op_info *)malloc(sizeof(op_info));
            p=p->next_oper;
        }
        q->next_oper=NULL;
         fclose(oper_f);
        return 1;
    }

    //取出所有信息返回三重链表头指针
    bool fileout_all()
    {
        FILE *stor_f=fopen(stor_file.toLatin1().data(),"r");
        if(stor_f==NULL){
            printf("open fail!");
            return 0;
        }
        head_all=(Storage *)malloc(sizeof(Storage));
        Storage *p_stor,*q_stor;
        Storage cur_stor;
        q_stor=p_stor=head_all;
        while(fscanf(stor_f,"%s %s %s %s",cur_stor.stor_code,cur_stor.stor_name,cur_stor.stor_loc,cur_stor.stor_phon)!=EOF){
            strcpy(p_stor->stor_code,cur_stor.stor_code);
            strcpy(p_stor->stor_name,cur_stor.stor_name);
            strcpy(p_stor->stor_loc,cur_stor.stor_loc);
            strcpy(p_stor->stor_phon,cur_stor.stor_phon);
            q_stor=p_stor;
            p_stor->next_stor=(Storage *)malloc(sizeof(Storage));
            p_stor=p_stor->next_stor;
        }
        q_stor->next_stor=NULL;
        fclose(stor_f);
        //第一次遍历,变为二重链表
        p_stor=head_all;
        while(p_stor){
            Catalogue *p_cata,*q_cata;
            Catalogue cur_cata;
            int flag=0;
            p_stor->head_cata=(Catalogue *)malloc(sizeof(Catalogue));
            q_cata=p_cata=p_stor->head_cata;
            FILE *cata_f=fopen(cata_file.toLatin1().data(),"r");
            while(fscanf(cata_f,"%s %s %s %s %s %s",cur_cata.stor_code,cur_cata.cata_code,cur_cata.cata_name,
                         cur_cata.cata_type,cur_cata.cata_unit,cur_cata.cata_comp)!=EOF){
                if(strcmp(cur_cata.stor_code,p_stor->stor_code)==0){
                    flag=1;
                    strcpy(p_cata->stor_code,cur_cata.stor_code);
                    strcpy(p_cata->cata_code,cur_cata.cata_code);
                    strcpy(p_cata->cata_name,cur_cata.cata_name);
                    strcpy(p_cata->cata_unit,cur_cata.cata_unit);
                    strcpy(p_cata->cata_type,cur_cata.cata_type);
                    strcpy(p_cata->cata_comp,cur_cata.cata_comp);
                    q_cata=p_cata;
                    p_cata->next_cata=(Catalogue *)malloc(sizeof(Catalogue));
                    p_cata=p_cata->next_cata;
                }
            }
            q_cata->next_cata=NULL;
            if(flag==0){
                p_stor->head_cata=NULL;
            }
            p_stor=p_stor->next_stor;
            fclose(cata_f);
        }
        //第二次遍历,变为三重链表
        p_stor=head_all;
        while(p_stor){
            Catalogue *p_cata;
            p_cata=p_stor->head_cata;
            while(p_cata){
                Record *p_reco,*q_reco;
                Record cur_reco;
                int flag=0;
                p_cata->head_reco=(Record *)malloc(sizeof(Record));
                q_reco=p_reco=p_cata->head_reco;
                FILE *reco_f=fopen(reco_file.toLatin1().data(),"r");
                while(fscanf(reco_f,"%s %s %s %s %c %s %d",cur_reco.oper_code,cur_reco.stor_code,cur_reco.cata_code,
                             cur_reco.reco_code,&cur_reco.reco_type,cur_reco.reco_date,&cur_reco.reco_sum)!=EOF){
                    if(strcmp(cur_reco.stor_code,p_cata->stor_code)==0&&strcmp(cur_reco.cata_code,p_cata->cata_code)==0){
                        flag=1;
                        strcpy(p_reco->stor_code,cur_reco.stor_code);
                        strcpy(p_reco->oper_code,cur_reco.oper_code);
                        strcpy(p_reco->cata_code,cur_reco.cata_code);
                        strcpy(p_reco->reco_code,cur_reco.reco_code);
                        p_reco->reco_type=cur_reco.reco_type;
                        strcpy(p_reco->reco_date,cur_reco.reco_date);
                        p_reco->reco_sum=cur_reco.reco_sum;
                        q_reco=p_reco;
                        p_reco->next_reco=(Record *)malloc(sizeof(Record));
                        p_reco=p_reco->next_reco;
                    }
                }
                q_reco->next_reco=NULL;
                if(flag==0){
                    p_cata->head_reco=NULL;
                }
                p_cata=p_cata->next_cata;
                fclose(reco_f);
            }
             p_stor=p_stor->next_stor;
        }
        return 1;
    }

    //将操作员信息写回文件
    bool filein_oper()
    {
        FILE *oper_f=fopen(oper_file.toLatin1().data(),"w");
        if(oper_f==NULL){
            printf("open fail:%s",oper_file.toLatin1().data());
            return 0;
        }
        op_info *p;
        p=head_oper;
        while(p){
            fprintf(oper_f,"%s %s %s %s",p->oper_code,p->oper_pwd,p->oper_name,p->stor_code);
            p=p->next_oper;
        }
        fclose(oper_f);
        return 1;
    }

    //将所有信息写回文件
    bool filein_all()
    {
        FILE *stor_f=fopen(stor_file.toLatin1().data(),"w");
        FILE *cata_f=fopen(cata_file.toLatin1().data(),"w");
        FILE *reco_f=fopen(reco_file.toLatin1().data(),"w");
        if(stor_f==NULL||cata_f==NULL||reco_f==NULL){
            printf("open fail!");
            return 0;
        }
        Storage *p_stor;
        Catalogue *p_cata;
        Record *p_reco;
        p_stor=head_all;
        while(p_stor){
            fprintf(stor_f,"%s %s %s %s",p_stor->stor_code,p_stor->stor_name,p_stor->stor_loc,p_stor->stor_phon);
            p_cata=p_stor->head_cata;
            while(p_cata){
                fprintf(cata_f,"%s %s %s %s %s %s",p_cata->stor_code,p_cata->cata_code,p_cata->cata_name,
                       p_cata->cata_type,p_cata->cata_unit,p_cata->cata_comp);
                p_reco=p_cata->head_reco;
                while(p_reco){
                    fprintf(reco_f,"%s %s %s %s %c %s %d",p_reco->oper_code,p_reco->stor_code,p_reco->cata_code,
                            p_reco->reco_code,p_reco->reco_type,p_reco->reco_date,p_reco->reco_sum);
                    p_reco=p_reco->next_reco;
                }
                p_cata=p_cata->next_cata;
            }
            p_stor=p_stor->next_stor;
        }
        fclose(stor_f);
        fclose(cata_f);
        fclose(reco_f);
        return 1;
    }

    //*******************操作员链表相关***************
    //添加操作员节点
    bool oper_add_node(op_info add_struc)
    {
        op_info *p;
        p=head_oper->next_oper;
        while(p->next_oper){
            p=p->next_oper;
        }
        p->next_oper=(op_info *)malloc(sizeof(op_info));
        p=p->next_oper;
        strcpy(p->oper_code,add_struc.oper_code);
        strcpy(p->oper_name,add_struc.oper_name);
        strcpy(p->oper_pwd,add_struc.oper_pwd);
        strcpy(p->stor_code,add_struc.stor_code);
        p->next_oper=NULL;
        return 1;
    }

    //删除操作员节点
    bool oper_dele_node(op_info dele_struc)
    {
        op_info *p,*q;
        p=q=head_oper;
        if(strcmp(p->oper_code,dele_struc.oper_code)==0){
            head_oper=head_oper->next_oper;
            return 1;
        }
        else p=p->next_oper;
        while(p){
            if(strcmp(p->oper_code,dele_struc.oper_code)==0){
                q->next_oper=p->next_oper;
            }
            q=p;
            p=p->next_oper;
        }
        return 1;

    }

    //修改操作员节点
    bool oper_alter_node(op_info alter_struc)
    {
        op_info *p;
        p=head_oper->next_oper;
        while(p){
            if(strcmp(p->oper_code,alter_struc.oper_code)==0){
                strcpy(p->oper_name,alter_struc.oper_name);
                strcpy(p->oper_pwd,alter_struc.oper_pwd);
            }
            p=p->next_oper;
        }
        return 1;

    }

    //***************仓库链表相关******************
    //添加仓库节点
    bool stor_add_node(Storage add_struc)
    {
        return 1;

    }

    //删除仓库节点
    bool stor_dele_node(Storage dele_struc)
    {
        return 1;

    }

    //修改仓库节点
    bool stor_alter_node(Storage alter_struc)
    {
        return 1;

    }

    //***************商品链表相关***********
    //添加商品节点
    bool cata_add_node(Catalogue add_struc)
    {
        Catalogue *p;
        p=cur_stor->head_cata;
        while(p->next_cata){
            p=p->next_cata;
        }
        p->next_cata=(Catalogue *)malloc(sizeof(Catalogue));
        p=p->next_cata;
        strcpy(p->stor_code,add_struc.stor_code);
        strcpy(p->cata_code,add_struc.cata_code);
        strcpy(p->cata_name,add_struc.cata_name);
        strcpy(p->cata_type,add_struc.cata_type);
        strcpy(p->cata_unit,add_struc.cata_unit);
        strcpy(p->cata_comp,add_struc.cata_comp);
        p->next_cata=NULL;
        return 1;

    }

    //删除商品节点
    bool cata_dele_node(Catalogue dele_struc)
    {
        Catalogue *p,*q;
        p=q=cur_stor->head_cata;
        if(strcmp(p->cata_code,dele_struc.cata_code)==0){
            cur_stor->head_cata=p->next_cata;
            return 1;
        }
        else p=p->next_cata;
        while(p){
            if(strcmp(p->cata_code,dele_struc.cata_code)==0){
                q->next_cata=p->next_cata;
            }
            q=p;
            p=p->next_cata;
        }
        return 1;

    }

    //修改商品节点
    bool cata_alter_node(Catalogue alter_struc)
    {
        Catalogue *p;
        p=cur_stor->head_cata;
        while(p){
            if(strcmp(p->cata_code,alter_struc.cata_code)==0){
                strcpy(p->cata_name,alter_struc.cata_name);
                strcpy(p->cata_type,alter_struc.cata_type);
                strcpy(p->cata_unit,alter_struc.cata_unit);
                strcpy(p->cata_comp,alter_struc.cata_comp);
            }
            p=p->next_cata;
        }
        return 1;
    }

    //*******************记录链表相关*****************
    //添加记录节点
    bool reco_add_node(Record add_struc)
    {
        return 1;

    }

    //删除记录节点
    bool reco_dele_node(Record dele_struc)
    {
        return 1;

    }

    //修改记录节点
    bool reco_alter_node(Record alter_struc)
    {
        return 1;

    }
    //统计
     int cata_count(Catalogue *p_count)
    {
         QString str="入库";
        Catalogue *p_cata;
        int cur_num=0;
        p_cata=cur_stor->head_cata;
        while(p_cata){
            if(strcmp(p_cata->cata_code,p_count->cata_code)==0){
                Record *p_reco;
                p_reco=p_cata->head_reco;
                while(p_reco){
                    if(p_reco->reco_type=='1')
                        cur_num=cur_num+p_reco->reco_sum;
                    if(p_reco->reco_type=='0')
                        cur_num=cur_num-p_reco->reco_sum;
                    p_reco=p_reco->next_reco;
                }
            }
            p_cata=p_cata->next_cata;
        }
        return cur_num;

    }
};


#endif // C_KERNEL_H
