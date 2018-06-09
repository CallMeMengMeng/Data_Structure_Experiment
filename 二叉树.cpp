#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT   10
#define MAXQSIZE 10
typedef struct BiTNode
{
	char data;
    struct BiTNode *lChild,*rChild;
}BiTNode,*BiTree;
typedef struct SqStack
{
    BiTNode *base;
    BiTNode *top;
    int stacksize;
} SqStack;//栈类型
void InitStack(SqStack *S)//创建栈
{
    S->base=(BiTNode*)malloc(STACK_INIT_SIZE*sizeof(BiTNode));
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
}
int StackEmpty(SqStack *S)//判断栈是否非空
{
    if(S->top == S->base ) return OK;
    else return ERROR;
}
void Push(SqStack *S,BiTNode e)//进栈
{
    if(S->top-S->base>=S->stacksize)
    {
        S->base=(BiTNode*)realloc(S->base,
            (S->stacksize+STACKINCREMENT)*sizeof(BiTNode));
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *(S->top)=e;
    S->top++;
}
BiTNode Pop(SqStack *S)//出栈
{
    S->top --;
    return *S->top;
}
typedef BiTree QElemType; //设栈元素为二叉树的指针类型
typedef struct
{
   QElemType *base;
   int front; //头指针,若队列不空,指向队列头元素
   int rear;   //尾指针,若队列不空,指向队列尾元素的下一个位置
}SqQueue;
int InitQueue(SqQueue *Q)//创建队列
{
	(*Q).base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
    if(!(*Q).base) exit(OVERFLOW);
    (*Q).front=(*Q).rear=0;
    return OK;
}
int QueueEmpty(SqQueue Q)//判断队列是否为空
{
	if(Q.front==Q.rear) return OK;
    else return ERROR;
}
int EnQueue(SqQueue *Q,QElemType e) //插入元素e为Q的新的队尾元素
{
	if(((*Q).rear+1)%MAXQSIZE==(*Q).front) return ERROR;
    (*Q).base[(*Q).rear]=e;
    (*Q).rear=((*Q).rear+1)%MAXQSIZE;
    return OK;
}
int DeQueue(SqQueue *Q,QElemType *e)//删除Q的队头元素,用e返回其值
{
	if((*Q).front==(*Q).rear) return ERROR;
    *e=(*Q).base[(*Q).front];
    (*Q).front=((*Q).front+1)%MAXQSIZE;
    return OK;
}
int CreateBiTree(BiTree &T)//按先序次序输入二叉中树结点的值，#表示空树构造
{
	char ch;
	scanf("%c",&ch);
	if(ch=='#')T=NULL;
    else
	{
	    if(!(T=(BiTree)malloc(sizeof(BiTNode))))exit(OVERFLOW);
        T->data=ch;
        CreateBiTree(T->lChild);
        CreateBiTree(T->rChild);
    }
    return OK;
}
void PreOrderTraverse(BiTree T)//先序遍历二叉树的递归算法
{
	if(T)
	{
		printf("%c",T->data);
        PreOrderTraverse(T->lChild);
        PreOrderTraverse(T->rChild);
    }
}
void InOrderTraverse(BiTree T)//中序遍历二叉树的递归算法
{
	if(T)
	{
		InOrderTraverse(T->lChild);
        printf("%c",T->data);
        InOrderTraverse(T->rChild);
    }
}
void PostOrderTraverse(BiTree T)//后序遍历二叉树的递归算法
{
	if(T)
	{
		PostOrderTraverse(T->lChild);
        PostOrderTraverse(T->rChild);
        printf("%c",T->data);
    }
}
void PreOrderTraverse1(BiTree T)//先序非递归遍历二叉树算法(利用栈)
{
	SqStack R;
    BiTree p=T;
    InitStack(&R);
     if(p) Push(&R,*p);
    while(!StackEmpty(&R))
    {
		p=(BiTNode *)malloc(sizeof(BiTNode));
        *p=Pop(&R);
        printf("%c",p->data);
        if(p->rChild)
        Push(&R,*p->rChild);
        if(p->lChild)
        Push(&R,*p->lChild);
    }
}
void LevelOrderTraverse(BiTree T)// 层序非递归遍历二叉树算法(利用队列)
{
	SqQueue Q;
    BiTree P;
    InitQueue(&Q);// 初始化队列
    if(T) EnQueue(&Q,T);
    while(Q.front!=Q.rear)
    {   T = Q.base[Q.front];
		DeQueue(&Q,&P);
        printf("%c",T->data);
        if (P->lChild) EnQueue(&Q, P->lChild); // 若存在左孩子，左孩子进队列
        if (P->rChild) EnQueue(&Q, P->rChild); // 若存在右孩子，右孩子进队列
    }
}
int main()//主函数分别实现建立并输出先、中、后序遍历二叉树
{
	BiTree T;
	printf("按先序输入二叉树中结点的值，#表示空结点:\n");   //输入124##5##36##7##
	CreateBiTree(T);
    printf("先序递归遍历二叉树:");
    PreOrderTraverse(T);
    printf("\n中序递归遍历二叉树:");
    InOrderTraverse(T);
    printf("\n后序递归遍历二叉树:");
    PostOrderTraverse(T);
	printf("\n先序非递归遍历二叉树:");
	PreOrderTraverse1(T);
	printf("\n层序遍历二叉树:");
	LevelOrderTraverse(T);
	printf("\n");
/****************************************************************************************************************************************************************
在程序设计中，递归算法可以有效简化某些特定问题的编程，它易编写、结构清晰、可读性强。但是它只能简化程序的编码，不能降低程序的时间与空间复杂度。
相反，由于执行过程依赖函数或过程的重复调用，会带来附加的时间的消耗。
非递归算法较复杂、可读性较差，但多数情况下具有较高的效率。
****************************************************************************************************************************************************************/
}
