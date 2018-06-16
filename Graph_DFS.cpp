#include<stdio.h>
#include<malloc.h>
#define MAX_NUM 20
#define OK 1
#define ERROR -1
typedef int ElemType;
typedef char VertexType;

typedef struct ArcNode { //定义弧结点
    ElemType data;
    ArcNode *nextarc;
}ArcNode,*ArcLink;

typedef struct VNode { //定义顶点结点
    VertexType data;
    ArcLink firstarc;
}VNode,AdjList[MAX_NUM];
//定义图
typedef struct {
    AdjList vdata;
    int vexnum,arcnum;
}ALGraph;  //为深度优先遍历进行类型设置
           //FALSE为0，TRUE为1
typedef enum{
    FALSE,TRUE
}Boolean;
Boolean visited[MAX_NUM]; //访问标志向量是全局量

void DFS(ALGraph *G,int i) {      //以vi为出发点对邻接表表示的图G进行深度优先搜索
    ArcNode *p=NULL;
    printf("visit 顶点：%c\n",G->vdata[i].data);//访问顶点vi
    visited[i]=TRUE; //标记vi已访问
    p=G->vdata[i].firstarc; //取vi边表的头指针,找和点vi连接的弧结点
    while(p!=NULL)  {//依次搜索vi的邻接点vj，这里j=p->nextarc->data
        if (!visited[p->data])//若vi尚未被访问
            DFS(G,p->data);//则以Vj为出发点向纵深搜索
        p=p->nextarc; //找vi的下一邻接点
    }
}//DFS

void DFSTraverse(ALGraph *G) { //深度优先遍历以邻接表表示的图G，而以邻接矩阵表示G时，算法完全与此相同
    int i;
    for(i=0;i<G->vexnum;i++)
        visited[i]=FALSE; //标志向量初始化
    for(i=0;i<G->vexnum;i++)
        if(!visited[i]) //vi未访问过
            DFS(G,i); //以vi为源点开始DFS搜索
}//DFSTraverse
        //构建图的邻接表
int Creategraph(ALGraph &G,int n){
    ArcLink p;
    int e,i;
    char v,w;
    for(i=0;i<n;i++){
        G.vdata[i].data='A'+i;
        G.vdata[i].firstarc=NULL;
    }
    printf("输入边的个数:\n");
    scanf("%d",&e);
    for(i=0;i<e;i++) {
        getchar();//接收scanf的回车符
        printf("请输入某边所依附的两个顶点用A--%C表示\n",'A'+n-1);
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
}   //输出邻接表

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
    printf("请输入你要构建的无向图的顶点个数:\n");
    scanf("%d",&n);
    Creategraph(G,n);
    printf("深度优先遍历：\n");
    DFSTraverse(&G);
    printf("你所构建的无向图的邻接表如下所示:\n");
    printGraph(G);
    return OK;
}
