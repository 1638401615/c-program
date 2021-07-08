#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
FILE *fp;
char FileName[30];
int x;
typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //线性表的管理表定义
     struct { char name[30];
     		  LinkList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 LinkList L;
 LISTS Lists;
/*-----------------------------------函数声明部分--------------------------------------------*/
status InitList(LinkList& L);                             
status DestroyList(LinkList& L);
status ClearList(LinkList& L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
int LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status  SaveList(LinkList L,char FileName[]);
status  LoadList(LinkList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
/*------------------------------------主函数部分---------------------------------------------*/
int main()
{
    strcpy(FileName,"d:\\abc.txt");
    int i , j , e , pre , next;
	Lists.length = 0;  
    int op=1;
    while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       10. ListInsert\n");
	printf("    	  2. DestroyList    11. ListDelete\n");
	printf("    	  3. ClearList      12. ListTrabverse\n");
	printf("    	  4. ListEmpty      13. SaveList\n");
	printf("    	  5. ListLength     14. LoadList\n");
	printf("    	  6. GetElem        15. AddList\n");
    printf("    	  7. LocateElem     16. RemoveList\n");
    printf("    	  8. PriorElem      17.LocateList\n");
	printf("    	  9. NextElem       18.changeList\n");
	printf("          0.exit"); 
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~18]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 if(InitList(L)==OK) 
         printf("线性表创建成功！\n");
		 else 
         printf("线性表创建失败！\n");
         getchar();getchar();
         break;
	   case 2:
		 if(DestroyList(L) == OK)
         printf("线性表删除成功！\n");
         else
         printf("线性表删除失败！请检查是否存在线性表！\n");
		 getchar();getchar();
		 break;
	   case 3:
		 if(ClearList(L) == OK)
         printf("线性表清空成功！\n");
         else
         printf("线性表清空失败！请检查是否存在线性表！\n");     
		 getchar();getchar();
		 break;
	   case 4:
		 if(ListEmpty(L) == TRUE)
         printf("线性表为空！\n");
         else if(ListEmpty(L) == FALSE)
         printf("线性表不为空！\n");
         else
         printf("线性表不存在！\n");     
		 getchar();getchar();
		 break;
	   case 5:
		 int len;
         len =  ListLength(L);
         if(len == INFEASIBLE)
         printf("线性表长度求取失败！请检查是否存在线性表！\n");
         else
         printf("线性表长度为：%d\n",len);    
		 getchar();getchar();
		 break;
	   case 6:
         scanf("%d",&i);
		 j=GetElem(L,i,e);
         if(j == INFEASIBLE)
         printf("线性表不存在！\n");
         else if(j == ERROR)    
         printf("输入位置不合法！\n");
         else
         printf("%d处获取的元素为：%d",i,e);
		 getchar();getchar();
		 break;
	   case 7:
         scanf("%d",&e);
		 j = LocateElem(L,e);     
		 if(j == INFEASIBLE)
         printf("线性表不存在！\n");
         else if(j == ERROR)
         printf("查找失败！线性表中不存在值为%d的元素！\n",e);
         else
         printf("线性表中 %d 所在的位置是：%d\n",e,j);
         getchar();getchar();
		 break;
	   case 8:
         int pre; 
		 scanf("%d",&e);
		 j = PriorElem(L,e,pre);
         if(j == INFEASIBLE)
         printf("线性表不存在！\n");    
         else if(j == ERROR)
         printf("没有找到指定元素%d的前驱元素！查找失败！\n",e);
         else
         printf("元素 %d 的前驱元素是：%d\n",e,pre);
		 getchar();getchar();
		 break;
	   case 9:
	   	 int next;
	   	 scanf("%d",&e);
	   	 j = NextElem(L,e,next);
	   	 if(j == INFEASIBLE)
         printf("线性表不存在！\n");    
         else if(j == ERROR)
         printf("没有找到指定元素%d的后继元素！查找失败！\n",e);
         else
         printf("元素 %d 的后继元素是：%d\n",e,next);    
		 getchar();getchar();
		 break;
	   case 10:
		 scanf("%d%d",&i,&e);
         j = ListInsert(L,i,e);  
         if(j == INFEASIBLE)
         printf("线性表不存在！\n");
         else if(j == ERROR)
         printf("插入元素失败!请检查插入位置选择是否正确！\n");
         else
         {
         	printf("元素插入成功！\n");
         	
		 }
		 getchar();getchar();
		 break;
	   case 11:
		 scanf("%d",&i);
		 j=ListDelete(L,i,e); 
         if(j == INFEASIBLE)
         printf("线性表不存在！\n");
         else if(j == ERROR)
         printf("删除元素失败!请检查删除位置选择是否正确！\n");   
         else
         printf("元素 %d 已被成功删除！\n",e); 
		 getchar();getchar();
		 break;
	   case 12:
		 j=ListTraverse(L);
         if(j == INFEASIBLE)
         printf("线性表不存在！\n");
         else if(j==OK && !L -> next) 
         printf("线性表是空表！\n");    
		 
		getchar();getchar();
		 break;
       case 13:
         j=SaveList(L,FileName);
         if(j == INFEASIBLE)
         printf("线性表不存在！\n");
         else
         printf("数据成功导入文件！\n");  
         getchar();getchar();
         break;
       case 14:
         j=LoadList(L,FileName);
         if(j == INFEASIBLE)
         printf("线性表已存在，载入失败！\n");
         else
         printf("成功载入文件数据！\n");  
         getchar();getchar();
         break;
       case 15: 
         char name[30];
         scanf("%s",name);
         j = AddList(Lists,name);
         if(j)
         printf("线性表增加成功！\n");
         getchar();getchar();
         break;
       case 16:
         char name1[30];
         scanf("%s",name1);
         j = RemoveList(Lists,name1);
         if(j == OK)
         printf("线性表 %s 删除成功！\n",name1);
         else
         printf("不存在名为 %s 的线性表，删除失败！\n",name1);
		 getchar();getchar();
         break;
       case 17:
       	 char name2[30];
       	 scanf("%s",name2);
       	 j = LocateList(Lists,name2);
       	 if(j != 0)
       	 {
       	 	printf("线性表 %s 在Lists中的位置是：%d\n",name2,j);
       	 	
			}
       	 else
       	 printf("Lists中没有名为 %s 的线性表！\n",name2);
         getchar();getchar(); 
         break;
        case 18:
		 char name3[30];
		 scanf("%s",name3);
		 x = LocateList(Lists,name3);
		 if(x != 0)
		 {
		 	printf("已成功切换到 %s 线性表！\n",name3);
		 	L = Lists.elem[x - 1].L;/*切换进去出来数据就无了*/ 
		 	
		  }  
		  else
		  printf("Lists中没有名为 %s 的线性表！\n",name3);
		  getchar();getchar();
	   case 0:
         break;
	}//end of switch
  }//end of while
printf("欢迎下次再使用本系统！\n");
    return 0;
}
/*-------------------------------------函数定义部分-------------------------------------------*/
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L)
    return INFEASIBLE;
    else
    {
        L = (LinkList)malloc(sizeof(LNode));
        L -> next = NULL;
        return OK;
    }
    /********** End **********/
}
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L)
    {
        free(L);
        L = NULL;
        return OK;
    }
    else
    return INFEASIBLE;
    /********** End **********/
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    else
    {
        free(L -> next);
        L -> next = NULL;
        return OK;
    }
    /********** End **********/
}
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    if(L -> next == NULL)
    return TRUE;
    else
    return FALSE;
    /********** End **********/
}
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    int length = 0;
    LinkList p = L -> next;
    while(p)
    {
        length++;
        p = p -> next;
    }
    return length;
    /********** End **********/
}
status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p = L -> next;
    if(i < 1)
    return ERROR;
    while(p)
    {
        i--;
        if(i == 0)
        {
            e = p -> data;
            return OK;
        }
        p = p -> next;
    }
    return ERROR;
    /********** End **********/
}
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p = L -> next;
    int i = 0;
    while(p)
    {
        i++;
        if(p -> data == e)
        return i;
        p = p -> next;
    }
    return ERROR;
    /********** End **********/
}
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p , q;
    p = L -> next;
    if(p)
    q = p -> next;
    else
    return ERROR;
    if(p -> data == e)
    return ERROR;
    while(q)
    {
        if(q -> data == e)
        {
            pre = p -> data;
            return OK;
        }
        p = p -> next;
        q = q -> next;
    }
    return ERROR;
    /********** End **********/
}
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p;
    p = L -> next;
    while(p)
    {
        if(p -> data == e && p -> next != NULL)
        {
            next = p -> next -> data;
            return OK;
        }
        p = p -> next;
    }
    return ERROR;
    /********** End **********/
}
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int j = 2;
    if(!L)
    return INFEASIBLE;
    LinkList p , q , r;
    p = L -> next;
    if(p)
    q = p -> next;
    if(!p && i > 1)
    return ERROR;
    
    if(i == 1)
    {
        r = (LinkList)malloc(sizeof(LNode));
        r -> data = e;
        r -> next = p;
        L -> next = r;
        return OK;
    }
    while(q)
    {
        
        if(j == i)
        {
            r = (LinkList)malloc(sizeof(LNode));
            r -> data = e;
            r -> next = q;
            p -> next = r;
            return OK;
        }
        q = q -> next;
        p = p -> next;
        j++;
        if(j == i && q == NULL)
        {
            r = (LinkList)malloc(sizeof(LNode));
            r -> data = e;
            r -> next = NULL;
            p -> next = r;
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}
status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p , q;
    p = L -> next;
    if(!p)
    return ERROR;
    q = p -> next;
    if(i == 1)
    {
        e = p -> data;
        L -> next = p -> next;
        return OK;
    }
    i--;
    while(q)
    {
        i--;
        if(i == 0)
        {
            e = q -> data;
            p -> next = q -> next;
            free(q);
            return OK;
        }
        p = p -> next;
        q = q -> next;
    }
    return ERROR;
    /********** End **********/
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p;
    p = L -> next;
    while(p)
    {
        printf("%d ",p -> data);
        p = p -> next;
    }
    return OK;
    /********** End **********/
}
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(!L)
    return INFEASIBLE;
    FILE *fp = NULL;
    fp = fopen(FileName,"w+");
    LinkList p;
    p = L -> next;
    while(p)
    {
        fprintf(fp,"%d ",p -> data);
        p = p -> next;
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if(L)
    return INFEASIBLE;
    int e;
    L = (LinkList)malloc(sizeof(LNode));
    L -> next = NULL;
    LinkList p;
    p = L;
    FILE *fp = NULL;
    fp = fopen(FileName,"r");
    while(fscanf(fp,"%d",&e) == 1)/*这里要注意最后while循环不能多添加一个链表*/
    {
        p -> next = (LinkList)malloc(sizeof(LNode));
        p = p -> next;
        p -> data = e;
    }
    p -> next = NULL;
    fclose(fp);
    return OK;
    /********** End 2 **********/
}
status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    LinkList L1;
    L1 = NULL;
    InitList(L1);
    Lists.elem[Lists.length].L = L1;
    int k = 0;
    for(k = 0;k < Lists.length;k++)
    {
        if(strcmp(Lists.elem[k].name,ListName) == 0)
        printf("已存在名为 %s 的线性表!",ListName);
        return 0;
    }
    strcpy(Lists.elem[Lists.length].name , ListName); 
    Lists.length++;
    
    /********** End **********/
}
status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    ElemType x , i , j;
    for(i = 0;i < Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name , ListName) == 0)
        {
            for(j = i;j < Lists.length - 1;j++)
            Lists.elem[j] = Lists.elem[j + 1];
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}
int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    ElemType i;
    for(i = 0;i < Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name , ListName) == 0)
        return i+1;
    }
    return 0;
    /********** End **********/
}