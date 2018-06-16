#include<stdio.h>
#include<malloc.h>
#define MAX_NUM 20
#define OK 1
#define ERROR -1

typedef int ElemType;
typedef char VertexType;
typedef struct ArcNode { //���廡���
    ElemType data;
    ArcNode *nextarc;
}ArcNode,*ArcLink;

 typedef struct VNode { //���嶥����
    VertexType data;
    ArcLink firstarc;
}VNode,AdjList[MAX_NUM];

typedef struct {
    AdjList vdata;
    int vexnum,arcnum;
}ALGraph; //����ͼ���ڽӱ�

int Creategraph(ALGraph &G,int n) {
    ArcLink p;
    int e,i;
    char v,w;
    for(i=0;i<n;i++){
        G.vdata[i].data='A'+i;
        G.vdata[i].firstarc=NULL;
    }
    printf("����ߵĸ���:\n");
    scanf("%d",&e);
    for(i=0;i<e;i++){
        getchar();//����scanf�Ļس���
        printf("������ĳ��������������������A--%C��ʾ\n",'A'+n-1);
        scanf("%c%c",&v,&w);//fflush(stdin);
        printf("V=%c,W=%c,I=%d\n",v,w,i);
        p=(ArcLink )malloc(sizeof(ArcNode));
        p->data=(int)(w-'A'+1);
        printf("%d\n",p->data);
        p->nextarc=G.vdata[(int)(v-'A')].firstarc;
        G.vdata[(int)(v-'A')].firstarc=p;
        p=(ArcLink)malloc(sizeof(ArcNode));
        p->data=(int)(v-'A'+1);
        p->nextarc=G.vdata[(int)(w-'A')].firstarc;
        G.vdata[(int)(w-'A')].firstarc=p;
    }
    G.vexnum=n;
    G.arcnum=e;
    return OK;
} //����ڽӱ�
int printGraph(ALGraph G){
    ArcLink p;
    int i;
    for(i=0;i<G.vexnum;i++){
        printf("%2d %c",i,G.vdata[i]);
        for(p=G.vdata[i].firstarc;p!=NULL;p=p->nextarc){
            printf("-->");
            printf("%d",p->data);
        }
        printf("\n");
    }
    return OK;
}
int main() {
    ALGraph G;
    int n;
    printf("��������Ҫ����������ͼ�Ķ������:\n");
    scanf("%d",&n);
    Creategraph(G,n);
    printf("��������������ͼ���ڽӱ�������ʾ:\n");
    printGraph(G);
    return OK;
}
