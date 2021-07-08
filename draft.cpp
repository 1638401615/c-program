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
    }
    return OK;
}
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
		if(i >= MAX_VERTEX_NUM)
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
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
{
int i=0,j,one,two;
VertexType e;
do {
    G.vertices[i].data=V[i];
    G.vertices[i].firstarc=NULL;
} while (V[i++].key!=-1);
G.vexnum=i-1;
i=0;
while (VR[i][0]!=-1) {
    ArcNode *p;
    for(j=0;j<G.vexnum;j++)
        if (VR[i][0]==G.vertices[j].data.key)
        {
            one=j; break;
        }
    for(j=0;j<G.vexnum;j++)
        if (VR[i][1]==G.vertices[j].data.key)
        {
            two=j; break;
        }
    p=(ArcNode*)malloc(sizeof(ArcNode));    
    p->adjvex=two;p->nextarc=G.vertices[one].firstarc;G.vertices[one].firstarc=p;  
    p=(ArcNode*)malloc(sizeof(ArcNode));    
    p->adjvex=one;p->nextarc=G.vertices[two].firstarc;G.vertices[two].firstarc=p;  
    i++;
} 
}
int main()
{
ALGraph G,G1;
G1.vexnum=0;
VertexType V[21];
KeyType VR[100][2];
char FileName[]="d:\\abc.txt";
int i=0;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(G,V,VR);
SaveGraph(G,FileName);
//G.vexnum=0;
LoadGraph(G1,FileName);
for(i=0;i<G1.vexnum;i++)
{
     ArcNode *p=G1.vertices[i].firstarc;
     printf("%d %s",G1.vertices[i].data.key,G1.vertices[i].data.others);
     while (p)
     {
         printf(" %d",p->adjvex);
         p=p->nextarc;
     }
     printf("\n");
}
return 1;
}
/*5 线性表 8 集合 7 二叉树 6 无向图 -1 nil  5 6  5 7 6 7 7 8 -1 -1*/
/*5 线性表 2 3
8 集合 2
7 二叉树 1 3 0
6 无向图 2 0*/