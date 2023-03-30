#ifndef M_ACCOUNT_H
#define M_ACCOUNT_H

#include "linkedList.h"

char* m_login(void);                                  //��¼
Status m_check(char*account,char* password);          //����˺������Ƿ���ȷ
void m_readfile(void);                                //���ļ���ȡ�˺����룬��������
void m_signup(void);                                  //ע��
void m_savetofile(char* a,char* p,char* c);           //���˺���������ļ�
Status m_check_signup(char*account);                  //���ע���˺��Ƿ��Ѵ���
void m_change_password(void);                         //�޸�����
Status m_DeleteList(LinkedList *L,char* account);     //�����˻����ƣ�Ѱ�������н�㲢ɾ��
Status m_deleteFile(char* account);                   //ɾ���ļ�
void home(void);                                      //������
char* m_printpassword(char* account,char* name);      //��ӡ����
void m_find_password(void);


#endif