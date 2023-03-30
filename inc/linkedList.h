#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef enum Status 
{
    ERROR, 
	SUCCESS
} Status;

typedef char* ElemType;

typedef struct goods
{
	ElemType name;
	int price;
	int number;
	ElemType owner;
}goods;

typedef struct USER
{
	ElemType account;
	ElemType password;
	ElemType name;
}USER;

typedef struct BILL
{
	int ordernumber;
	ElemType name;
	ElemType buyer;
	ElemType address;
	ElemType seller;
	int number;
}BILL;

typedef struct B_LNode
{
	struct BILL *bill;
	struct B_LNode *next;
}B_LNode, *B_LinkedList;

typedef  struct LNode
{
	struct USER *user;
	struct LNode *next;
}LNode, *LinkedList;

typedef struct G_LNode
{
	struct goods *good;
	struct G_LNode *next;
}G_LNode, *G_LinkedList;

//Á´Õ»
Status InitList(LinkedList *L);
Status InsertList(LNode *p, LNode *q);
Status InitGList(G_LinkedList *L);
Status InsertGList(G_LNode *p, G_LNode *q);
Status InitBList(B_LinkedList *L);
Status InsertBList(B_LNode *p, B_LNode *q);


#endif
