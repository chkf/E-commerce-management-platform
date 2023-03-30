#ifndef M_ACCOUNT_H
#define M_ACCOUNT_H

#include "linkedList.h"

char* m_login(void);                                  //登录
Status m_check(char*account,char* password);          //检查账号密码是否正确
void m_readfile(void);                                //从文件读取账号密码，存入链表
void m_signup(void);                                  //注册
void m_savetofile(char* a,char* p,char* c);           //将账号密码存入文件
Status m_check_signup(char*account);                  //检查注册账号是否已存在
void m_change_password(void);                         //修改密码
Status m_DeleteList(LinkedList *L,char* account);     //传入账户名称，寻找链表中结点并删除
Status m_deleteFile(char* account);                   //删除文件
void home(void);                                      //主界面
char* m_printpassword(char* account,char* name);      //打印密码
void m_find_password(void);


#endif