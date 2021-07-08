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
	} VertexType; //�������Ͷ���


	typedef struct ArcNode {         //�������Ͷ���
   		 int adjvex;              //����λ�ñ�� 
    	 struct ArcNode  *nextarc;	   //��һ������ָ��
	} ArcNode;
	typedef struct VNode{				//ͷ��㼰���������Ͷ���
   		 VertexType data;       	//������Ϣ
    	 ArcNode *firstarc;      	 //ָ���һ����
    	} VNode,AdjList[MAX_VERTEX_NUM];
	typedef  struct {  //�ڽӱ�����Ͷ���
        AdjList vertices;     	 //ͷ�������
        int vexnum,arcnum;   	  //������������
        GraphKind  kind;        //ͼ������
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
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
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
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
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
		
		//��ȡ���� 
		fscanf(fp, "%d %s", &G.vertices[i].data.key, G.vertices[i].data.others);
		G.vexnum++;

		ch = fgetc(fp); //����һ���ո���� 

		if (ch != '\n')
		{
			G.vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
			ArcNode* p = G.vertices[i].firstarc;

			//��һ���ո񣬶�һ�����ݣ���������ֱ���ˣ����е���������� 
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
/*5 ���Ա� 8 ���� 7 ������ 6 ����ͼ -1 nil  5 6  5 7 6 7 7 8 -1 -1*/
/*5 ���Ա� 2 3
8 ���� 2
7 ������ 1 3 0
6 ����ͼ 2 0*/