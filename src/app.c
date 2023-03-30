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
G_LNode *find_goods_node(char *name)
{
    G_LNode *p = g_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good->name,name) == 0)
        {
            //printf("name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
            return p;
        }
        p = p->next;
    }
    printf("no such goods\n");
    return NULL;
}

//������Ʒ�����������޸���Ʒ�ļ۸�
void change_goods_price(char *name, char *owner, int price)
{
    G_LNode *p = find_goods_node(name);
    if (p == NULL)
    {
        printf("no such goods\n");
        return;
    }
    if (strcmp(p->good->owner, owner) != 0)
    {
        printf("you are not the owner of this goods\n");
        return;
    }
    p->good->price += price;
    update_goods_info();
}



//������Ʒ�������������ʹ���Ŀ��仯����������Ʒ���
void change_goods_number(char *name, char *owner, int number)
{
    G_LNode *p = find_goods_node(name);
    if (p == NULL)
    {
        printf("no such goods\n");
        return;
    }
    if (strcmp(p->good->owner, owner) != 0)
    {
        printf("you are not the owner of this goods\n");
        return;
    }
    p->good->number += number;
    update_goods_info();
}

//��������������ӡ������Ʒ��Ϣ
void print_goods(char *owner)
{
    int flag = 0;
    G_LNode *p = g_list->next;
    if (p == NULL)
    {
        printf("none\n");
        return;
    }
    while (p != NULL)
    {
        if (strcmp(p->good->owner, owner) == 0)
        {
            flag = 1;
            printf("name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
        }
        p = p->next;
    }
    if (flag == 0)
    {
        printf("none\n");
    }
}

//�����˺ţ���������b_list���ҳ�����Ϊ���˺ŵ����ж�������ӡ����
void print_bill(char *account)
{
    B_LNode *p = b_list->next;
    if(p==NULL)
    {
        printf("none\n");
        return;
    }
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
    if(p==NULL)
    {
        printf("none\n");
        return;
    }
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
    G_LNode *p = find_goods_node(name);
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
    FILE *fp;
    fp = fopen("data\\bills.txt", "a+");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    printf("success!\n");
    fprintf(fp, "ordernumber:%d\nname:%s\nbuyer:%s\naddress:%s\nseller:%s\nnumber:%d\n\n", ordernumber,p->good->name, account,address,p->good->owner,number);
    change_goods_number(p->good->name,p->good->owner,-number);
    update_goods_info();
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



//ɾ��ָ����Ʒ
void delete_goods(char* account)
{
    char name[20];
    printf("input goods name>");
    scanf("%s",name);
    G_LNode *p = find_goods_node(name);
    if (p == NULL)
    {
        printf("no such goods\n");
        return;
    }
    if(strcmp(p->good->owner,account))
    {
        printf("you can only delete your goods\n");
        return;
    }
    DeleteGList(&g_list, p);
    update_goods_info();
    printf("delete success\n");
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


//���������˺ź���Ʒ��,�������˺���ͬʱ������Ʒ��Ϣ�����ļ�apply.txt
void apply_recommendation(char* account)
{
    char name[20];
    printf("input goods name>");
    scanf("%s", name);
    G_LNode *p = g_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good->name, name) == 0)
        {
            if(strcmp(p->good->owner,account))
            {
                printf("you can only apply your own goods\n" );
                return;
            }
            FILE *fp;
            fp = fopen("data\\apply.txt", "a");
            if (fp == NULL)
            {
                printf("open file error\n");
                return;
            }
            fprintf(fp, "name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
            fclose(fp);
            printf("apply success,wait for the manager to pass it\n");
            return;
        }
        p = p->next;
    }
    printf("no such goods\n");
}

//��apply.txt�е���Ʒ��Ϣ�����ӡ����һ�δ�ӡһ�������û�ѡ���Ƿ���
void recommended_goods(char* account)
{
    FILE *fp;
    int command;
    fp = fopen("data\\apply.txt", "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    char address[50];
    char name[20];
    int price;
    int number;
    char owner[20];
    while (fscanf(fp, "name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", name, &price, &number, owner) != EOF)
    {
        printf("***recommendation goods:***\n");
        printf("name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", name, price, number, owner);
        printf("press enter to continue\n");
        printf("press B to buy it\n");
        scanf("%c", &command);
        if (command == 'B'||command == 'b')
        {
            printf("buy it? 1:yes/0:no>");
            while(1)
            {
                my_scanf(&command,"command error>");
                if(command==1)
                {
                    if(!strcmp(owner,account))
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
        }
    }
    fclose(fp);
    
}


//goods information update
void goods_info_change(char* account)
{
    FILE *fp;
    int command;
    fp = fopen("data\\goodslist.txt", "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    printf("1.goods number update\n");
    printf("2.goods price update\n");
    my_scanf(&command,"command error>");
    if(command==1)
    {
        char name[20];
        int number;
        printf("input goods name>");
        scanf("%s", name);
        printf("input goods number(how many it change)>");
        my_scanf(&number,"number error>");
        change_goods_number(name, account,number);
        printf("number update success\n");
    }
    else if(command==2)
    {
        char name[20];
        int price;
        printf("input goods name>");
        scanf("%s", name);
        printf("input goods price(how much it change)>");
        my_scanf(&price,"price error>");
        change_goods_price(name, account,price);
        printf("price update success\n");
    }
    else
    {
        printf("command error\n");
    }
}
