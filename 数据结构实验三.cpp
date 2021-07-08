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
	} TElemType; //二叉树结点类型定义


	typedef struct BiTNode{  //二叉链表结点的定义
	      TElemType  data;
	      struct BiTNode *lchild,*rchild;
	} BiTNode, *BiTree;
    typedef struct { //森林中每棵树的定义 
	BiTree T;
	char name[30];
} Tree, *pTree;

typedef struct {  //森林定义(线性表结构存储) 
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
/*------------------------------------函数定义部分---------------------------------*/
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
/*------------------------------------主函数部分---------------------------------------*/
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
	printf("    请选择你的操作[0~18]:");
	scanf("%d",&op);
    switch(op)
    {
        case 1:
        i = 0;
        printf("请输入各结点数据：\n");
        do {
	    scanf("%d%s",&definition[i].key,definition[i].others);
        } while (definition[i++].key!=-1);
        if (T != NULL)
        {
        	printf("二叉树已存在，创建失败！\n");
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
            printf("二叉树创建成功!\n");
        }
        else printf("关键字不唯一,二叉树创建失败！\n");
        getchar();getchar();
        break;
        case 2:
        ans = ClearBiTree(T);
        if(ans == OK)
        printf("二叉树清空成功！\n");
        else
        printf("二叉树不存在，清空失败!\n");
        getchar();getchar();
        break;
        case 3:
        ans = BiTreeDepth(T);
        if(ans == 0)
        printf("二叉树为空！\n");
        else
        printf("二叉树的深度为：%d\n",ans);
        getchar();getchar();
        break;
        case 4:
        scanf("%d",&e);
        pans = LocateNode(T,e);
        if(pans != NULL)
        printf("该结点处的关键字和储存内容为：%d %s\n",pans->data.key,pans->data.others);
        else
        printf("不存在此结点,查找失败！\n");
        getchar();getchar();
        break;
        case 5:
        printf("请输入要修改的结点关键字以及修改值（新的关键字和结点内容）\n");
        scanf("%d %d %s",&e,&value.key,value.others);
        ans = Assign(T,e,value);
        if(ans == OK)
        printf("已成功将关键字 %d 所在结点数据修改为 %d %s !\n",e,value.key,value.others);
        else if(ans == ERROR)
        printf("二叉树中不存在该结点！\n");
        else
        printf("关键字重复，修改失败！\n");
        getchar();getchar();
        break;
        case 6:
        printf("请输入想要进行操作的结点关键字\n");
        scanf("%d",&e);
        pans = GetSibling(T,e);
        if(pans != NULL)
        printf("%d 结点的兄弟结点为： %d %s\n",e,pans->data.key,pans->data.others);
        else
        printf("无法查找到兄弟结点！\n");
        getchar();getchar();
        break;
        case 7:
        printf("请输入插入处结点关键字 插入位置 待插入结点关键字和其他内容\n");
        scanf("%d %d %d %s",&e,&LR,&c.key,c.others);
        ans = InsertNode(T,e,LR,c);
        if(ans == OK)
        printf("结点已成功插入！\n");
        else if(ans == ERROR)
        printf("不存在该结点，插入失败!\n");
        else
        printf("关键字重复，结点插入失败！\n");
        getchar();getchar();
        break;
        case 8:
        printf("请输入所要删除的结点的关键字：\n");
        scanf("%d",&e);
        ans = DeleteNode(T,e);
        if(ans == OK)
        printf("关键字为 %d 结点删除成功！\n",e);
        else
        printf("不存在该结点，删除失败！\n");
        getchar();getchar();
        break;
        case 9:
        printf("二叉树的前序遍历为：");
        ans = PreOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("二叉树为空！\n");
        getchar();getchar();
        break;
        case 10:
        printf("二叉树的中序遍历为：");
        ans = InOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("二叉树为空！\n");
        getchar();getchar();
        break;
        case 11:
        printf("二叉树的后序遍历为：");
        ans = PostOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("二叉树为空！\n");
        getchar();getchar();
        break;
        case 12:
        printf("二叉树的层序遍历为：");
        ans = LevelOrderTraverse(T,visit);
        printf("\n");
        if(ans == ERROR)
        printf("二叉树为空！\n");
        getchar();getchar();
        break;
        case 13:
        ans = SaveBiTree(T,FileName);
        if(ans == OK)
        printf("已成功将二叉树写入指定文件！\n");
        else
        printf("二叉树为空，文件写入失败！\n");
        getchar();getchar();
        break;
        case 14:
        ans = LoadBiTree(T,FileName);
        if(ans != ERROR)
        printf("已成功导入文件数据并创建二叉树！\n");
        else
        printf("二叉树已存在，导入文件数据失败！\n");
        getchar();getchar();
        break;
        case 15:
        ans = CreateForest(fst);
        if(ans == OK)
        printf("森林创建成功！\n");
        else
        {
            printf("森林已存在，创建失败！\n");
        }
        getchar();getchar();
        break;
        case 16:
        printf("请输入要添加树的位置和树的名称：\n");
        scanf("%d %s", &i , BiTreeName);
        ans = AddTree(fst , i , BiTreeName);
        if(ans == INFEASIBLE)
        printf("森林不存在！\n");
        else if(ans == OK)
        printf("成功添加名为 %s 的树！\n",BiTreeName);
        else if(ans == 2)
        printf("已存在名为 %s 的树,添加失败！\n",BiTreeName);
        else
        {
            printf("插入位置不合法，请重新输入！\n");
        }
        getchar();getchar();
        break;
        case 17:
        printf("请输入所要删除的树的名字：\n");
        scanf("%s",BiTreeName);
        ans = DeleteTree(fst , BiTreeName);
        if(ans == INFEASIBLE)
        {
            printf("森林为空，操作失败！\n");
        }
        else if(ans == OK)
        {
            printf("已成功删除名为 %s 的树！\n",BiTreeName);
        }
        else
        {
            printf("不存在名为 %s 的树，删除失败！\n",BiTreeName);
        }
        getchar();getchar();
        break;
        case 18:
        printf("请输入要切换的树的名字：\n");
        scanf("%s",BiTreeName);
        ans = SwitchTree(fst , BiTreeName,T);
        if(ans == INFEASIBLE)
        printf("森林不存在！\n");
        else if(ans == OK)
        {
            printf("已成功切换到名为 %s 的树！\n",BiTreeName);
        }
        else
        {
            printf("不存在名为 %s 的树，操作失败！\n",BiTreeName);
        }
        getchar();getchar();
        break;
        case 0:
        break;  
    }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
/*-------------------------------------函数定义部分-------------------------------------------*/
bool IsRepeat(TElemType definition[])
//判断先序序列definition中是否有重复key值，用于创建树
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
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    static int k=0,flag=0;//i为递归变量，遍历definition；flag控制IsRepeat函数只被调用一次；over处理二叉树结束标志-1 
    if(flag==0&&(flag=1)&&IsRepeat(definition)) //判断是否有重复，并由于IsRepeat只需运行一次，通过flag使其成为一次性。 
    {
        return ERROR;
    }
    T=(BiTree)malloc(sizeof(BiTNode));    //先对当前结点分配空间
    //printf("In CreateBiTree, definition[%d].key = %d\n", i, definition[i].key);
    if(definition[k].key==0)     //对于 0,null，直接回溯，将分配的空间free，T置NULL，definition后移 
    {
        free(T);
        T=NULL;
        k++;
        if(definition[k].key==-1)
        {
            k=0;   //函数结束，全局变量应恢复原状 
            flag=0;
        }
        return OK;
    }else{
        T->data.key=definition[k].key;
        strcpy(T->data.others,definition[k].others);
    }
    k++;           //definition后移 
    CreateBiTree(T->lchild,definition);
    CreateBiTree(T->rchild,definition);

        /********** End **********/
    }
    status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
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
//求二叉树T的深度
{
    // 请在这里补充代码，完成本关任务
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
//查找结点
{
    // 请在这里补充代码，完成本关任务
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
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode *p = LocateNode(T, value.key);
	//p记录树中key值为value.key的结点地址用于保证赋值后的树中无key值重复项 
	BiTNode *q = LocateNode(T, e);
	//q记录结点编号为e的结点地址以查重以及赋值 
	if(!q)  //所有错误状况 
	//q为空，代表树中无编号为e结点，不可赋值；p!=q且p,q均不为空，说明赋值后会有key值重复 
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
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
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
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode *p;
    BiTNode *q = LocateNode(T, e);
    if(!q)  //所有错误状况 
	//q为空，代表树中无编号为e结点，不可赋值；p!=q且p,q均不为空，说明赋值后会有key值重复 
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
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
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
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
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
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
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
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
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
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
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
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
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
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
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
    for(int j = fst->length; j >= i; j--) //移位置 
	{
		fst->tree[j] = fst->tree[j - 1];
	}
    fst->tree[i - 1] = (pTree)malloc(sizeof(Tree));
	strcpy(fst->tree[i - 1]->name, BiTreeName); //树命名 && 树初始化 
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

