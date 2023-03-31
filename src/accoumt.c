#include "account.h"
#include "linkedList.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "main.h"

extern LinkedList list;

//从txt文件中读取账号密码，转换为字符串后，存入链表
void readfile(void)
{
    USER* user;
    LNode* q;
    FILE *fp;
    fp = fopen("..\\data\\account.txt","r");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //分配空间
    c=(char*)malloc(20*sizeof(char));
    while(fscanf(fp,"account:%s\npassword:%s\nname:%s\n\n",a,p,c)!=EOF)
    {
        q = (LNode*)malloc(sizeof(LNode));
        user = (USER*)malloc(sizeof(USER));
        user->account=(char*)malloc(20*sizeof(char));
        user->password=(char*)malloc(20*sizeof(char));
        user->name=(char*)malloc(20*sizeof(char));
        strcpy(user->account,a);                        //将读取的账号密码存入结点
        strcpy(user->password,p);
        strcpy(user->name,c);
        q->user = user;
        q->next = NULL;
        InsertList(list,q);
    }
    fclose(fp);
}


//向文件中写入账号密码
void savetofile(char* a,char* p,char* c)
{
    FILE *fp;
    fp = fopen("..\\data\\account.txt","a");
    fprintf(fp,"account:%s\npassword:%s\nname:%s\n\n",a,p,c);       //写入文件
    fclose(fp);
}

//根据传入的账号，检查是否已经存在
Status check_signup(char*account)
{
    LNode* p;
    p=(LNode*)malloc(sizeof(LNode));
    p = list->next;
    while(p!=NULL)
    {
        if(strcmp(p->user->account,account)==0)
        {
            printf("The account exists!\n");
            return ERROR;
        }
        p = p->next;
    }
    return SUCCESS;
}


//检查输入的账号对应的密码是否正确
Status check(char*account,char* password)
{
    LNode* p;
    p=(LNode*)malloc(sizeof(LNode));
    p = list->next;
    while(p!=NULL)
    {
        if(strcmp(p->user->account,account)==0&&strcmp(p->user->password,password)==0)
        {
            return SUCCESS;
        }
        p = p->next;
    }
    printf("fail!\n");
    return ERROR;
}



char* login(void)
{
    system("cls");
    printf("\n\
***                 log in               ***\n\
***                                      ***\n\
account>");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));               //分配空间
    p=(char*)malloc(20*sizeof(char));
    scanf("%s",a);
    printf("password>");
    scanf("%s",p);
    printf("********************************************\n");
    if(check(a,p))
    {
        return a;
    }
    else
    {
        return NULL;
    }
}


//sign up
void signup(void)
{
    char *a,*p,*c,*n;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //分配空间
    c=(char*)malloc(20*sizeof(char));
    n=(char*)malloc(20*sizeof(char));
    system("cls");
    printf("\n\
********************************************\n\
***                 sign up              ***\n\
***                                      ***\n\
account>");
    scanf("%s",a);
    printf("your name>");
    scanf("%s",n);
    printf("password>");
    scanf("%s",p);
    printf("confirm password>");
    scanf("%s",c);
    printf("********************************************\n");
    if(strcmp(p,c)==0)
    {
        if(check_signup(a))
        {
            savetofile(a,p,n);
            USER* user;
            LNode* q;
            q = (LNode*)malloc(sizeof(LNode));
            user = (USER*)malloc(sizeof(USER));
            user->account=a;
            user->password=p;
            user->name=n;
            q->user = user;
            InsertList(list,q);
            home();
            printf("success!\n");
        }
    }
    else
    {
        home();
        printf("The passwords are not the same\n");
    }
}

//传入账户名称，在文件中删除对应的账户密码
Status deleteFile(char* account)
{
    FILE *fp;
    FILE *fp1;
    fp = fopen("..\\data\\account.txt","r");
    fp1 = fopen("data\\account1.txt","w");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //分配空间
    c=(char*)malloc(20*sizeof(char));
    while(fscanf(fp,"account:%s\npassword:%s\nname:%s\n\n",a,p,c)!=EOF)     //读取文件 除了要删除的账户，其他账户密码写入新文件
    {
        if(strcmp(a,account)!=0)                                    //不是要删除的账户
        {
            fprintf(fp1,"account:%s\npassword:%s\nname:%s\n\n",a,p,c);         //写入新文件
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("..\\data\\account.txt");
    rename("data\\account1.txt","..\\data\\account.txt");
    return SUCCESS;
}


//传入账户名称，寻找链表中结点并删除
Status DeleteList(LinkedList *L,char* account)
{
    LNode *p,*q;
    p = (*L)->next;
    q = *L;
    while(p!=NULL)
    {
        if(strcmp(p->user->account,account)==0)
        {
            q->next = p->next;
            free(p);
            return SUCCESS;
        }
        q = p;
        p = p->next;
    }
    return ERROR;
}

void change_password(void)
{
    char *a,*p,*c,*n;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //分配空间
    c=(char*)malloc(20*sizeof(char));
    n=(char*)malloc(20*sizeof(char));
    system("cls");
    printf("change password\n");
    printf("account>");
    scanf("%s",a);
    printf("your name>");
    scanf("%s",n);
    printf("new password>");
    scanf("%s",p);
    printf("confirm password>");
    scanf("%s",c);
    if(check_signup(a))
    {
        home();
        printf("The account does not exist!\n");
        return;
    }
    else if(strcmp(p,c)==0)
    {
        if(DeleteList(&list,a))
        {
            deleteFile(a);
            savetofile(a,p,n);
            USER* user;
            LNode* q;
            q = (LNode*)malloc(sizeof(LNode));
            user = (USER*)malloc(sizeof(USER));
            user->account=a;
            user->password=p;
            user->name=n;
            q->user = user;
            InsertList(list,q);
            home();
            printf("success!\n");
        }
    }
    else
    {
        home();
        printf("The passwords are not the same\n");
    }
}

//输入账户和姓名，打印出对应的密码，如果账户和姓名不匹配，打印出密码错误
void find_password(void)
{
    char *a,*n;
    a=(char*)malloc(20*sizeof(char));
    n=(char*)malloc(20*sizeof(char));                               //分配空间
    system("cls");
    printf("change password\n");
    printf("account>");
    scanf("%s",a);
    printf("your name>");
    scanf("%s",n);
    if (!check_signup(a))                                        //账户和姓名匹配                        
    {
        home();
        printf("The password is %s\n",printpassword(a,n));
    }
    else
    {
        home();
        printf("The account does not exist!\n");
        return;
    }   
}

//传入账户名称，返回对应的密码
char* printpassword(char* account,char* name)
{
    FILE *fp;
    fp = fopen("..\\data\\account.txt","r");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //分配空间
    c=(char*)malloc(20*sizeof(char));
    while(fscanf(fp,"account:%s\npassword:%s\nname:%s\n\n",a,p,c)!=EOF)
    {
        if(strcmp(a,account)==0&&strcmp(c,name)==0)
        {
            return p;
        }
    }
    return NULL;
}