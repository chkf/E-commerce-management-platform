#ifndef APP_H
#define APP_H

#include "linkedlist.h" 


//函数声明
void read_bills(void);                                          //读取账单文件
Status search_goods(char* account);                             //搜索商品
void add_goods(char *name, int price, int number, char *owner); //添加商品到文件，被函数调用的函数
void read_goods(void);                                          //读取商品文件到链表
void add_goods_info(void);                                      //添加商品到文件和链表，调用了add_goods函数
void buy_goods(char *name, char *address,char*account);         //购买商品
G_LNode *find_goods_node(char *name);                           //查找商品结点，被函数调用的函数
void delete_goods(char* account);                               //删除商品
void update_goods_info(void);                                   //更新商品信息，链表更新到文件
void submit_goods(char* account);                               //提交商品
void change_goods_price(char *name, char *owner, int price);    //修改商品价格，被函数调用的函数
void change_goods_number(char *name, char *owner, int number);  //修改商品数量，被函数调用的函数
void print_bill(char *account);                                 //打印已卖出商品
void print_bill_buyer(char *account);                           //打印已买到商品
int count(void);                                                //统计全平台订单数量
void add_bill(char *name, char *address, char *buyer, char *seller, int number);    //添加订单到链表，被函数调用的函数
void apply_recommendation(char* account);                       //申请推荐
void recommended_goods(char* account);                          //浏览推荐商品
void print_goods(char *owner);                                  //打印账号所有在售商品
void goods_info_change(char* account);                          //更新商品信息，由用户修改信息，链表更新到文件


#endif
