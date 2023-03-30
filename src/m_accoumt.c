#include "m_account.h"
#include "linkedList.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

extern LinkedList m_list;

//��txt�ļ��ж�ȡ�˺����룬ת��Ϊ�ַ����󣬴�������
void m_readfile(void)
{
    USER* user;
    LNode* q;
    FILE *fp;
    fp = fopen("data\\m_account.txt","r");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //����ռ�
    c=(char*)malloc(20*sizeof(char));
    while(fscanf(fp,"account:%s\npassword:%s\nname:%s\n\n",a,p,c)!=EOF)
    {
        q = (LNode*)malloc(sizeof(LNode));
        user = (USER*)malloc(sizeof(USER));
        user->account=(char*)malloc(20*sizeof(char));
        user->password=(char*)malloc(20*sizeof(char));
        user->name=(char*)malloc(20*sizeof(char));
        strcpy(user->account,a);                        //����ȡ���˺����������
        strcpy(user->password,p);
        strcpy(user->name,c);
        q->user = user;
        q->next = NULL;
        InsertList(m_list,q);
    }
    fclose(fp);
}


//���ļ���д���˺�����
void m_savetofile(char* a,char* p,char* c)
{
    FILE *fp;
    fp = fopen("data\\m_account.txt","a");
    fprintf(fp,"account:%s\npassword:%s\n\n",a,p,c);       //д���ļ�
    fclose(fp);
}

//���ݴ�����˺ţ�����Ƿ��Ѿ�����
Status m_check_signup(char*account)
{
    LNode* p;
    p=(LNode*)malloc(sizeof(LNode));
    p = m_list->next;
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


//���������˺Ŷ�Ӧ�������Ƿ���ȷ
Status m_check(char*account,char* password)
{
    LNode* p;
    p=(LNode*)malloc(sizeof(LNode));
    p = m_list->next;
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



char* m_login(void)
{
    system("cls");
    printf("\n\
***                 log in               ***\n\
***                                      ***\n\
account>");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));               //����ռ�
    p=(char*)malloc(20*sizeof(char));
    scanf("%s",a);
    printf("password>");
    scanf("%s",p);
    printf("********************************************\n");
    if(m_check(a,p))
    {
        return a;
    }
    else
    {
        return NULL;
    }
}


//sign up
void m_signup(void)
{
    char *a,*p,*c,*n;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //����ռ�
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
        if(m_check_signup(a))
        {
            m_savetofile(a,p,n);
            USER* user;
            LNode* q;
            q = (LNode*)malloc(sizeof(LNode));
            user = (USER*)malloc(sizeof(USER));
            user->account=a;
            user->password=p;
            user->name=n;
            q->user = user;
            InsertList(m_list,q);
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

//�����˻����ƣ����ļ���ɾ����Ӧ���˻�����
Status m_deleteFile(char* account)
{
    FILE *fp;
    FILE *fp1;
    fp = fopen("data\\m_account.txt","r");
    fp1 = fopen("data\\m_account1.txt","w");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));      
    c=(char*)malloc(20*sizeof(char));                             //����ռ�
    while(fscanf(fp,"account:%s\npassword:%s\nname:%s\n\n",a,p,c)!=EOF)     //��ȡ�ļ� ����Ҫɾ�����˻��������˻�����д�����ļ�
    {
        if(strcmp(a,account)!=0)                                    //����Ҫɾ�����˻�
        {
            fprintf(fp1,"account:%s\npassword:%s\nname:%s\n\n",a,p,c);         //д�����ļ�
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("data\\m_account.txt");
    rename("data\\m_account1.txt","data\\m_account.txt");
    return SUCCESS;
}


//�����˻����ƣ�Ѱ�������н�㲢ɾ��
Status m_DeleteList(LinkedList *L,char* account)
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

void m_change_password(void)
{
    char *a,*p,*c,*n;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //����ռ�
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
    if(m_check_signup(a))
    {
        home();
        printf("The account does not exist!\n");
        return;
    }
    else if(strcmp(p,c)==0)
    {
        if(m_DeleteList(&m_list,a))
        {
            m_deleteFile(a);
            m_savetofile(a,p,n);
            USER* user;
            LNode* q;
            q = (LNode*)malloc(sizeof(LNode));
            user = (USER*)malloc(sizeof(USER));
            user->account=a;
            user->password=p;
            user->name=n;
            q->user = user;
            InsertList(m_list,q);
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

//�����˻�����������ӡ����Ӧ�����룬����˻���������ƥ�䣬��ӡ���������
void m_find_password(void)
{
    char *a,*n;
    a=(char*)malloc(20*sizeof(char));
    n=(char*)malloc(20*sizeof(char));                               //����ռ�
    system("cls");
    printf("change password\n");
    printf("account>");
    scanf("%s",a);
    printf("your name>");
    scanf("%s",n);
    if (!m_check_signup(a))                                        //�˻�������ƥ��                        
    {
        home();
        printf("The password is %s\n",m_printpassword(a,n));
    }
    else
    {
        home();
        printf("The account does not exist!\n");
        return;
    }   
}

//�����˻����ƣ����ض�Ӧ������
char* m_printpassword(char* account,char* name)
{
    FILE *fp;
    fp = fopen("data\\m_account.txt","r");
    char *a,*p,*c;
    a=(char*)malloc(20*sizeof(char));
    p=(char*)malloc(20*sizeof(char));                               //����ռ�
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