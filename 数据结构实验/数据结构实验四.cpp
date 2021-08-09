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
typedef struct {  //��ͼ����
    G *elem;
    int length;
    int size;
}ALGraphs;
/*------------------------------------------������������------------------------------------------*/
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
/*---------------------------------------------����������-------------------------------------*/
int main()
{
    VertexType V[30];
    KeyType VR[100][2];
    ALGraph *G = (ALGraph*)malloc(sizeof(ALGraph));   //ͼ  
	G->vexnum = 0;
	G->arcnum = 0;
    char GraphName[30];
    int op=1;
    int j = 0, k = 0;   //����ִ��״̬
	KeyType key = 0, key1 = 0; //��ֵ����
	VertexType value;
    ALGraphs GS;  //��ͼ
	GS.elem = NULL;
	int flag = 0;  //��ͼ������ɱ�־ 
	ALGraph* G_ope = NULL, *temp = NULL; //��ͼ����ͼ������
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
	printf("    ��ѡ����Ĳ���[0~18]:");
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
        printf("ͼ�ѱ���ʼ��������ʧ�ܣ�\n");
        else if(j == ERROR)
        printf("���������ʽ����ͼ����ʧ�ܣ�\n");
        else
        printf("�����ɹ���\n");
        getchar();getchar();
        break;
        case 2:
        j = DestroyGraph(*G);
        if(j == ERROR)
        printf("ͼΪ��,ɾ��ʧ�ܣ�\n");
        else
        printf("�ɹ�ɾ������ͼ��\n");
        getchar();getchar();
        break;
        case 3:
        printf("������Ҫ���ҵĽ��Ĺؼ��֣�\n");
        scanf("%d",&key);
        j = LocateVex(*G,key);
        if(j == -1)
        printf("�����ڸý�㣡\n");
        else
        printf("�������λ��Ϊ��%d \n",j);
        getchar();getchar();
        break;
        case 4:
        printf("������Ҫ�޸ĵĽ��Ĺؼ��ֺ��޸ĺ�����ݣ��ؼ��� + �������� \n");
        scanf("%d %d %s",&key,&value.key,value.others);
        if(PutVex(*G,key,value) == ERROR)
        printf("�޸�ʧ�ܣ��������������Ƿ�����\n");
        else 
        printf("�ɹ��޸Ķ��㣡\n");
        getchar();getchar();
        break;
        case 5:
        printf("������Ҫ���ҵĶ���ؼ��֣�\n");
        scanf("%d",&key1);
        j = FirstAdjVex(*G,key1);
        if(j == -1)
        printf("�����ڸý�㣡\n");
        else
        printf("���ĵ�һ�ڽӽ�����Ϊ��%d",j);
        getchar();getchar();
        break;
        case 6:
        printf("������Ҫ���ҵĶ���ؼ��ֺ���Խ��Ĺؼ��֣�\n");
        scanf("%d %d",&key,&key1);
        j = NextAdjVex(*G,key,key1);
        if(j == -1)
        printf("��������һ�ڽӶ��㣡\n");
        else
        printf("�ؼ���Ϊ %d ������ڽӵ� %d �Ľ�����һ�ڽӽ�����Ϊ��%d",key,key1,j);
        getchar();getchar();
        break;
        case 7:
        printf("������Ҫ����Ķ������ݣ�\n");
        scanf("%d %s",&value.key,value.others);
        j = InsertVex(*G,value);
        if(j == ERROR)
        printf("����ʧ�ܣ��������������Ƿ��������ͼ�Ƿ������\n");
        else
        printf("�ѳɹ����붥�㣡\n");
        getchar();getchar();
        break;
        case 8:
        printf("������Ҫɾ���Ķ���Ĺؼ��֣�\n");
        scanf("%d",&key);
        j = DeleteVex(*G,key);
        if(j == ERROR)
        printf("�����ڸö��㣡\n");
        else
        printf("�ѳɹ�ɾ�����㣡\n");
        getchar();getchar();
        break;
        case 9:
        printf("������Ҫ���ӵĻ������˶���ؼ��֣�\n");
        scanf("%d %d",&key,&key1);
        j = InsertArc(*G,key,key1);
        if(j == ERROR)
        printf("�����������\n");
        else
        printf("�ѳɹ����뻡��\n");
        getchar();getchar();
        break;
        case 10:
        printf("������Ҫɾ���Ļ������˶���ؼ��֣�\n");
        scanf("%d %d",&key,&key1);
        j = DeleteArc(*G,key,key1);
        if(j == ERROR)
        printf("������������Ҳ����û���\n");
        else
        printf("�ѳɹ�ɾ������\n");
        getchar();getchar();
        break;
        case 11:
        if(G->arcnum == 0)
        printf("ͼ�����ڣ�\n");
        else
        {printf("ͼ��������ȱ���Ϊ��\n");
        j = DFSTraverse(*G,visit);}
        getchar();getchar();
        break;
        case 12:
        if(G->arcnum == 0)
        printf("ͼ�����ڣ�\n");
        else
        {printf("ͼ�Ĺ�����ȱ���Ϊ��\n");
        j = BFSTraverse(*G,visit);}
        getchar();getchar();
        break;
        case 13:
        j = SaveGraph(*G,FileName);
        if(j == ERROR)
        printf("ͼΪ�գ��ļ�д��ʧ�ܣ�\n");
        else
        printf("ͼ�������ѳɹ������ļ���\n");
        getchar();getchar();
        break;
        case 14:
        if(G->vexnum != 0)
        printf("ͼ�Ѵ��ڣ���ȡ�ļ�ʧ�ܣ�\n");
        else
        {
            j == LoadGraph(*G,FileName);
            printf("�ļ��ɹ����룬ͼ�����ɹ���\n");
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
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
    }
/*-------------------------------------�������岿��--------------------------------*/
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}
status Isrepeat(VertexType V[])/*�жϹؼ����Ƿ��ظ�*/
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
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i , j , k;
    int a , b;
    ArcNode *p ,*q;
    if(G.vexnum != 0)
    return INFEASIBLE;
    if(Isrepeat(V))/*�жϽ�������Ƿ��ظ��ؼ���*/
    return ERROR;
    if(!IsVRright(V,VR))/*�жϻ����˵��Ƿ�Ϸ�*/
    return ERROR;
    if(V[0].key == -1)/*�߻��ߵ�Ϊ���������*/
    return ERROR;
    for(i = 0;V[i].key != -1;i++)
    {
        G.vertices[i].data.key = V[i].key;
        strcpy(G.vertices[i].data.others,V[i].others);
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = i;/*�����*/
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
    G.arcnum = j;/*����*/
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
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(G.vexnum == 20)/*�������20��*/
    return ERROR;
    for(int i = 0;i < G.vexnum;i++)/*�жϲ��붥���Ƿ�ᵼ�¹ؼ��ֲ�Ψһ*/
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
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int a = -1 , b = -1;/*���v,m��λ��*/
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
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int a = -1 , b = -1;/*���v,m��λ��*/
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
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
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
		if(i > MAX_VERTEX_NUM)
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
		printf("    ��ѡ����Ĳ���[0~7]:");
		scanf("%d", &op);
		switch (op)
        {
            case 1:
            j = InitALGraphs(GS);
            if(j == INFEASIBLE)
            printf("ͼ���Ѿ���ʼ�����ˣ�\n");
            else
            printf("ͼ����ʼ���ɹ���\n");
            getchar();getchar();
            break;
            case 2:
            printf("������Ҫ�����ͼ��λ�ú����֣�\n");
            scanf("%d %s",&i,GraphName);
            j = AddGraph(GS,i,GraphName);
            if(j == -2)
            printf("ͼ��δ��ʼ��������ʧ��\n");
            else if(j == ERROR)
            printf("����λ�ò��Ϸ���\n");
            else if(j == -1)
            printf("�Ѵ�����Ϊ %s ��ͼ��\n",GraphName);
            else
            printf("�ѳɹ�����ͼ��\n");
            getchar();getchar();
            break;
            case 3:
            printf("��������Ҫɾ����ͼ�����֣�\n");
            scanf("%s",GraphName);
            j = RemoveGraph(GS,GraphName);
            if(j == INFEASIBLE)
            printf("ͼ�������ڣ�����ʧ�ܣ�\n");
            else if(j == ERROR)
            printf("ͼ���в�������Ϊ %s ��ͼ��\n",GraphName);
            else
            printf("�ѳɹ�ɾ����Ϊ %s ��ͼ��\n",GraphName);
            getchar();getchar();
            break;
            case 4:
            printf("������Ҫ���ҵ�ͼ�����֣�\n");
            scanf("%s",GraphName);
            j = LocateGraph(GS,GraphName);
            if(j == ERROR)
            printf("ͼ���в�������Ϊ %s ��ͼ��\n",GraphName);
            else
            printf("ͼ %s ��ͼ���е�λ���ǣ�%d",GraphName,j);
            getchar();getchar();
            break;
            case 5:
            printf("������Ҫ�޸ĵ�ͼ�����֣�\n");
            scanf("%s",GraphName);
            j = LocateGraph(GS,GraphName);
            if(j == ERROR)
            printf("���Ҳ����ñ�\n");
            else
            return &(GS.elem[j - 1]->G);
            getchar();getchar();
            break;
            case 6:
            j = ALGraphsTraverse(GS);
            if(j == INFEASIBLE)
            printf("������ͼ����\n");
            else if(j == ERROR)
            printf("ͼ��Ϊ�գ�\n");
            getchar();getchar();
            break;
            case 7:
            if(ClearALGraphs(GS) == INFEASIBLE) 
            printf("��ǰ������δ����ʼ��!\n");
			else 
            printf("��ճɹ�!\n");
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
    if (GS.length >= GS.size) //���� 
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
    status(*p)(ALGraph &G, void (*visit)(VertexType)) = NULL;/*����ָ�룡��������*/
    while(op)
    {
        system("cls");
		printf("            ������ʽѡ��\n");
		printf("           1.������ȱ���\n");
		printf("           2.������ȱ���\n");
		printf("  ����������ѡ�������ʽ����Ӧ���[1-2],ѡ�������0����ѡ��ʽ�Կ�ʼ����:");
		scanf("%d", &op);
		switch (op)
		{
		case 1: p = DFSTraverse;   getchar();getchar();break;
		case 2: p = BFSTraverse;    getchar();getchar();break;
		}
	}
	printf("��ǰ����������������ʾ��\n");
	for (int i = 0; i < GS.length; i++)
	{
		printf("��%d��ͼ��\n %s:\n", i + 1, GS.elem[i]->name);
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