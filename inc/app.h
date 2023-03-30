#ifndef APP_H
#define APP_H

#include "linkedlist.h" 


//��������
void read_bills(void);                                          //��ȡ�˵��ļ�
Status search_goods(char* account);                             //������Ʒ
void add_goods(char *name, int price, int number, char *owner); //�����Ʒ���ļ������������õĺ���
void read_goods(void);                                          //��ȡ��Ʒ�ļ�������
void add_goods_info(void);                                      //�����Ʒ���ļ�������������add_goods����
void buy_goods(char *name, char *address,char*account);         //������Ʒ
G_LNode *find_goods_node(char *name);                           //������Ʒ��㣬���������õĺ���
void delete_goods(char* account);                               //ɾ����Ʒ
void update_goods_info(void);                                   //������Ʒ��Ϣ��������µ��ļ�
void submit_goods(char* account);                               //�ύ��Ʒ
void change_goods_price(char *name, char *owner, int price);    //�޸���Ʒ�۸񣬱��������õĺ���
void change_goods_number(char *name, char *owner, int number);  //�޸���Ʒ���������������õĺ���
void print_bill(char *account);                                 //��ӡ��������Ʒ
void print_bill_buyer(char *account);                           //��ӡ������Ʒ
int count(void);                                                //ͳ��ȫƽ̨��������
void add_bill(char *name, char *address, char *buyer, char *seller, int number);    //��Ӷ������������������õĺ���
void apply_recommendation(char* account);                       //�����Ƽ�
void recommended_goods(char* account);                          //����Ƽ���Ʒ
void print_goods(char *owner);                                  //��ӡ�˺�����������Ʒ
void goods_info_change(char* account);                          //������Ʒ��Ϣ�����û��޸���Ϣ��������µ��ļ�


#endif
