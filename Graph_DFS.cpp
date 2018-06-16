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
//����ͼ
typedef struct {
    AdjList vdata;
    int vexnum,arcnum;
}ALGraph;  //Ϊ������ȱ���������������
           //FALSEΪ0��TRUEΪ1
typedef enum{
    FALSE,TRUE
}Boolean;
Boolean visited[MAX_NUM]; //���ʱ�־������ȫ����

void DFS(ALGraph *G,int i) {      //��viΪ��������ڽӱ��ʾ��ͼG���������������
    ArcNode *p=NULL;
    printf("visit ���㣺%c\n",G->vdata[i].data);//���ʶ���vi
    visited[i]=TRUE; //���vi�ѷ���
    p=G->vdata[i].firstarc; //ȡvi�߱��ͷָ��,�Һ͵�vi���ӵĻ����
    while(p!=NULL)  {//��������vi���ڽӵ�vj������j=p->nextarc->data
        if (!visited[p->data])//��vi��δ������
            DFS(G,p->data);//����VjΪ����������������
        p=p->nextarc; //��vi����һ�ڽӵ�
    }
}//DFS

void DFSTraverse(ALGraph *G) { //������ȱ������ڽӱ��ʾ��ͼG�������ڽӾ����ʾGʱ���㷨��ȫ�����ͬ
    int i;
    for(i=0;i<G->vexnum;i++)
        visited[i]=FALSE; //��־������ʼ��
    for(i=0;i<G->vexnum;i++)
        if(!visited[i]) //viδ���ʹ�
            DFS(G,i); //��viΪԴ�㿪ʼDFS����
}//DFSTraverse
        //����ͼ���ڽӱ�
int Creategraph(ALGraph &G,int n){
    ArcLink p;
    int e,i;
    char v,w;
    for(i=0;i<n;i++){
        G.vdata[i].data='A'+i;
        G.vdata[i].firstarc=NULL;
    }
    printf("����ߵĸ���:\n");
    scanf("%d",&e);
    for(i=0;i<e;i++) {
        getchar();//����scanf�Ļس���
        printf("������ĳ��������������������A--%C��ʾ\n",'A'+n-1);
        scanf("%c%c",&v,&w);//fflush(stdin);
        printf("V=%c,W=%c,I=%d\n",v,w,i);
        p=(ArcLink )malloc(sizeof(ArcNode));
        p->data=(int)(w-'A');
        printf("%d\n",p->data);
        p->nextarc=G.vdata[(int)(v-'A')].firstarc;
        G.vdata[(int)(v-'A')].firstarc=p;
        p=(ArcLink)malloc(sizeof(ArcNode));
        p->data=(int)(v-'A');
        p->nextarc=G.vdata[(int)(w-'A')].firstarc;
        G.vdata[(int)(w-'A')].firstarc=p;
    }
    G.vexnum=n;
    G.arcnum=e;
    return OK;
}   //����ڽӱ�

int printGraph(ALGraph G){
    ArcLink p;
    int i;
    for(i=0;i<G.vexnum;i++){
        printf("%2d %c",i,G.vdata[i]);
        for(p=G.vdata[i].firstarc;p!=NULL;p=p->nextarc){
            printf("-->");
            printf("%d",p->data);
        } printf("\n");
    }
    return OK;
}
int main(){
    ALGraph G;
    int n;
    printf("��������Ҫ����������ͼ�Ķ������:\n");
    scanf("%d",&n);
    Creategraph(G,n);
    printf("������ȱ�����\n");
    DFSTraverse(&G);
    printf("��������������ͼ���ڽӱ�������ʾ:\n");
    printGraph(G);
    return OK;
}
