	#include "stdio.h"
	#include "stdlib.h"
    #include "string.h"
	#define TRUE 1
	#define FALSE 0
	#define OK 1
	#define ERROR 0
	#define INFEASIBLE -1
	#define OVERFLOW -2
	#define MAX_VERTEX_NUM 20
    #define INIT_SIZE 10
    #define INCREMENT 10
	typedef int status;
	typedef int KeyType; 
   typedef enum {DG,DN,UDG,UDN} GraphKind;
	typedef struct {
         KeyType  key;
         char others[20];
	} VertexType; //顶点类型定义
	typedef struct ArcNode {         //表结点类型定义
   		 int adjvex;              //顶点位置编号 
    	 struct ArcNode  *nextarc;	   //下一个表结点指针
	} ArcNode;
	typedef struct VNode{				//头结点及其数组类型定义
   		 VertexType data;       	//顶点信息
    	 ArcNode *firstarc;      	 //指向第一条弧
    	} VNode,AdjList[MAX_VERTEX_NUM];
	typedef  struct {  //邻接表的类型定义
        AdjList vertices;     	 //头结点数组
        int vexnum,arcnum;   	  //顶点数、弧数
        GraphKind  kind;        //图的类型
       } ALGraph;
int count[100] = {0};
char FileName[30];
typedef struct QNode{
    int data;
    struct QNode *next;
}QNode, *QueuePtr;
typedef struct 
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
typedef struct {
    char name[30];
    ALGraph G;
}Graph, *G;
typedef struct {  //多图定义
    G *elem;
    int length;
    int size;
}ALGraphs;
/*------------------------------------------函数声明部分------------------------------------------*/
status Isrepeat(VertexType V[]);
status IsVRright(VertexType V[],KeyType VR[][2]);
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyArcNode(ALGraph &G,int i);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void DFS(ALGraph &G,int v,void (*visit)(VertexType));
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status InitQueue(LinkQueue &Q);
status EnQueue(LinkQueue &Q, int e);
status DeQueue(LinkQueue &Q, int &e);
status QueueEmpty(LinkQueue Q);
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
ALGraph* gather_operate(ALGraphs& GS);
status InitALGraphs(ALGraphs& GS);
status AddGraph(ALGraphs& GS, int i, char GraphName[]);
status RemoveGraph(ALGraphs& GS, char GraphName[]);
int LocateGraph(ALGraphs GS, char GraphName[]);
status ALGraphsTraverse(ALGraphs GS);
status ClearALGraphs(ALGraphs& GS);
status DestroyALGraphs(ALGraphs& GS);
void visit(VertexType v);
/*---------------------------------------------主函数部分-------------------------------------*/
int main()
{
    VertexType V[30];
    KeyType VR[100][2];
    ALGraph *G = (ALGraph*)malloc(sizeof(ALGraph));   //图  
	G->vexnum = 0;
	G->arcnum = 0;
    char GraphName[30];
    int op=1;
    int j = 0, k = 0;   //函数执行状态
	KeyType key = 0, key1 = 0; //键值载体
	VertexType value;
    ALGraphs GS;  //多图
	GS.elem = NULL;
	int flag = 0;  //多图操作完成标志 
	ALGraph* G_ope = NULL, *temp = NULL; //多图操作图的载体
    strcpy(FileName,"d:\\abc.txt");
    while(op)
    {
	system("cls");	printf("\n\n");
	printf("      The graph operation menu based on the adjacent table \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateCraph     9. InsertArc\n");
	printf("    	  2. DestroyGraph    10. DeleteArc\n");
	printf("    	  3. LocateVex       11. DFSTraverse\n");
	printf("    	  4. PutVex          12. BFSTraverse\n");
	printf("    	  5. FirstAdjVex     13. SaveGraph\n");
	printf("    	  6. NextAdjVex      14. LoadGraph\n");
    printf("    	  7. InsertVex       15. ALGraphsOperate\n");
    printf("    	  8. DeleteVex       0.exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~18]:");
	scanf("%d",&op);
    switch(op)
    {
        case 1:
        do 
        {
            scanf("%d%s",&V[k].key,V[k].others);
        } while(V[k++].key!=-1);
        k=0;
        do 
        {
            scanf("%d%d",&VR[k][0],&VR[k][1]);
        } while(VR[k++][0]!=-1);
        j = CreateCraph(*G,V,VR);
        if(j == INFEASIBLE)
        printf("图已被初始化，创建失败！\n");
        else if(j == ERROR)
        printf("数据输入格式错误，图创建失败！\n");
        else
        printf("创建成功！\n");
        getchar();getchar();
        break;
        case 2:
        j = DestroyGraph(*G);
        if(j == ERROR)
        printf("图为空,删除失败！\n");
        else
        printf("成功删除无向图！\n");
        getchar();getchar();
        break;
        case 3:
        printf("请输入要查找的结点的关键字：\n");
        scanf("%d",&key);
        j = LocateVex(*G,key);
        if(j == -1)
        printf("不存在该结点！\n");
        else
        printf("结点所在位序为：%d \n",j);
        getchar();getchar();
        break;
        case 4:
        printf("请输入要修改的结点的关键字和修改后的数据（关键字 + 其他）： \n");
        scanf("%d %d %s",&key,&value.key,value.others);
        if(PutVex(*G,key,value) == ERROR)
        printf("修改失败！请检查数据输入是否有误！\n");
        else 
        printf("成功修改顶点！\n");
        getchar();getchar();
        break;
        case 5:
        printf("请输入要查找的顶点关键字：\n");
        scanf("%d",&key1);
        j = FirstAdjVex(*G,key1);
        if(j == -1)
        printf("不存在该结点！\n");
        else
        printf("结点的第一邻接结点序号为：%d",j);
        getchar();getchar();
        break;
        case 6:
        printf("请输入要查找的顶点关键字和相对结点的关键字：\n");
        scanf("%d %d",&key,&key1);
        j = NextAdjVex(*G,key,key1);
        if(j == -1)
        printf("不存在下一邻接顶点！\n");
        else
        printf("关键字为 %d 顶点的邻接点 %d 的结点的下一邻接结点序号为：%d",key,key1,j);
        getchar();getchar();
        break;
        case 7:
        printf("请输入要插入的顶点数据：\n");
        scanf("%d %s",&value.key,value.others);
        j = InsertVex(*G,value);
        if(j == ERROR)
        printf("插入失败，请检查输入数据是否有误或者图是否溢出！\n");
        else
        printf("已成功插入顶点！\n");
        getchar();getchar();
        break;
        case 8:
        printf("请输入要删除的顶点的关键字：\n");
        scanf("%d",&key);
        j = DeleteVex(*G,key);
        if(j == ERROR)
        printf("不存在该顶点！\n");
        else
        printf("已成功删除顶点！\n");
        getchar();getchar();
        break;
        case 9:
        printf("请输入要增加的弧的两端顶点关键字：\n");
        scanf("%d %d",&key,&key1);
        j = InsertArc(*G,key,key1);
        if(j == ERROR)
        printf("数据输入错误！\n");
        else
        printf("已成功插入弧！\n");
        getchar();getchar();
        break;
        case 10:
        printf("请输入要删除的弧的两端顶点关键字：\n");
        scanf("%d %d",&key,&key1);
        j = DeleteArc(*G,key,key1);
        if(j == ERROR)
        printf("数据输入错误，找不到该弧！\n");
        else
        printf("已成功删除弧！\n");
        getchar();getchar();
        break;
        case 11:
        if(G->arcnum == 0)
        printf("图不存在！\n");
        else
        {printf("图的深度优先遍历为：\n");
        j = DFSTraverse(*G,visit);}
        getchar();getchar();
        break;
        case 12:
        if(G->arcnum == 0)
        printf("图不存在！\n");
        else
        {printf("图的广度优先遍历为：\n");
        j = BFSTraverse(*G,visit);}
        getchar();getchar();
        break;
        case 13:
        j = SaveGraph(*G,FileName);
        if(j == ERROR)
        printf("图为空，文件写入失败！\n");
        else
        printf("图中数据已成功导入文件！\n");
        getchar();getchar();
        break;
        case 14:
        if(G->vexnum != 0)
        printf("图已存在，读取文件失败！\n");
        else
        {
            j == LoadGraph(*G,FileName);
            printf("文件成功导入，图创建成功！\n");
        }
        getchar();getchar();
        break;
        case 15:
        G_ope = gather_operate(GS);
        if(G_ope != NULL)
        G = G_ope;
        getchar();getchar();
        break;
        case 0:
        break;  
    }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
    }
/*-------------------------------------函数定义部分--------------------------------*/
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}
status Isrepeat(VertexType V[])/*判断关键字是否重复*/
{
    int a = 0, b = 0;
    for(int i = 0; (a = V[i].key) != -1; i++)
    {
        for(int j = i + 1; (b = (V[j].key)) != -1; j++)
        {
            if(a==b&&a!=0)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}
status IsVRright(VertexType V[],KeyType VR[][2])
{
    int count[100] = {0};
    for(int i = 0;V[i].key != -1;i++)
    {
        count[V[i].key]++;
    }
    for(int j = 0;VR[j][0] != -1;j++)
    {
        if(count[VR[j][0]] == 0 || count[VR[j][1]] == 0)
        return FALSE;
    }
    return TRUE;
}
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i , j , k;
    int a , b;
    ArcNode *p ,*q;
    if(G.vexnum != 0)
    return INFEASIBLE;
    if(Isrepeat(V))/*判断结点数组是否重复关键字*/
    return ERROR;
    if(!IsVRright(V,VR))/*判断弧两端点是否合法*/
    return ERROR;
    if(V[0].key == -1)/*边或者点为空特殊情况*/
    return ERROR;
    for(i = 0;V[i].key != -1;i++)
    {
        G.vertices[i].data.key = V[i].key;
        strcpy(G.vertices[i].data.others,V[i].others);
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = i;/*结点数*/
    if(G.vexnum > 20)
    return ERROR;
    for(j = 0;VR[j][0] != -1;j++)
    {
        for(a = 0;a < G.vexnum;a++)
        {
            if(G.vertices[a].data.key == VR[j][0])
            {
                q = (ArcNode *)malloc(sizeof(ArcNode));
                q ->adjvex = a;
                q ->nextarc = NULL;
                break;
            }
        }
        for(b = 0;b < G.vexnum;b++)
        {
            if(G.vertices[b].data.key == VR[j][1])
            {
            	p = (ArcNode *)malloc(sizeof(ArcNode));
                p ->adjvex = b;
                p ->nextarc = NULL;
                break;
            }
        }
        p -> nextarc = G.vertices[a].firstarc;
        G.vertices[a].firstarc = p;
        q -> nextarc = G.vertices[b].firstarc;
        G.vertices[b].firstarc = q;
    }
    G.arcnum = j;/*边数*/
    return OK;
    /********** End **********/
}
status DestroyArcNode(ALGraph &G,int i)
{
    ArcNode *p , *q;
    q = NULL;
    p = G.vertices[i].firstarc;
    while(p)
    {
        q = p;
        p = p -> nextarc;
        free(q);
        q = NULL;
        if(p == NULL)
        break;
    }
    return OK;
}
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum == 0)
    return ERROR;
    for(int i = 0;i < G.vexnum;i++)
    {
        DestroyArcNode(G,i);
        G.vertices[i].firstarc = NULL;
    }

    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
    /********** End **********/
}
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i = 0;i < G.vexnum;i++)
    {
        if(G.vertices[i].data.key == u)
        return i;
    }
    return -1;
    /********** End **********/
}
status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i = 0;i < G.vexnum;i++)
    {
        if(G.vertices[i].data.key == value.key)
        return ERROR;
    }
    for(int i = 0;i < G.vexnum;i++)
    {
        if(G.vertices[i].data.key == u)
        {
            G.vertices[i].data.key = value.key;
            strcpy(G.vertices[i].data.others,value.others);
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}
int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i = 0;i < G.vexnum;i++)
    {
        if(G.vertices[i].data.key == u)
        {
            return G.vertices[i].firstarc->adjvex;
        }
    }
    return -1;
    /********** End **********/
}
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    
    for(int i = 0;i < G.vexnum;i++)
        {
            if(G.vertices[i].data.key == v)
            {
                ArcNode *p = G.vertices[i].firstarc;
                while(G.vertices[p -> adjvex].data.key != w)
            {
                p = p -> nextarc;
                if(p == NULL)
                return -1;
            }
                if(p -> nextarc == NULL)
                return -1;
                else
                return (p -> nextarc -> adjvex);
            }
        }
 
    return -1;

    /********** End **********/
}
status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum == 20)/*顶点最多20个*/
    return ERROR;
    for(int i = 0;i < G.vexnum;i++)/*判断插入顶点是否会导致关键字不唯一*/
    {
        if(G.vertices[i].data.key == v.key)
        return ERROR;
    }
    G.vertices[G.vexnum].data.key = v.key;
    strcpy(G.vertices[G.vexnum].data.others,v.others);
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
    /********** End **********/
}
status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    for(i = 0;i < G.vexnum;i++)
    {
        if(G.vertices[i].data.key == v && G.vexnum != 1)
        break;
        if(i == G.vexnum - 1)
        return ERROR;
    }
    ArcNode *p = G.vertices[i].firstarc;
    ArcNode *q = NULL;
    ArcNode *t = NULL;
    while(p)
    {
        q = G.vertices[p -> adjvex].firstarc;
        if(G.vertices[p -> adjvex].firstarc -> adjvex == i)
        {
            t = G.vertices[p -> adjvex].firstarc -> nextarc;
            free(G.vertices[p -> adjvex].firstarc);
            G.vertices[p -> adjvex].firstarc = t;
            G.arcnum--;
        }
        else
        {
            while(q -> nextarc -> adjvex != i)
            q = q -> nextarc;
            t = q -> nextarc;
            q -> nextarc = t -> nextarc;
            free(t);
            G.arcnum--;
        }
        p = p -> nextarc;
    }
    int j;
    DestroyArcNode(G,i);
    for(j = i;j < G.vexnum - 1;j++)
    G.vertices[j] = G.vertices[j + 1];
    /*DestroyArcNode(G,j + 1);*/
    G.vexnum--;
    for(int k = 0;k < G.vexnum;k++)
    {
        p = G.vertices[k].firstarc;
        while(p)
        {
            if(p -> adjvex > i)
            p -> adjvex --;
            p = p -> nextarc;
        }
    }
    return OK;
    /********** End **********/
}
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int a = -1 , b = -1;/*标记v,m的位序*/
    for(int i = 0;i < G.vexnum;i++)
    {
        if(G.vertices[i].data.key == v)
        a = i;
        if(G.vertices[i].data.key == w)
        b = i;
    }
    if(a == -1 || b == -1)
    return ERROR;
    ArcNode *p = G.vertices[a].firstarc;
    ArcNode *q = G.vertices[b].firstarc;
    while(p)
    {
        if(p -> adjvex == b)
        return ERROR;
        p = p -> nextarc;
    }
    p = G.vertices[a].firstarc;
    ArcNode *t = NULL;
    t = (ArcNode *)malloc(sizeof(ArcNode));
    t ->adjvex = b;
    t ->nextarc = NULL;
    if(p == NULL)
    G.vertices[a].firstarc = t;
    else
    {
        t -> nextarc = p;
        G.vertices[a].firstarc = t;
    }
    t = (ArcNode *)malloc(sizeof(ArcNode));
    t ->adjvex = a;
    t ->nextarc = NULL;
    if(q == NULL)
    G.vertices[b].firstarc = t;
    else
    {
        t -> nextarc = q;
        G.vertices[b].firstarc = t;
    }
    G.arcnum++;
    return OK;
    /********** End **********/
}
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int a = -1 , b = -1;/*标记v,m的位序*/
    for(int i = 0;i < G.vexnum;i++)
    {
        if(G.vertices[i].data.key == v)
        a = i;
        if(G.vertices[i].data.key == w)
        b = i;
    }
    if(a == -1 || b == -1)
    return ERROR;
    ArcNode *p = G.vertices[a].firstarc;
    ArcNode *q = G.vertices[b].firstarc;
    ArcNode *t = NULL;
    while(p)
    {
        if(p -> adjvex == b)
        break;
        p = p -> nextarc;
        if(p == NULL)
        return ERROR;
    }
    p = G.vertices[a].firstarc;
    if(p -> adjvex == b)
    {
        t = p;
        G.vertices[a].firstarc = p -> nextarc;
        free(t);
    }
    else
    {
        while(p -> nextarc -> adjvex != b)
       {
            p = p -> nextarc;
       }
        t = p -> nextarc;
        p -> nextarc = t -> nextarc;
        free(t);
    }
    if(q -> adjvex == a)
    {
        t = q;
        G.vertices[b].firstarc = q -> nextarc;
        free(t);
    }
    else
    {
        while(q -> nextarc -> adjvex != a)
        {
            q = q -> nextarc;
        }
        t = q -> nextarc;
        q -> nextarc = t -> nextarc;
        free(t);
    }
    G.arcnum--;
    return OK;
    /********** End **********/
}
void DFS(ALGraph &G,int v,void (*visit)(VertexType))
{
    KeyType w;
    count[v]++;
    visit(G.vertices[v].data);
    for(w = FirstAdjVex(G,G.vertices[v].data.key); w >= 0;w = NextAdjVex(G,G.vertices[v].data.key,G.vertices[w].data.key))
    {
        if(count[w] == 0)
        DFS(G,w,visit);
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    
    for(int i = 0;i < G.vexnum;i++)
    {
        if(count[i] == 0)
        DFS(G,i,visit);
    }
    for(int i = 0;i < G.vexnum;i++)
    count[i] = 0;
    return OK;
    /********** End **********/
}
status InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front)
    exit(OVERFLOW);
    Q.front -> next = NULL;
    return OK;
}
status EnQueue(LinkQueue &Q, int e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    p -> data = e;
    p -> next = NULL;
    Q.rear -> next = p;
    Q.rear = p;
    return OK;
}
status DeQueue(LinkQueue &Q, int &e)
{
    if(Q.front == Q.rear)
    return ERROR;
    QueuePtr p;
    p = Q.front -> next;
    e = p -> data;
    Q.front -> next = p -> next;
    if(Q.rear == p)
    {
        Q.front = Q.rear;
    }
    free(p);
    return OK;
}
status QueueEmpty(LinkQueue Q)
{
    if(Q.front == Q.rear)
    return OK;
    return ERROR;
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int u;
    KeyType w;
    LinkQueue Q;
    bool visited[100];
    for(int i = 0; i < G.vexnum;i++)
    {
        visited[i] = FALSE;
    }
    InitQueue(Q);
    for(int v = 0;v < G.vexnum;v++)
    {
        if(!visited[v])
        {
            visited[v] = TRUE;
            visit(G.vertices[v].data);
            EnQueue(Q,v);
            while(!QueueEmpty(Q))
            {
                DeQueue(Q,u);
                for(w = FirstAdjVex(G,G.vertices[u].data.key); w >= 0;w = NextAdjVex(G,G.vertices[u].data.key,G.vertices[w].data.key))
                {
                    if(!visited[w])
                    {
                        visited[w] = TRUE;
                        visit(G.vertices[w].data);
                        EnQueue(Q,w);
                    }
                }
            }
        }
    }
    return OK;
    /********** End **********/
}
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    int i;
    KeyType w , v;
    ArcNode *p;
    if(G.vexnum == 0)
    return ERROR;
    FILE *fp = fopen(FileName,"w+");
    for(i = 0;i < G.vexnum;i++)
    {
        fprintf(fp,"%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
        p = G.vertices[i].firstarc;
        while (p != NULL)
        {
            fprintf(fp," %d",p -> adjvex);
            p = p -> nextarc;
        }
        fprintf(fp,"\n");
        
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE *fp = fopen(FileName,"r");
    if(fp == NULL)
    return ERROR;
    int ch = 0;
	G.vexnum = G.arcnum = 0;
    for (int i = 0; ch != EOF; i++)
	{
		if(i > MAX_VERTEX_NUM)
		{
			DestroyGraph(G);
			return INFEASIBLE;
		}
		
		//读取部分 
		fscanf(fp, "%d %s", &G.vertices[i].data.key, G.vertices[i].data.others);
		G.vexnum++;

		ch = fgetc(fp); //读掉一个空格或换行 

		if (ch != '\n')
		{
			G.vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
			ArcNode* p = G.vertices[i].firstarc;

			//读一个空格，读一个数据，读到换行直接退，此行的链表构建完成 
			while ((ch != '\n') && (ch != EOF) && fscanf(fp, "%d", &ch) != EOF)
			{
				p->adjvex = ch;

				ch = fgetc(fp);
				if (ch == '\n' || ch == EOF)
					p->nextarc = NULL;
				else
				{
					p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
					p = p->nextarc;
					p->nextarc = NULL; 
				}
				G.arcnum++;
			}
			p = NULL;
		}
		else G.vertices[i].firstarc = NULL;
	}
	--G.vexnum;
	G.arcnum /= 2;
	fclose(fp);
	return OK;
    /********** End 2 **********/
}
ALGraph* gather_operate(ALGraphs& GS)
{
    int op = 1; int j = 0; int i = 0;
	char GraphName[30];
    while (op)
    {
        system("cls");	printf("\n\n");
        printf("     Multi-plot collection operation menu\n");
		printf("--------------------------------------------\n");
		printf("    	 1. InitALGraphs       5.reviseALGraph\n");
		printf("    	 2. AddGraph           6.ALGraphsTraverse\n");
		printf("    	 3. RemoveGraph        7.ClearALGraphs\n");
		printf("    	 4. LocateGraph        0. exit\n");
		printf("--------------------------------------------\n");
		printf("    请选择你的操作[0~7]:");
		scanf("%d", &op);
		switch (op)
        {
            case 1:
            j = InitALGraphs(GS);
            if(j == INFEASIBLE)
            printf("图集已经初始化过了！\n");
            else
            printf("图集初始化成功！\n");
            getchar();getchar();
            break;
            case 2:
            printf("请输入要插入的图的位置和名字：\n");
            scanf("%d %s",&i,GraphName);
            j = AddGraph(GS,i,GraphName);
            if(j == -2)
            printf("图集未初始化！操作失败\n");
            else if(j == ERROR)
            printf("插入位置不合法！\n");
            else if(j == -1)
            printf("已存在名为 %s 的图！\n",GraphName);
            else
            printf("已成功插入图！\n");
            getchar();getchar();
            break;
            case 3:
            printf("请输入想要删除的图的名字：\n");
            scanf("%s",GraphName);
            j = RemoveGraph(GS,GraphName);
            if(j == INFEASIBLE)
            printf("图集不存在，操作失败！\n");
            else if(j == ERROR)
            printf("图集中不存在名为 %s 的图！\n",GraphName);
            else
            printf("已成功删除名为 %s 的图！\n",GraphName);
            getchar();getchar();
            break;
            case 4:
            printf("请输入要查找的图的名字：\n");
            scanf("%s",GraphName);
            j = LocateGraph(GS,GraphName);
            if(j == ERROR)
            printf("图集中不存在名为 %s 的图！\n",GraphName);
            else
            printf("图 %s 在图集中的位置是：%d",GraphName,j);
            getchar();getchar();
            break;
            case 5:
            printf("请输入要修改的图的名字：\n");
            scanf("%s",GraphName);
            j = LocateGraph(GS,GraphName);
            if(j == ERROR)
            printf("查找不到该表！\n");
            else
            return &(GS.elem[j - 1]->G);
            getchar();getchar();
            break;
            case 6:
            j = ALGraphsTraverse(GS);
            if(j == INFEASIBLE)
            printf("不存在图集！\n");
            else if(j == ERROR)
            printf("图集为空！\n");
            getchar();getchar();
            break;
            case 7:
            if(ClearALGraphs(GS) == INFEASIBLE) 
            printf("当前集合尚未被初始化!\n");
			else 
            printf("清空成功!\n");
            getchar();getchar();
            break;
            case 0:
            break;
        }
    }
    return NULL;
}
status InitALGraphs(ALGraphs& GS)
{
    if(GS.elem != NULL)
    return INFEASIBLE;
    GS.elem = (G*)calloc(INIT_SIZE, sizeof(G));
	GS.length = 0;
	GS.size = INIT_SIZE;
	return OK;
}
status AddGraph(ALGraphs& GS, int i, char GraphName[])
{
    if(GS.elem == NULL)
    return -2;
    if (i > GS.length + 1 || i < 1) 
    return ERROR;
    for(int t = 0; t < GS.length; t++)
	{
		if(!strcmp(GraphName, GS.elem[t]->name))
		return -1;
	}
    G p = (Graph *)malloc(sizeof(Graph));
    strcpy(p -> name,GraphName);
    p -> G.arcnum = p ->G.vexnum = 0;
    if (GS.length >= GS.size) //扩容 
	{
		GS.size += INCREMENT;
		GS.elem = (G*)realloc(GS.elem, GS.size * sizeof(G));
	}
	for(int j = GS.length;j >= i;j--)
    {
        GS.elem[j] = GS.elem[j - 1];
    }
    GS.elem[i - 1] = p;
    GS.length++;
    return OK;
}
status RemoveGraph(ALGraphs& GS, char GraphName[])
{
    if(GS.elem == NULL)
    return INFEASIBLE;
    for(int i = 0;i < GS.length;i++)
    {
        if(!strcmp(GS.elem[i]->name,GraphName))
        {
            DestroyGraph(GS.elem[i]->G);
            free(GS.elem[i]);
            for(int j = i;j < GS.length - 1;j++)
            GS.elem[j] = GS.elem[j + 1];
            GS.length--;
            return OK;
        }
    }
    return ERROR;
}
int LocateGraph(ALGraphs GS, char GraphName[])
{
    if(GS.elem == NULL)
    return INFEASIBLE;
    for(int i = 0;i < GS.length;i++)
    {
        if(!strcmp(GS.elem[i]->name,GraphName))
        return i + 1;
    }
    return ERROR;
}
status ALGraphsTraverse(ALGraphs GS)
{
    if (GS.elem == NULL) return INFEASIBLE;
	if (GS.length == 0) return ERROR;
	int op = 1;
    status(*p)(ALGraph &G, void (*visit)(VertexType)) = NULL;/*函数指针！！！！！*/
    while(op)
    {
        system("cls");
		printf("            遍历方式选择\n");
		printf("           1.深度优先遍历\n");
		printf("           2.广度优先遍历\n");
		printf("  请输入您所选择遍历方式的相应序号[1-2],选择后输入0保存选择方式以开始遍历:");
		scanf("%d", &op);
		switch (op)
		{
		case 1: p = DFSTraverse;   getchar();getchar();break;
		case 2: p = BFSTraverse;    getchar();getchar();break;
		}
	}
	printf("当前集合中数据如下所示：\n");
	for (int i = 0; i < GS.length; i++)
	{
		printf("第%d个图：\n %s:\n", i + 1, GS.elem[i]->name);
		p(GS.elem[i]->G, visit);
		printf("\n\n");
	}
	return OK;
}
status ClearALGraphs(ALGraphs& GS)
{
    if(GS.elem == NULL)
    return INFEASIBLE;
    for(int i = 0;i < GS.length;i++)
    {
        DestroyGraph(GS.elem[i]->G);
        free(GS.elem[i]);
        GS.elem[i] = NULL;
    }
    GS.length = 0;
    return OK;
}
status DestroyALGraphs(ALGraphs& GS)
{
    if (GS.elem == NULL) return INFEASIBLE;
	ClearALGraphs(GS);
	GS.size = 0;
	free(GS.elem);
	GS.elem = NULL;
	return OK;
}