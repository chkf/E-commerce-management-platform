#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "linkedList.h"

char* login(void);                                 //登录
Status check(char*account,char* password);          //检查账号密码是否正确
void readfile(void);                                //从文件读取账号密码，存入链表
void signup(void);                                  //注册
void savetofile(char* a,char* p,char* c);           //将账号密码存入文件
Status check_signup(char*account);                  //检查注册账号是否已存在
void change_password(void);                         //修改密码
Status DeleteList(LinkedList *L,char* account);     //传入账户名称，寻找链表中结点并删除
Status deleteFile(char* account);                   //删除文件
void home(void);                                
void find_password(void);                           
char* printpassword(char* account,char* name);      //打印密码



#endif