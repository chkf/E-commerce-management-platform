#include "linkedList.h"
#include <string.h>
#include <windows.h>
#include "account.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*initialize an empty linked list with only the head node without value*/
Status InitList(LinkedList *L)              //L是头节点指针的指针
{
    *L = (LNode*)malloc(sizeof(LNode));         
    if(*L==NULL)return ERROR;               //if没有得到malloc给的指针
    (*L)->next=NULL;                        //清空可能存在的值
    return SUCCESS;
}

/*insert node q after node p*/
Status InsertList(LNode *p, LNode *q)
{
    if(q==NULL)                    //q指针指向NULL
    {
        return ERROR;
    }
    if(p->next!=NULL)
    {
        q->next=p->next;
        p->next=q;
    }
    else
    {
        p->next=q;
        q->next=NULL;
    }
    return SUCCESS;
}

//初始化链表g_list
Status InitGList(G_LinkedList *L)
{
    *L = (G_LNode*)malloc(sizeof(G_LNode));
    if(*L==NULL)return ERROR;
    (*L)->next=NULL;
    return SUCCESS;
}

//插入节点q到p后面
Status InsertGList(G_LNode *p, G_LNode *q)
{
    if(q==NULL)
    {
        return ERROR;
    }
    if(p->next!=NULL)
    {
        q->next=p->next;
        p->next=q;
    }
    else
    {
        p->next=q;
        q->next=NULL;
    }
    return SUCCESS;
}

//初始化链表b_list
Status InitBList(B_LinkedList *L)
{
    *L = (B_LNode*)malloc(sizeof(B_LNode));
    if(*L==NULL)return ERROR;
    (*L)->next=NULL;
    return SUCCESS;
}


//插入节点q到p后面
Status InsertBList(B_LNode *p, B_LNode *q)
{
    if(q==NULL)
    {
        return ERROR;
    }
    if(p->next!=NULL)
    {
        q->next=p->next;
        p->next=q;
    }
    else
    {
        p->next=q;
        q->next=NULL;
    }
    return SUCCESS;
}