#仓库商品出入库管理系统
##1. 系统功能
  多仓库商品出入库的记录、查询和统计  
1. 仓库信息（增删改）  
2. 商品目录（增删改）  
3. 出入库记录（增删改）  
4. 查询与统计（增删改）  
5. 操作员信息（增删改）  

##2. 系统数据
以文件形式保存，分别有操作员信息、仓库信息、商品信息、记录信息 共4种
###（1）操作员信息(op_info)
- 操作员编号  ——oper_code char[20]
- 操作员姓名  ——oper_name char[20]
- 所属仓库编号  ——stor_code char[20]
- 操作员密码  ——oper_pwd char[20]

###（2）仓库信息(storage)
- 仓库编号  ——stor_code char[20]
- 仓库名称  ——stor_name char[20]
- 仓库地点  ——stor_loc char[20]
- 仓库电话  ——stor_pho char[20]

###（3）商品信息(catalogue)
- 商品编号  ——cata_code char[20]
- 商品名称  ——cata_name char[20]
- 商品类别  ——cata_type char[20]
- 数量单位  ——cata_unit char[20]
- 生产厂商  ——cata_comp char[20]

###（4）出入记录(record)
- 操作流水号  ——reco_code char[20]
- 所属仓库编号  ——stor_code char[20]
- 商品编号  ——cata_code char[20]
- 出入类型  ——reco_type char[20]
- 处理数量  ——reco_sum int
- 操作员编号	——oper_code [20]

##3. 详细设计
将所有信息从文件中取出  
1. 取出所有仓库信息，以单链表保存  
2. 取出商品信息，附在单链表上形成二重链表   
3. 取出记录信息，附在对应商品信息上，形成三重链表  
4. 对链表进行操作  
5. 增删改在链表上进行操作  
6. 最后结束后在写回文件中