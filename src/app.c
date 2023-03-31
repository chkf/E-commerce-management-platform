#include "linkedList.h"
#include "account.h"
#include "m_account.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "app.h"
#include "main.h"
#include <conio.h>


extern G_LinkedList g_list,r_list;
extern B_LinkedList b_list;


//将bills.txt文件中账单信息读入链表
void read_bills(void)
{
    FILE *fp;
    BILL *b;
    B_LNode *p;
    fp = fopen("..\\data\\bills.txt", "r");
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

//向goodslist.txt中加入新商品信息，包含商品名，价格，库存，卖家
void add_goods(char *name, int price, int number, char *owner)
{
    FILE *fp;
    fp = fopen("..\\data\\goodslist.txt", "a+");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    fprintf(fp, "name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", name, price, number, owner);
    fclose(fp);
}

//将recommendation.txt文件中推荐信息读入链表
void read_recommendation(void)
{
    FILE *fp;
    fp = fopen("..\\data\\recommendlist.txt", "r");
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
        InsertGList(r_list, p);
    }
    fclose(fp);
}

//将goodslist.txt文件中商品信息读入链表
void read_goods(void)
{
    FILE *fp;
    fp = fopen("..\\data\\goodslist.txt", "r");
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

//输入信息，将商品信息加入链表和文件中
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
    add_goods(name, price, number, owner);        //将商品信息加入文件
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

//根据商品名查找商品
G_LNode *find_goods_node(G_LinkedList*L,char *name)
{
    G_LNode *p = (*L)->next;
    while (p != NULL)
    {
        if (strcmp(p->good->name,name) == 0)
        {
            return p;
        }
        p = p->next;
    }
    printf("no such goods\n");
    return NULL;
}

//根据商品名和卖家名修改商品的价格
void change_goods_price(G_LinkedList *L,char *name, char *owner, int price)
{
    G_LNode *p = find_goods_node(L,name);
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



//根据商品名和卖家名，和传入的库存变化量，更改商品库存
void change_goods_number(G_LinkedList *L,char *name, char *owner, int number)
{
    G_LNode *p = find_goods_node(L,name);
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

//根据卖家名，打印在售商品信息
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

//输入账号，根据链表b_list，找出卖家为该账号的所有订单，打印出来
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

//输入账号，根据链表b_list，找出买家为该账号的所有订单，打印出来
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

//从1开始计数，计数存储在temp.txt文件中
int count(void)
{
    FILE *fp;
    fp = fopen("..\\data\\temp.txt", "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return 0;
    }
    int count;
    fscanf(fp, "%d", &count);
    fclose(fp);
    count++;
    fp = fopen("..\\data\\temp.txt", "w");
    if (fp == NULL)
    {
        printf("open file error\n");
        return 0;
    }
    fprintf(fp, "%d", count);
    fclose(fp);
    return count;
}

//把购买订单信息录入链表b_list中
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



//用户购买商品，生成订单，存入bills.txt文件中
void buy_goods(char *name, char *address,char*account)
{
    int number,ordernumber;
    G_LNode *p = find_goods_node(&g_list,name);
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
    fp = fopen("..\\data\\bills.txt", "a+");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    printf("success!\n");
    fprintf(fp, "ordernumber:%d\nname:%s\nbuyer:%s\naddress:%s\nseller:%s\nnumber:%d\n\n", ordernumber,p->good->name, account,address,p->good->owner,number);
    change_goods_number(&g_list,p->good->name,p->good->owner,-number);
    update_goods_info();
    add_bill(p->good->name,address,account,p->good->owner,number);
    fclose(fp);
    G_LNode *q = find_goods_node(&r_list,name);
    if (q == NULL)
    {
        return;
    }
    else
    {
        change_goods_number(&r_list,q->good->name,q->good->owner,-number);
        update_recommend_info();
    }
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



//删除指定商品
void delete_goods(char* account)
{
    char name[20];
    printf("input goods name>");
    scanf("%s",name);
    G_LNode *p = find_goods_node(&g_list,name);
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

//根据r_list中的商品信息更新recommendlist.txt文件中的商品信息
void update_recommend_info(void)
{
    FILE *fp;
    fp = fopen("..\\data\\recommendlist.txt", "w");
    fclose(fp);
    remove("..\\data\\recommendlist.txt");
    fp = fopen("..\\data\\recommendlist.txt", "w");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    G_LNode *p = r_list->next;
    while (p != NULL)
    {
        fprintf(fp, "name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", p->good->name, p->good->price, p->good->number, p->good->owner);
        p = p->next;
    }
    fclose(fp);
}


//根据链表信息更新文件信息
void update_goods_info(void)
{
    FILE *fp;
    fp = fopen("..\\data\\goodslist.txt", "w");
    fclose(fp);
    remove("..\\data\\goodslist.txt");
    fp = fopen("..\\data\\goodslist.txt", "w");
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

//输入商品信息，存入链表，更新文件信息
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


//函数传入账号和商品名,卖家与账号相同时，把商品信息存入文件apply.txt
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
            fp = fopen("..\\data\\apply.txt", "a");
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

//把apply.txt中的商品信息逐个打印，按一次打印一个，供用户选择是否购买
void recommended_goods(char* account)
{
    FILE *fp;
    int command;
    char key;
    fp = fopen("..\\data\\recommendlist.txt", "r");
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
        system("cls");
        printf("***recommended goods:***\n");
        printf("name:%s\nprice:%d\nnumber:%d\nowner:%s\n\n", name, price, number, owner);
        printf("press enter to continue\n");
        printf("press B to buy it\n");
        scanf("%c", &key);
        if (key == 'B'||key == 'b')
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
                        printf("press any key to continue\n");
                        getch();
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
    printf("no more goods\n");
    fclose(fp);
    
}


//goods information update
void goods_info_change(char* account)
{
    FILE *fp;
    int command;
    fp = fopen("..\\data\\goodslist.txt", "r");
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
        change_goods_number(&g_list,name, account,number);
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
        change_goods_price(&g_list,name, account,price);
        printf("price update success\n");
    }
    else
    {
        printf("command error\n");
    }
}
