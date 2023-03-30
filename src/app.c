#include "linkedList.h"
#include "account.h"
#include "m_account.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "app.h"
#include "main.h"

extern G_LinkedList g_list;
extern B_LinkedList b_list;


//��bills.txt�ļ����˵���Ϣ��������
void read_bills(void)
{
    FILE *fp;
    BILL *b;
    B_LNode *p;
    fp = fopen("data\\bills.txt", "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    char name[20];
    int ordernumber;
    int number;
    char address[50];
    char seller[20];
    char buyer[20];
    while (fscanf(fp, "ordernumber:%d\nname:%s\nbuyer:%s\naddress:%s\nseller:%s\nnumber:%d\n\n", &ordernumber, name, buyer,address, seller, &number) != EOF)
    {
        b = (BILL *)malloc(sizeof(BILL));
        b->address = (char*)malloc(sizeof(char) * 50);
        b->name = (char *)malloc(sizeof(char) * 20);
        b->seller = (char *)malloc(sizeof(char) * 20);
        b->buyer = (char *)malloc(sizeof(char) * 20);
        b->ordernumber = ordernumber;
        strcpy(b->name, name);
        strcpy(b->address, address);
        b->number = number;
        strcpy(b->seller, seller);
        strcpy(b->buyer, buyer);
        p = (B_LNode *)malloc(sizeof(B_LNode));
        p->bill = b;
        p->next = NULL;
        InsertBList(b_list, p);
    }
    fclose(fp);
}

//��goodslist.txt�м�������Ʒ��Ϣ��������Ʒ�����۸񣬿�棬����
void add_goods(char *name, int price, int number, char *owner)
{
    FILE *fp;
    fp = fopen("data\\goodslist.txt", "a+");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    fprintf(fp, "name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", name, price, number, owner);
    fclose(fp);
}

//��goodslist.txt�ļ�����Ʒ��Ϣ��������
void read_goods(void)
{
    FILE *fp;
    fp = fopen("data\\goodslist.txt", "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    char name[20];
    int price;
    int number;
    char owner[20];
    while (fscanf(fp, "name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", name, &price, &number, owner) != EOF)
    {
        goods *good = (goods *)malloc(sizeof(goods));
        good->name = (char *)malloc(sizeof(char) * 20);
        good->owner = (char *)malloc(sizeof(char) * 20);
        strcpy(good->name, name);
        good->price = price;
        good->number = number;
        strcpy(good->owner, owner);
        G_LNode *p = (G_LNode *)malloc(sizeof(G_LNode));
        p->good = good;
        p->next = NULL;
        InsertGList(g_list, p);
    }
    fclose(fp);
}


//������Ϣ������Ʒ��Ϣ����������ļ���
void add_goods_info(void)
{
    char name[20];
    int price;
    int number;
    char owner[20];
    printf("product name>");
    scanf("%s", name);
    printf("price>");
    scanf("%d", &price);
    printf("number>");
    scanf("%d", &number);
    printf("owner>");
    scanf("%s", owner);
    add_goods(name, price, number, owner);        //����Ʒ��Ϣ�����ļ�
    goods *good = (goods *)malloc(sizeof(goods));
    good->name = (char *)malloc(sizeof(char) * 20);
    good->owner = (char *)malloc(sizeof(char) * 20);
    strcpy(good->name, name);
    good->price = price;
    good->number = number;
    strcpy(good->owner, owner);
    G_LNode *p = (G_LNode *)malloc(sizeof(G_LNode));
    p->good = good;
    p->next = NULL;
    InsertGList(g_list, p);
}

//������Ʒ��������Ʒ
G_LNode *find_goods(char *name)
{
    G_LNode *p = g_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good->name,name) == 0)
        {
            printf("name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
            return p;
        }
        p = p->next;
    }
    printf("no such goods\n");
    return NULL;
}

//������Ʒ���޸���Ʒ�۸�
void modify_goods(char *name)
{
    G_LNode *p = find_goods(name);
    if (p == NULL)
    {
        return;
    }
    printf("new price>");
    scanf("%d", &p->good->price);
}

//�����˺ţ���������b_list���ҳ�����Ϊ���˺ŵ����ж�������ӡ����
void print_bill(char *account)
{
    B_LNode *p = b_list->next;
    while (p != NULL)
    {
        if (strcmp(p->bill->seller, account) == 0)
        {
            printf("ordernumber:%d\nname:%s\nbuyer:%s\naddress:%s\nseller:%s\nnumber:%d\n\n", p->bill->ordernumber, p->bill->name, p->bill->buyer, p->bill->address, p->bill->seller, p->bill->number);
        }
        p = p->next;
    }
}

//�����˺ţ���������b_list���ҳ����Ϊ���˺ŵ����ж�������ӡ����
void print_bill_buyer(char *account)
{
    B_LNode *p = b_list->next;
    while (p != NULL)
    {
        if (strcmp(p->bill->buyer, account) == 0)
        {
            printf("ordernumber:%d\nname:%s\nbuyer:%s\naddress:%s\nseller:%s\nnumber:%d\n\n", p->bill->ordernumber, p->bill->name, p->bill->buyer, p->bill->address, p->bill->seller, p->bill->number);
        }
        p = p->next;
    }
}

//��1��ʼ�����������洢��temp.txt�ļ���
int count(void)
{
    FILE *fp;
    fp = fopen("data\\temp.txt", "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return 0;
    }
    int count;
    fscanf(fp, "%d", &count);
    fclose(fp);
    count++;
    fp = fopen("data\\temp.txt", "w");
    if (fp == NULL)
    {
        printf("open file error\n");
        return 0;
    }
    fprintf(fp, "%d", count);
    fclose(fp);
    return count;
}

//���ݴ�����Ʒ���������ļ�

//�ѹ��򶩵���Ϣ¼������b_list��
void add_bill(char *name, char *address, char *buyer, char *seller, int number)
{
    BILL *b = (BILL *)malloc(sizeof(BILL));
    b->name = (char *)malloc(sizeof(char) * 20);
    b->address = (char *)malloc(sizeof(char) * 20);
    b->buyer = (char *)malloc(sizeof(char) * 20);
    b->seller = (char *)malloc(sizeof(char) * 20);
    strcpy(b->name, name);
    strcpy(b->address, address);
    strcpy(b->buyer, buyer);
    strcpy(b->seller, seller);
    b->number = number;
    b->ordernumber = count()-1;
    B_LNode *p = (B_LNode *)malloc(sizeof(B_LNode));
    p->bill = b;
    p->next = NULL;
    InsertBList(b_list, p);
}

//�û�������Ʒ�����ɶ���������bills.txt�ļ���
void buy_goods(char *name, char *address,char*account)
{
    int number,ordernumber;
    G_LNode *p = find_goods(name);
    if (p == NULL)
    {
        printf("no enough goods\n");
        return;
    }
    printf("buy number>");
    while(1)
    {
        my_scanf(&number,"number error>");
        if (number > p->good->number)
        {
            printf("no enough goods\n");
        }
        else
        {
            break;
        }
    }
    ordernumber = count();
    if(count==0)
    {
        printf("count error\n");
        return;
    }
    p->good->number-=number;
    FILE *fp;
    fp = fopen("data\\bills.txt", "a+");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    printf("success!\n");
    fprintf(fp, "ordernumber:%d\nname:%s\nbuyer:%s\naddress:%s\nseller:%s\nnumber:%d\n\n", ordernumber,p->good->name, account,address,p->good->owner,number);
    add_bill(p->good->name,address,account,p->good->owner,number);
    fclose(fp);
}

Status search_goods(char* account)
{
    int command;
    char name[20];
    char address[50];
    printf("input goods name>");
    scanf("%s",name);
    G_LNode *p = g_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good->name, name) == 0)
        {
            printf("name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
            printf("buy it? 1:yes/0:no>");
            while(1)
            {
                my_scanf(&command,"command error>");
                if(command==1)
                {
                    if(!strcmp(p->good->owner,account))
                    {
                        printf("can't buy your own goods\n" );
                        break;
                    }
                    printf("input address>");
                    scanf("%s",address);
                    buy_goods(name,address,account);
                    break;
                }
                else if(command==0)
                {
                    break;
                }
                else
                {
                    printf("command error>");
                }
            }
            return SUCCESS;
        }
        p = p->next;
    }
    printf("no such goods\n");
    return ERROR;
}

//�����������鿴����
void check_order(char *owner)
{
    FILE *fp;
    fp = fopen("data\\bills.txt", "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    char address[20];
    char name[20];
    int price;
    int number;
    char ownered[20];
    while (fscanf(fp, "address:%s\nname:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", address, name, &price, &number,ownered) != EOF)
    {
        if(strcmp(owner,ownered))printf("address:%s\nname:%s\nprice:%d\nnumber:%d\n\n", address, name, price, number);
    }
    fclose(fp);
}

//�����������鿴��Ʒ
void check_goods(char *name)
{
    G_LNode *p = g_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good->owner, name) == 0)
        {
            printf("name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
        }
        p = p->next;
    }
}

//������Ʒ���鿴��Ʒ���
G_LNode *find_goods_node(char *name)
{
    G_LNode *p = g_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good->name, name) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//ɾ������Ϊ0����Ʒ
void delete_zero_goods(void)
{
    G_LNode *p = g_list->next;
    G_LNode *q = g_list;
    while (p != NULL)
    {
        if (p->good->number == 0)
        {
            q->next = p->next;
            free(p);
            p = q->next;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }
}

//����������Ϣ�����ļ���Ϣ
void update_goods_info(void)
{
    FILE *fp;
    fp = fopen("data\\goodslist.txt", "w");
    fclose(fp);
    remove("data\\goodslist.txt");
    fp = fopen("data\\goodslist.txt", "w");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    G_LNode *p = g_list->next;
    while (p != NULL)
    {
        fprintf(fp, "name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
        p = p->next;
    }
    fclose(fp);
}

//������Ʒ��Ϣ���������������ļ���Ϣ
void submit_goods(char* account)
{
    char name[20];
    int price;
    int number;
    char owner[20];
    printf("input goods name>");
    scanf("%s", name);
    printf("input goods price>");
    my_scanf(&price,"price error>");
    printf("input goods number>");
    my_scanf(&number,"number error>");
    strcpy(owner, account);
    G_LNode *p = (G_LNode *)malloc(sizeof(G_LNode));
    p->good = (goods *)malloc(sizeof(goods));
    p->good->name = (char *)malloc(sizeof(char) * 20);
    p->good->owner = (char *)malloc(sizeof(char) * 20);
    strcpy(p->good->name,name);
    p->good->price = price;
    p->good->number = number;
    strcpy(p->good->owner,owner);
    InsertGList(g_list, p);
    update_goods_info();
}
