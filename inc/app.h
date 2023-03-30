#ifndef APP_H
#define APP_H

#include "linkedlist.h" 


//º¯ÊýÉùÃ÷
void read_bills(void);
Status search_goods(char* account);
void add_goods(char *name, int price, int number, char *owner);
void read_goods(void);
void add_goods_info(void);
G_LNode *find_goods(char *name);
void delete_goods(char *name);
void modify_goods(char *name);
void buy_goods(char *name, char *address,char*account);
void check_order(char *name);
void check_goods(char *name);
G_LNode *find_goods_node(char *name);
void delete_zero_goods(void);
void update_goods_info(void);
void submit_goods(char* account);




#endif
