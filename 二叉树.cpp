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
} SqStack;//ջ����
void InitStack(SqStack *S)//����ջ
{
    S->base=(BiTNode*)malloc(STACK_INIT_SIZE*sizeof(BiTNode));
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
}
int StackEmpty(SqStack *S)//�ж�ջ�Ƿ�ǿ�
{
    if(S->top == S->base ) return OK;
    else return ERROR;
}
void Push(SqStack *S,BiTNode e)//��ջ
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
BiTNode Pop(SqStack *S)//��ջ
{
    S->top --;
    return *S->top;
}
typedef BiTree QElemType; //��ջԪ��Ϊ��������ָ������
typedef struct
{
   QElemType *base;
   int front; //ͷָ��,�����в���,ָ�����ͷԪ��
   int rear;   //βָ��,�����в���,ָ�����βԪ�ص���һ��λ��
}SqQueue;
int InitQueue(SqQueue *Q)//��������
{
	(*Q).base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
    if(!(*Q).base) exit(OVERFLOW);
    (*Q).front=(*Q).rear=0;
    return OK;
}
int QueueEmpty(SqQueue Q)//�ж϶����Ƿ�Ϊ��
{
	if(Q.front==Q.rear) return OK;
    else return ERROR;
}
int EnQueue(SqQueue *Q,QElemType e) //����Ԫ��eΪQ���µĶ�βԪ��
{
	if(((*Q).rear+1)%MAXQSIZE==(*Q).front) return ERROR;
    (*Q).base[(*Q).rear]=e;
    (*Q).rear=((*Q).rear+1)%MAXQSIZE;
    return OK;
}
int DeQueue(SqQueue *Q,QElemType *e)//ɾ��Q�Ķ�ͷԪ��,��e������ֵ
{
	if((*Q).front==(*Q).rear) return ERROR;
    *e=(*Q).base[(*Q).front];
    (*Q).front=((*Q).front+1)%MAXQSIZE;
    return OK;
}
int CreateBiTree(BiTree &T)//������������������������ֵ��#��ʾ��������
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
void PreOrderTraverse(BiTree T)//��������������ĵݹ��㷨
{
	if(T)
	{
		printf("%c",T->data);
        PreOrderTraverse(T->lChild);
        PreOrderTraverse(T->rChild);
    }
}
void InOrderTraverse(BiTree T)//��������������ĵݹ��㷨
{
	if(T)
	{
		InOrderTraverse(T->lChild);
        printf("%c",T->data);
        InOrderTraverse(T->rChild);
    }
}
void PostOrderTraverse(BiTree T)//��������������ĵݹ��㷨
{
	if(T)
	{
		PostOrderTraverse(T->lChild);
        PostOrderTraverse(T->rChild);
        printf("%c",T->data);
    }
}
void PreOrderTraverse1(BiTree T)//����ǵݹ�����������㷨(����ջ)
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
void LevelOrderTraverse(BiTree T)// ����ǵݹ�����������㷨(���ö���)
{
	SqQueue Q;
    BiTree P;
    InitQueue(&Q);// ��ʼ������
    if(T) EnQueue(&Q,T);
    while(Q.front!=Q.rear)
    {
        T=Q.base[Q.front];//ѭ�����У���T���ض���ͷָ��
		DeQueue(&Q,&P);
        printf("%c",T->data);
        if (P->lChild) EnQueue(&Q, P->lChild); // ���������ӣ����ӽ�����
        if (P->rChild) EnQueue(&Q, P->rChild); // �������Һ��ӣ��Һ��ӽ�����
    }
}
int main()//�������ֱ�ʵ�ֽ���������ȡ��С��������������
{
	BiTree T;
	printf("����������������н���ֵ��#��ʾ�ս��:\n");
	CreateBiTree(T);
    printf("����ݹ����������:");
    PreOrderTraverse(T);
    printf("\n����ݹ����������:");
    InOrderTraverse(T);
    printf("\n����ݹ����������:");
    PostOrderTraverse(T);
	printf("\n����ǵݹ����������:");
	PreOrderTraverse1(T);
	printf("\n�������������:");
	LevelOrderTraverse(T);
	printf("\n");
}
