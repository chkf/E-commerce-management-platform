#include "linkedList.h"
#include <string.h>
#include <windows.h>
#include "account.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*initialize an empty linked list with only the head node without value*/
Status InitList(LinkedList *L)              //L��ͷ�ڵ�ָ���ָ��
{
    *L = (LNode*)malloc(sizeof(LNode));         
    if(*L==NULL)return ERROR;               //ifû�еõ�malloc����ָ��
    (*L)->next=NULL;                        //��տ��ܴ��ڵ�ֵ
    return SUCCESS;
}

/*insert node q after node p*/
Status InsertList(LNode *p, LNode *q)
{
    if(q==NULL)                    //qָ��ָ��NULL
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

//��ʼ������g_list
Status InitGList(G_LinkedList *L)
{
    *L = (G_LNode*)malloc(sizeof(G_LNode));
    if(*L==NULL)return ERROR;
    (*L)->next=NULL;
    return SUCCESS;
}

//����ڵ�q��p����
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

//��ʼ������b_list
Status InitBList(B_LinkedList *L)
{
    *L = (B_LNode*)malloc(sizeof(B_LNode));
    if(*L==NULL)return ERROR;
    (*L)->next=NULL;
    return SUCCESS;
}


//����ڵ�q��p����
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