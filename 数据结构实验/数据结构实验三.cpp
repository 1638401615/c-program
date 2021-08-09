#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define INCREMENT 10
#define INIT_SIZE 100
	typedef int status;
	typedef int KeyType; 
	typedef struct {
         KeyType  key;
         char others[20];
	} TElemType; //������������Ͷ���


	typedef struct BiTNode{  //����������Ķ���
	      TElemType  data;
	      struct BiTNode *lchild,*rchild;
	} BiTNode, *BiTree;
    typedef struct { //ɭ����ÿ�����Ķ��� 
	BiTree T;
	char name[30];
} Tree, *pTree;

typedef struct {  //ɭ�ֶ���(���Ա�ṹ�洢) 
	pTree *tree;
	int length;
	int size;
} FOREST, *FST;
int count[100] = {0};
char FileName[30];
int flag1 = 0;
BiTree T = NULL;
TElemType definition[100];
FST fst = NULL;
int n = 0 , pattern = 0;
int f[100] = {0};
/*------------------------------------�������岿��---------------------------------*/
bool IsRepeat(TElemType definition[]);
status CreateBiTree(BiTree &T,TElemType definition[]);
status ClearBiTree(BiTree &T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
void bianli(BiTree &T);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status printLevel(BiTree T, int level,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T,  char FileName[]);
void visit(BiTree T);
status CreateForest(FST &fst);
status DeleteTree(FST &fst , char BiTreeName[]);
status AddTree(FST &fst , int i , char BiTreeName[]);
status SwitchTree(FST &fst , char BiTreeName[],BiTree &T);
/*------------------------------------����������---------------------------------------*/
int main()
{
    char BiTreeName[30];
    strcpy(FileName,"d:\\abc.txt");
    int op=1;
    int ans , i = 0 , LR;
    KeyType e;
    TElemType value , c;
    BiTNode* pans;
    while(op)
    {
	system("cls");	printf("\n\n");
	printf("      Menu for Binary Trees On Chain Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateBiTree     10. InOrderTraverse\n");
	printf("    	  2. ClearBiTree      11. PostOrderTraverse\n");
	printf("    	  3. BiTreeDepth      12. LevelOrderTraverse\n");
	printf("    	  4. LocateNode       13. SaveBiTree\n");
	printf("    	  5. Assign           14. LoadBiTree\n");
	printf("    	  6. GetSibling       15. CreateForest\n");
    printf("    	  7. InsertNode       16. AddTree\n");
    printf("    	  8. DeleteNode       17. DeleteTree\n");
	printf("    	  9. PreOrderTraverse 18. SwitchTree\n");
	printf("          0.exit"); 
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~18]:");
	scanf("%d",&op);
    switch(op)
    {
        case 1:
        i = 0;
        printf("�������������ݣ�\n");
        do {
	    scanf("%d%s",&definition[i].key,definition[i].others);
        } while (definition[i++].key!=-1);
        if (T != NULL)
        {
        	printf("�������Ѵ��ڣ�����ʧ�ܣ�\n");
        	getchar();getchar();
        	break;	 
		}
        ans=CreateBiTree(T,definition);
        if (ans!=ERROR)
        {
        	if(pattern == 1)
        	{
        		fst -> tree[n] -> T = T;
        		fst -> tree[n] -> T -> data = T -> data;
        		pattern = 0;
			}
            printf("�����������ɹ�!\n");
        }
        else printf("�ؼ��ֲ�Ψһ,����������ʧ�ܣ�\n");
        getchar();getchar();
        break;
        case 2:
        ans = ClearBiTree(T);
        if(ans == OK)
        printf("��������ճɹ���\n");
        else
        printf("�����������ڣ����ʧ��!\n");
        getchar();getchar();
        break;
        case 3:
        ans = BiTreeDepth(T);
        if(ans == 0)
        printf("������Ϊ�գ�\n");
        else
        printf("�����������Ϊ��%d\n",ans);
        getchar();getchar();
        break;
        case 4:
        scanf("%d",&e);
        pans = LocateNode(T,e);
        if(pans != NULL)
        printf("�ý�㴦�Ĺؼ��ֺʹ�������Ϊ��%d %s\n",pans->data.key,pans->data.others);
        else
        printf("�����ڴ˽��,����ʧ�ܣ�\n");
        getchar();getchar();
        break;
        case 5:
        printf("������Ҫ�޸ĵĽ��ؼ����Լ��޸�ֵ���µĹؼ��ֺͽ�����ݣ�\n");
        scanf("%d %d %s",&e,&value.key,value.others);
        ans = Assign(T,e,value);
        if(ans == OK)
        printf("�ѳɹ����ؼ��� %d ���ڽ�������޸�Ϊ %d %s !\n",e,value.key,value.others);
        else if(ans == ERROR)
        printf("�������в����ڸý�㣡\n");
        else
        printf("�ؼ����ظ����޸�ʧ�ܣ�\n");
        getchar();getchar();
        break;
        case 6:
        printf("��������Ҫ���в����Ľ��ؼ���\n");
        scanf("%d",&e);
        pans = GetSibling(T,e);
        if(pans != NULL)
        printf("%d �����ֵܽ��Ϊ�� %d %s\n",e,pans->data.key,pans->data.others);
        else
        printf("�޷����ҵ��ֵܽ�㣡\n");
        getchar();getchar();
        break;
        case 7:
        printf("��������봦���ؼ��� ����λ�� ��������ؼ��ֺ���������\n");
        scanf("%d %d %d %s",&e,&LR,&c.key,c.others);
        ans = InsertNode(T,e,LR,c);
        if(ans == OK)
        printf("����ѳɹ����룡\n");
        else if(ans == ERROR)
        printf("�����ڸý�㣬����ʧ��!\n");
        else
        printf("�ؼ����ظ���������ʧ�ܣ�\n");
        getchar();getchar();
        break;
        case 8:
        printf("��������Ҫɾ���Ľ��Ĺؼ��֣�\n");
        scanf("%d",&e);
        ans = DeleteNode(T,e);
        if(ans == OK)
        printf("�ؼ���Ϊ %d ���ɾ���ɹ���\n",e);
        else
        printf("�����ڸý�㣬ɾ��ʧ�ܣ�\n");
        getchar();getchar();
        break;
        case 9:
        printf("��������ǰ�����Ϊ��");
        ans = PreOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("������Ϊ�գ�\n");
        getchar();getchar();
        break;
        case 10:
        printf("���������������Ϊ��");
        ans = InOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("������Ϊ�գ�\n");
        getchar();getchar();
        break;
        case 11:
        printf("�������ĺ������Ϊ��");
        ans = PostOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("������Ϊ�գ�\n");
        getchar();getchar();
        break;
        case 12:
        printf("�������Ĳ������Ϊ��");
        ans = LevelOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("������Ϊ�գ�\n");
        getchar();getchar();
        break;
        case 13:
        ans = SaveBiTree(T,FileName);
        if(ans == OK)
        printf("�ѳɹ���������д��ָ���ļ���\n");
        else
        printf("������Ϊ�գ��ļ�д��ʧ�ܣ�\n");
        getchar();getchar();
        break;
        case 14:
        ans = LoadBiTree(T,FileName);
        if(ans != ERROR)
        printf("�ѳɹ������ļ����ݲ�������������\n");
        else
        printf("�������Ѵ��ڣ������ļ�����ʧ�ܣ�\n");
        getchar();getchar();
        break;
        case 15:
        ans = CreateForest(fst);
        if(ans == OK)
        printf("ɭ�ִ����ɹ���\n");
        else
        {
            printf("ɭ���Ѵ��ڣ�����ʧ�ܣ�\n");
        }
        getchar();getchar();
        break;
        case 16:
        printf("������Ҫ�������λ�ú��������ƣ�\n");
        scanf("%d %s", &i , BiTreeName);
        ans = AddTree(fst , i , BiTreeName);
        if(ans == INFEASIBLE)
        printf("ɭ�ֲ����ڣ�\n");
        else if(ans == OK)
        printf("�ɹ������Ϊ %s ������\n",BiTreeName);
        else if(ans == 2)
        printf("�Ѵ�����Ϊ %s ����,���ʧ�ܣ�\n",BiTreeName);
        else
        {
            printf("����λ�ò��Ϸ������������룡\n");
        }
        getchar();getchar();
        break;
        case 17:
        printf("��������Ҫɾ�����������֣�\n");
        scanf("%s",BiTreeName);
        ans = DeleteTree(fst , BiTreeName);
        if(ans == INFEASIBLE)
        {
            printf("ɭ��Ϊ�գ�����ʧ�ܣ�\n");
        }
        else if(ans == OK)
        {
            printf("�ѳɹ�ɾ����Ϊ %s ������\n",BiTreeName);
        }
        else
        {
            printf("��������Ϊ %s ������ɾ��ʧ�ܣ�\n",BiTreeName);
        }
        getchar();getchar();
        break;
        case 18:
        printf("������Ҫ�л����������֣�\n");
        scanf("%s",BiTreeName);
        ans = SwitchTree(fst , BiTreeName,T);
        if(ans == INFEASIBLE)
        printf("ɭ�ֲ����ڣ�\n");
        else if(ans == OK)
        {
            printf("�ѳɹ��л�����Ϊ %s ������\n",BiTreeName);
        }
        else
        {
            printf("��������Ϊ %s ����������ʧ�ܣ�\n",BiTreeName);
        }
        getchar();getchar();
        break;
        case 0:
        break;  
    }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}
/*-------------------------------------�������岿��-------------------------------------------*/
bool IsRepeat(TElemType definition[])
//�ж���������definition���Ƿ����ظ�keyֵ�����ڴ�����
{
    int a = 0, b = 0;
    for(int i = 0; (a = definition[i].key) != -1; i++)
    {
        for(int j = i + 1; (b = (definition[j].key)) != -1; j++)
        {
            if(a==b&&a!=0)
            {
                return true;
            }
        }
    }
    return false;
}
status CreateBiTree(BiTree &T,TElemType definition[])
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    static int k=0,flag=0;//iΪ�ݹ����������definition��flag����IsRepeat����ֻ������һ�Σ�over���������������־-1 
    if(flag==0&&(flag=1)&&IsRepeat(definition)) //�ж��Ƿ����ظ���������IsRepeatֻ������һ�Σ�ͨ��flagʹ���Ϊһ���ԡ� 
    {
        return ERROR;
    }
    T=(BiTree)malloc(sizeof(BiTNode));    //�ȶԵ�ǰ������ռ�
    //printf("In CreateBiTree, definition[%d].key = %d\n", i, definition[i].key);
    if(definition[k].key==0)     //���� 0,null��ֱ�ӻ��ݣ�������Ŀռ�free��T��NULL��definition���� 
    {
        free(T);
        T=NULL;
        k++;
        if(definition[k].key==-1)
        {
            k=0;   //����������ȫ�ֱ���Ӧ�ָ�ԭ״ 
            flag=0;
        }
        return OK;
    }else{
        T->data.key=definition[k].key;
        strcpy(T->data.others,definition[k].others);
    }
    k++;           //definition���� 
    CreateBiTree(T->lchild,definition);
    CreateBiTree(T->rchild,definition);

        /********** End **********/
    }
    status ClearBiTree(BiTree &T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T)
    {
        ClearBiTree(T -> lchild);
        ClearBiTree(T -> rchild);
        free(T);
        T = NULL;
        return OK;
    }
    return ERROR;
    /********** End **********/
}
int BiTreeDepth(BiTree T)
//�������T�����
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int d1 = 0 , d2 = 0;
    if(T == NULL)
    return 0;
    d1 = BiTreeDepth(T -> lchild);
    d2 = BiTreeDepth(T -> rchild);
    if(d1 > d2)
    return (d1 + 1);
    else
    return (d2 + 1);
    /********** End **********/
}
BiTNode* LocateNode(BiTree T,KeyType e)
//���ҽ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    BiTNode* p;
    if(T == NULL)
    return NULL;
    if(T -> data.key == e)
    return T;
    else
    {
        p = LocateNode(T -> lchild,e);
        if(p != NULL)
        return p;
        else
        return LocateNode(T -> rchild,e);
    }
    /********** End **********/
}
status Assign(BiTree &T,KeyType e,TElemType value)
//ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    BiTNode *p = LocateNode(T, value.key);
	//p��¼����keyֵΪvalue.key�Ľ���ַ���ڱ�֤��ֵ���������keyֵ�ظ��� 
	BiTNode *q = LocateNode(T, e);
	//q��¼�����Ϊe�Ľ���ַ�Բ����Լ���ֵ 
	if(!q)  //���д���״�� 
	//qΪ�գ����������ޱ��Ϊe��㣬���ɸ�ֵ��p!=q��p,q����Ϊ�գ�˵����ֵ�����keyֵ�ظ� 
    {
    	return ERROR;
	}
    if(p && q && p != q)
    {
        return INFEASIBLE;
    }
	else
	{
		q->data.key = value.key;
		strcpy(q->data.others, value.others);
		return OK;
	}
    /********** End **********/
}
BiTNode* GetSibling(BiTree T,KeyType e)
//ʵ�ֻ���ֵܽ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    BiTNode *p;
    if(T -> lchild == NULL || T -> rchild == NULL)
    return NULL;
    if(T -> lchild -> data.key == e)
    return (T -> rchild);
    else if(T -> rchild -> data.key == e)
    return (T -> lchild);
    else
    {
        p = GetSibling(T -> lchild,e);
        if(p != NULL)
        return p;
        else
        return GetSibling(T -> rchild,e);
    }
    /********** End **********/
}
void bianli(BiTree &T)
{
    if(T == NULL)
    return;
    if(T)
    count[T -> data.key]++;
    if(T -> lchild)
    bianli(T -> lchild);
    if(T -> rchild)
    bianli(T -> rchild);
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//�����㡣��������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    BiTNode *p;
    BiTNode *q = LocateNode(T, e);
    if(!q)  //���д���״�� 
	//qΪ�գ����������ޱ��Ϊe��㣬���ɸ�ֵ��p!=q��p,q����Ϊ�գ�˵����ֵ�����keyֵ�ظ� 
    {
    	return ERROR;
	}
    if(p && q && p != q)
    {
        return INFEASIBLE;
    }
    p = (BiTNode *)malloc(sizeof(BiTNode));
    p -> data = c;
    if(flag1 == 0)
    {
    	bianli(T);
    	flag1 = 1;
	}
	if(T == NULL)
	return ERROR;
    if(LR == -1 && count[c.key] == 0)
    {
        p -> rchild = T;
        T = p;
        return OK;
    }
    else if(LR == 0 && count[c.key] == 0)
    {
        if(T -> data.key == e)
        {
            p -> rchild = T -> lchild;
            p -> lchild = NULL;
            T -> lchild = p;
            return OK;
        }
        else
        {
            if(InsertNode(T -> lchild,e,LR,c) == OK)
            return OK;
            else
            return InsertNode(T -> rchild,e,LR,c);
        }
         
    }
    else if(LR == 1 && count[c.key] == 0)
    {
        if(T -> data.key == e)
        {
            p -> rchild = T -> rchild;
            p -> lchild = NULL;
            T -> rchild = p;
            return OK;
        }
        else
        {
            if(InsertNode(T -> lchild,e,LR,c) == OK)
            {
                return OK;
            }
            else
            return InsertNode(T -> rchild,e,LR,c);
        }
         
    }
    return ERROR;
    /********** End **********/
}
status DeleteNode(BiTree &T,KeyType e)
//ɾ����㡣��������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    BiTree p , q;
    if(T == NULL)
    return ERROR;
    if(T -> data.key == e)
    {
        if(T -> lchild == NULL && T -> rchild == NULL)
        {
            free(T);
            T = NULL;
            return OK;
        }
        else if(T -> lchild == NULL && T -> rchild != NULL)
        {
            p = T;
            T = T -> rchild;
            free(p);
            return OK;
        }
        else if(T -> lchild != NULL && T -> rchild == NULL)
        {
            p = T;
            T = T -> lchild;
            free(p);
            return OK;
        }
        else if(T -> lchild != NULL && T -> rchild != NULL)
        {
            p = T;
            T = T -> lchild;
            q = T;
            while(q -> rchild)
            {
                q = q -> rchild;
            }
            q -> rchild = p -> rchild;
            free(p);
            return OK;
        }
    }
    else
    {
        if(DeleteNode(T -> lchild,e) == OK)
        return OK;
        if(DeleteNode(T -> rchild,e) == OK)
        return OK;
    }
    return ERROR;
    /********** End **********/
}
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T == NULL)
    return ERROR;
    BiTree st[101];
    int top = 0;
    do
    {
        while(T)
        {
            if(top == 100)
            exit(OVERFLOW);
            st[++top] = T;
            visit(T);
            T = T -> lchild;
        }
        if(top)
        {
            T = st[top--];
            T = T -> rchild;
        }
    }while(top || T);
    return OK;
    /********** End **********/
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T == NULL)
    return ERROR;
    BiTree st[101];
    int top = 0;
    do
    {
        while(T)
        {
            if(top == 100)
            exit(OVERFLOW);
            st[++top] = T;
            T = T -> lchild;
        }
        if(top)
        {
            T = st[top--];
            visit(T);
            T = T -> rchild;
        }
    }while(top || T);
    return OK;
    /********** End **********/
}
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T == NULL)
    return ERROR;
    if(T)
    {
        PostOrderTraverse(T -> lchild,visit);
        PostOrderTraverse(T -> rchild,visit);
        visit(T);
    }
    return OK;
    /********** End **********/
}
status printLevel(BiTree T, int level,void (*visit)(BiTree)) 
{
	if(!T || level < 0) {
		return false;
	}
	if(level == 0) {
		visit(T);
		return true;
	}
	return printLevel(T->lchild, level - 1,visit) + printLevel(T->rchild, level - 1,visit);
}
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T == NULL)
    return ERROR;
    int i;
    for(i = 0; ;i++)
    {
        if(!printLevel(T,i,visit))
        break;
    }
    return OK;
    /********** End **********/
}
status SaveBiTree(BiTree T, char FileName[])
//���������Ľ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    static FILE *fp = fopen(FileName, "w+");
	static int flag = 1;
	int over = 0;
	int key = 0; char others[20] = "null";
    
	if(flag == 1)
	{
		over = 1;
		flag = 0;
	}
	if(T != NULL)
	{
		key = T->data.key;
		strcpy(others, T->data.others);
	}
	fprintf(fp, "%d %s ", key, others);
	if(T == NULL) return OK;
	SaveBiTree(T->lchild, FileName);
	SaveBiTree(T->rchild, FileName);
	if(over)
	{
		fprintf(fp, "%d %s ", -1, "null");
		fclose(fp);
	}
	return OK;


    /********** End 1 **********/
}
status LoadBiTree(BiTree &T,  char FileName[])
//�����ļ�FileName�Ľ�����ݣ�����������
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    if(T != NULL)
    return ERROR;
    FILE *fp = fopen(FileName, "r");
    if(fp == NULL) return ERROR;
    int i = 0;
    int number = 0;
    TElemType definition[100];
    while(fscanf(fp, "%d", &definition[i].key) != EOF && fscanf(fp, "%s", &definition[i].others) != EOF) i++;
	CreateBiTree(T, definition);
	fclose(fp);
	return OK;
}
    /********** End 2 **********/
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}
status CreateForest(FST &fst)
{
    if(fst != NULL)
    return INFEASIBLE;
    else
    {
        fst = (FST)malloc(sizeof(FOREST));
	    fst->tree = (pTree*)malloc(INIT_SIZE * sizeof(pTree));
	    fst->length = 0;
	    fst->size = INIT_SIZE;
	    return OK;
    }
}
status AddTree(FST &fst, int i ,char BiTreeName[])
{
    if(fst == NULL)
    return INFEASIBLE;
    if(i > fst -> length + 1 || i < 1)
    return ERROR;
    if(fst -> length >= fst -> size)
    {
        fst->size += INCREMENT;
		fst->tree = (pTree*)realloc(fst->tree, fst->size * sizeof(pTree));
    }
    for(int k = 0;k < fst -> length;k++)
    {
        if(!strcmp(fst -> tree[k] ->name,BiTreeName))
        return 2;
    }
    for(int j = fst->length; j >= i; j--) //��λ�� 
	{
		fst->tree[j] = fst->tree[j - 1];
	}
    fst->tree[i - 1] = (pTree)malloc(sizeof(Tree));
	strcpy(fst->tree[i - 1]->name, BiTreeName); //������ && ����ʼ�� 
	fst->tree[i - 1]->T = NULL;
	fst->length++;
	return OK;
}
status DeleteTree(FST &fst, char BiTreeName[])
{
	if(fst == NULL) 
    return INFEASIBLE;
	for(int i = 0; i < fst->length; i++)
	{
		if(!strcmp(BiTreeName, fst->tree[i]->name))
		{
			ClearBiTree(fst->tree[i]->T);
			free(fst->tree[i]);
			
			for(int a = i + 1; a < fst->length; a++)
			fst->tree[a - 1] = fst->tree[a];
			
			fst->length--;
			return OK;
		}
	}
	return ERROR;
}
status SwitchTree(FST &fst , char BiTreeName[] ,BiTree &T)
{
    if(fst == NULL) 
    return INFEASIBLE;
    for(n = 0;n < fst -> length;n++)
    {
        if(!strcmp(BiTreeName , fst -> tree[n] -> name))
        {
            ClearBiTree(T);
            pattern = 1;
            return OK;
        }
    }
    return ERROR;
}

