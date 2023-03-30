#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "linkedList.h"

char* login(void);                                 //��¼
Status check(char*account,char* password);          //����˺������Ƿ���ȷ
void readfile(void);                                //���ļ���ȡ�˺����룬��������
void signup(void);                                  //ע��
void savetofile(char* a,char* p,char* c);           //���˺���������ļ�
Status check_signup(char*account);                  //���ע���˺��Ƿ��Ѵ���
void change_password(void);                         //�޸�����
Status DeleteList(LinkedList *L,char* account);     //�����˻����ƣ�Ѱ�������н�㲢ɾ��
Status deleteFile(char* account);                   //ɾ���ļ�
void home(void);                                
void find_password(void);                           
char* printpassword(char* account,char* name);      //��ӡ����



#endif